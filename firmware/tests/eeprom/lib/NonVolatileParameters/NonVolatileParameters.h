#pragma once

#include "Arduino.h"

class NonVolatileParameters
{
public:
	typedef enum
	{
		CONTINUOUSLY_ON,
		SINGLE_FLASH,
		TRIPLE_FLASH,
		MAX_MODE
	} LED_MODE;
	NonVolatileParameters(int address);
	void store() const;
	// Every LED has its own mode and brightness settings
	struct LedParameters
	{
		LED_MODE led_mode = CONTINUOUSLY_ON;
		byte led_brightness = 0;
	};
	LedParameters *getLedParameters(byte id);
	byte* getSelectedLed();

private:
	int _address;
	static const int MAX_NR_OF_LEDS=6;
	struct DeviceParameters
	{
		byte selected_led = 0;
		LedParameters led_parameters[MAX_NR_OF_LEDS];
	};
	DeviceParameters _device_params; //!< Actual object that will be stored in EEPROM
};
