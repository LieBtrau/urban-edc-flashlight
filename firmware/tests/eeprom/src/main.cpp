#include "Arduino.h"
#include "NonVolatileParameters.h"
#include "EEPROM.h"

void showParameters(NonVolatileParameters::LedParameters &lp)
{
	Serial.printf("%d %d %d\r\n", lp.hue, lp.led_brightness, lp.led_mode);
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
	//EEPROM.write(0, 0xAA); // invalidate EEPROM
	NonVolatileParameters nvp(0);
	NonVolatileParameters::LedParameters *lp = nvp.getLedParameters(NonVolatileParameters::COB_ARRAY);
	showParameters(*lp);
	lp->hue++;
	lp->led_brightness++;
	lp->led_mode = NonVolatileParameters::TRIPLE_FLASH;
	nvp.store();
	Serial.println("all stored");
}

void loop()
{ /* Empty loop */
}