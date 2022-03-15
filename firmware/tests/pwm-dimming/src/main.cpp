#include <Arduino.h>

const byte LED_PWM = PIN_PA6;

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
}

void setup()
{
	initSerialPort();
}

void loop()
{
	// put your main code here, to run repeatedly:
	for (int i = 0; i < 8; i++)
	{
		analogWrite(LED_PWM, 1<<i);
		//Serial.println(i, DEC);
		delay(50);
	}
	for (int i = 7; i >=0; i--)
	{
		analogWrite(LED_PWM, 1<<i);
		delay(50);
	}

}