#pragma once

#include "Arduino.h"

class NonVolatileParameters
{
public:
	typedef enum
	{
		COB_ARRAY,
		UV_LED,
		RGB_LED,
		MAX_LED
	} LED_DEVICE;
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
		uint16_t hue = 0; //!< Most LEDs won't have option to change color.  EEPROM is large enough anyway.
	};
	LedParameters *getLedParameters(LED_DEVICE led);
	LED_DEVICE* getSelectedLed();

private:
	int _address;
	struct DeviceParameters
	{
		LED_DEVICE selected_led = COB_ARRAY;
		LedParameters led_parameters[MAX_LED];
	};
	DeviceParameters _device_params; //!< Actual object that will be stored in EEPROM
};
