#include "Arduino.h"
#include "ButtonHandler.h"

const byte PIN_BUTTON = PIN_PB0;

ButtonHandler bh(PIN_BUTTON);

void setup()
{
	OSCCAL -= 5; // 999.178kHz
	Serial.begin(4800);
	// Disable Serial RX
	ACSR &= ~(1 << ACIE);
	ACSR |= ~(1 << ACD);
	delay(2000);
	bh.init();
	Serial.println("ready");
}

void loop()
{
	ButtonHandler::BUTTON_ACTION ba = bh.loop();
	if(ba!=ButtonHandler::BT_NO_ACTION)
	{
		Serial.println(ba, DEC);
	}
}