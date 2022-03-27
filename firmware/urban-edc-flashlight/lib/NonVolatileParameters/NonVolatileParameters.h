#pragma once

#include "Arduino.h"

class NonVolatileParameters
{
public:
	NonVolatileParameters(int address);
	void store() const;
	// Every LED has its own mode and brightness settings
	struct LedParameters
	{
		byte led_mode = 0;
		byte led_brightness = 0;
	};
	LedParameters *getLedParameters(byte id);
	byte *getSelectedLed();

private:
	int _address;
	static const int MAX_NR_OF_LEDS = 6;
	struct DeviceParameters
	{
		byte selected_led = 0;
		LedParameters led_parameters[MAX_NR_OF_LEDS];
	};
	DeviceParameters _device_params; //!< Actual object that will be stored in EEPROM
};
