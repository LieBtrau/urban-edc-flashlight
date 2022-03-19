#include "Arduino.h"
#include "NonVolatileParameters.h"
#include "LED_Controller/LED_Controller.h"

NonVolatileParameters nvp(0);
LED_Controller led_ctrl(nvp);

void initSerialPort()
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
	led_ctrl.begin();
	delay(2000);
}

void setup()
{
	initSerialPort();
	Serial.println("ready");
}

void loop()
{
	led_ctrl.showNextLed();
	delay(1000);
	if(!led_ctrl.increaseBrightness())
	{
		led_ctrl.setMinimumBrightness();
	}
	delay(1000);
}