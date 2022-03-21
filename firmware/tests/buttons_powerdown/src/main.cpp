#include <Arduino.h>
#include <avr/sleep.h>
#include "ButtonHandler.h"

const byte PIN_BUTTON = PIN_PA0;

ButtonHandler bh(PIN_BUTTON);

void setup()
{
	OSCCAL -= 5; // 999.178kHz
	Serial.begin(4800);
	// Disable Serial RX
	ACSR &= ~(1 << ACIE);
	ACSR |= ~(1 << ACD);
	bh.init();
	pinMode(LED_BUILTIN, OUTPUT);
	delay(2000);
	Serial.println("ready");
}

ISR(PCINT0_vect)
{
	sleep_disable(); // Disable sleep mode
}

void going_To_Sleep()
{
	bitSet(PCMSK0, PCINT0); // EXTINT0 pin mask : enable external interrupt on pin PCINT0
	bitSet(GIFR, PCIF0);	// Clear pending interrupt flag
	bitSet(GIMSK, PCIE0);	// Enable EXTINT0 as interrupt source
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	byte adcsra_backup = ADCSRA;
	bitClear(ADCSRA, ADEN); // disable ADC
	byte acsr_backup = ACSR;
	bitSet(ACSR, ACD); // disable Analog comparator
	byte didr0_backup = DIDR0;
	DIDR0 = 0xFF; // disable digital input buffer for analog pins
	byte prr_backup = PRR;
	PRR = 0x0F;		// Disable peripherals (timer1, timer0, USI, ADC)
	sleep_enable(); // Enabling sleep mode
	sei();
	sleep_cpu(); // activating sleep mode

	// zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...

	// next line of code executed after the interrupt
	PRR = prr_backup;
	DIDR0 = didr0_backup;
	ADCSRA = adcsra_backup;
	ACSR = acsr_backup;
	Serial.println("just woke up!");
}

void loop()
{
	ButtonHandler::BUTTON_ACTION ba = bh.loop();
	if (ba != ButtonHandler::BT_NO_ACTION)
	{
		Serial.println(ba, DEC);
		switch (ba)
		{
		case ButtonHandler::BT_NO_ACTION:
			// do nothing
			break;
		case ButtonHandler::BT_START_OF_PRESS:
			if (digitalRead(LED_BUILTIN) == LOW)
			{
				Serial.println("Turning LED on");
				digitalWrite(LED_BUILTIN, HIGH);
			}
			break;
		case ButtonHandler::BT_SINGLE_LONG_PRESS:
			digitalWrite(LED_BUILTIN, LOW);
			going_To_Sleep();
		default:
			break;
		}
	}
}
