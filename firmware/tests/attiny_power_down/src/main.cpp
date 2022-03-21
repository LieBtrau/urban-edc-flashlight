#include <Arduino.h>
#include <avr/sleep.h>


void setup()
{
	OSCCAL -= 5; // 999.178kHz
	Serial.begin(4800);
	// Disable Serial RX
	ACSR &= ~(1 << ACIE);
	ACSR |= ~(1 << ACD);
	delay(2000);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PIN_PA0, INPUT_PULLUP); //PCINT0-pin
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.println("ready");
}

ISR(PCINT0_vect)
{
	sleep_disable(); // Disable sleep mode
}

void Going_To_Sleep()
{
	bitSet(PCMSK0, PCINT0);		// EXTINT0 pin mask : enable external interrupt on pin PCINT0
	bitSet(GIFR, PCIF0);		// Clear pending interrupt flag
	bitSet(GIMSK, PCIE0);		// Enable EXTINT0 as interrupt source
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	byte adcsra_backup = ADCSRA;
	bitClear(ADCSRA, ADEN); 	// disable ADC
	byte acsr_backup = ACSR;
	bitSet(ACSR, ACD);			// disable Analog comparator
	byte didr0_backup = DIDR0;
	DIDR0 = 0xFF; 				// disable digital input buffer for analog pins
	byte prr_backup = PRR;
	PRR = 0x0F;					// Disable peripherals (timer1, timer0, USI, ADC)
	sleep_enable(); 			// Enabling sleep mode
	sei();
	sleep_cpu(); 				// activating sleep mode

	//zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...zzz...
	//Status of digital outputs will keep its pre-sleep status, so LED will remain ON during sleep.

	// next line of code executed after the interrupt
	PRR = prr_backup;
	DIDR0 = didr0_backup;
	ADCSRA = adcsra_backup;
	ACSR = acsr_backup;
	Serial.println("just woke up!"); 
}

void loop()
{
	delay(3000); // wait 5 seconds before going to sleep
	Serial.println("going to sleep");
	// digitalWrite(LED_BUILTIN, LOW); // turning LED off
	delay(1000);				// wait a second to allow the led to be turned off before going to sleep
	Going_To_Sleep();
	// digitalWrite(LED_BUILTIN, HIGH);
}
