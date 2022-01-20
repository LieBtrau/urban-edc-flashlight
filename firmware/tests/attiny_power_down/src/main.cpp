#include <Arduino.h>
#include <avr/sleep.h>

const byte PIN_LED = PIN_PB0;

void setup()
{
	OSCCAL -= 5; // 999.178kHz
	Serial.begin(4800);
	// Disable Serial RX
	ACSR &= ~(1 << ACIE);
	ACSR |= ~(1 << ACD);
	delay(2000);
	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_PA0, INPUT_PULLUP);
	pinMode(PIN_PA7, INPUT_PULLUP);
	digitalWrite(PIN_LED, HIGH);
	Serial.println("ready");
}

ISR(PCINT0_vect)
{
	sleep_disable(); // Disable sleep mode
}

void Going_To_Sleep()
{
	Serial.println("going to sleep");
	digitalWrite(PIN_LED, LOW); // turning LED off
	delay(1000);				// wait a second to allow the led to be turned off before going to sleep
	bitSet(PCMSK0, PCINT0);		// EXTINT0 pin mask : enable external interrupt on pin PCINT0
	bitSet(GIFR, PCIF0);		// Clear pending interrupt flag
	bitSet(GIMSK, PCIE0);		// Enable EXTINT0 as interrupt source
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	byte adcsra = ADCSRA;
	bitClear(ADCSRA, ADEN); // disable ADC
	byte acsr = ACSR;
	bitSet(ACSR, ACD);		// disable Analog comparator
	byte didr0 = DIDR0;
	DIDR0 = 0xFF; // disable digital input buffer for analog pins
	byte prr = PRR;
	PRR = 0x0F;		// Disable peripherals (timer1, timer0, USI, ADC)
	sleep_enable(); // Enabling sleep mode
	sei();
	sleep_cpu(); // activating sleep mode
	// next line of code executed after the interrupt
	PRR = prr;
	DIDR0 = didr0;
	ADCSRA = adcsra;
	ACSR = acsr;
	Serial.println("just woke up!"); 
}

void loop()
{
	delay(3000); // wait 5 seconds before going to sleep
	Going_To_Sleep();
	digitalWrite(PIN_LED, HIGH);
}
