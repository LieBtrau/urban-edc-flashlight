#include "Arduino.h"
#include "NonVolatileParameters.h"
#include "LED_Controller/LED_Controller.h"
#include "AsyncDelay.h"

NonVolatileParameters nvp(0);
LED_Controller led_ctrl(nvp);
AsyncDelay _timer;

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
	delay(2000);
	Serial.println("ready");
}

void setup()
{
	initSerialPort();
	led_ctrl.begin();
	_timer.start(3000, AsyncDelay::MILLIS);
}

void loop()
{
	led_ctrl.loop();
	if (_timer.isExpired())
	{
		_timer.restart();
		led_ctrl.showNextLed();
		led_ctrl.nextFlashingMode();
	}
	// delay(1000);
	// if(!led_ctrl.increaseBrightness())
	// {
	// 	led_ctrl.setMinimumBrightness();
	// }
	// delay(1000);
}
