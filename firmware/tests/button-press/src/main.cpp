#include "Arduino.h"
#include "ButtonHandler.h"

const byte PIN_BUTTON = PIN_PA0;
const byte PIN_LED = PIN_PB0;

ButtonHandler bh(PIN_BUTTON);

void setup()
{
	OSCCAL -= 5; // 999.178kHz
	pinMode(PIN_LED, OUTPUT);
	Serial.begin(4800);
	// Disable Serial RX
	ACSR &= ~(1 << ACIE);
	ACSR |= ~(1 << ACD);
	bh.init();
}

void loop()
{
	ButtonHandler::BUTTON_ACTION ba = bh.loop();
	if(ba!=ButtonHandler::BT_NO_ACTION)
	{
		Serial.println(ba, DEC);
	}
}