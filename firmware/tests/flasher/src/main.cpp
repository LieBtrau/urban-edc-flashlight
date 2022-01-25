#include <Arduino.h>
#include "Flasher.h"

const byte LED_PIN = PIN_B0;
Flasher flasher;

void led_on()
{
	digitalWrite(LED_PIN, HIGH);
}

void led_off()
{
	digitalWrite(LED_PIN, LOW);
}

void setup()
{
	OSCCAL -= 5; // 999.178kHz
	Serial.begin(4800);
	// Disable Serial RX
	ACSR &= ~(1 << ACIE);
	ACSR |= ~(1 << ACD);
	while (!Serial)
	{
		; // wait for serial port to connect. Needed for native USB port only
	}
	delay(2000);
	Serial.println("ready");

	pinMode(LED_PIN, OUTPUT);
	flasher.setTurnOffHandler(led_off);
	flasher.setTurnOnHandler(led_on);
	flasher.setLedMode(NonVolatileParameters::SINGLE_FLASH);
}

void loop()
{
	flasher.loop();
}