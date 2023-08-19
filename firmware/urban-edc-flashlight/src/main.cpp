#include "Arduino.h"
#include <avr/sleep.h>
#include "NonVolatileParameters.h"
#include "LED_Controller/LED_Controller.h"
#include "AsyncDelay.h"
#include "ButtonHandler.h"
#include "pins.h"

/**
 * This is a hack to get the device signature into the .version section of the ELF file
 * ".signature"-section will be at address 0x00840000
 */
#include <avr/signature.h>
#ifdef COMMIT_HASH
/**
 * This is a hack to get the firmware version into the .version section of the ELF file
 * ".version"-section will be stored just behind the .signature section (at address 0x00840003)
 */
static const unsigned char  __attribute__((__section__(".version"), used))  firmwareversion[] = COMMIT_HASH;
#endif


NonVolatileParameters nvp(0);
LED_Controller led_ctrl(nvp);
ButtonHandler bh(PIN_BUTTON);
bool firstKeyPressAfterWakeUp = false;

void initSerialPort()
{
	OSCCAL -= 5; // 999.178kHz
	Serial.begin(4800);
	// Disable Serial RX
	ACSR &= ~(1 << ACIE);
	ACSR |= ~(1 << ACD);
	while (!Serial)
	{
		; // wait for serial port to connect. Needed for native #include <avr/sleep.h>#include <avr/sleep.h>USB port only
	}
	delay(2000);
	Serial.println("ready");
	Serial.print("Firmware version: ");Serial.println((char*)firmwareversion);
}

void setup()
{
	initSerialPort();
	led_ctrl.begin();
	bh.init();
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
	led_ctrl.loop();
	if (ba != ButtonHandler::BT_NO_ACTION)
	{
		Serial.println(ba, DEC);
		switch (ba)
		{
		case ButtonHandler::BT_NO_ACTION:
			// do nothing
			break;
		case ButtonHandler::BT_START_OF_PRESS:
			firstKeyPressAfterWakeUp = !led_ctrl.isLedOn();
			if(firstKeyPressAfterWakeUp)
			{
				Serial.println("Turning LED on");
				led_ctrl.onOffControl(true);
			}
			break;
		case ButtonHandler::BT_SINGLE_SHORT_press:
			if (!firstKeyPressAfterWakeUp && led_ctrl.isLedOn())
			{
				led_ctrl.showNextLed();
			}
			break;
		case ButtonHandler::BT_DOUBLE_SHORT_press:
			if (!firstKeyPressAfterWakeUp && !led_ctrl.increaseBrightness())
			{
				led_ctrl.setMinimumBrightness();
			}
			break;
		case ButtonHandler::BT_TRIPLE_SHORT_press:
			if (!firstKeyPressAfterWakeUp && !led_ctrl.nextFlashingMode())
			{
				led_ctrl.disableFlashing();
			}
			break;
		case ButtonHandler::BT_SINGLE_LONG_PRESS:
			led_ctrl.onOffControl(false);
			going_To_Sleep();
			nvp.store();
		default:
			break;
		}
	}
}