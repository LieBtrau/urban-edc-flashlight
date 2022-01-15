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
        LUXEON_LED,
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
	//Every LED has its own mode and brightness settings
	struct LedParameters
	{
		LED_MODE led_mode;
		byte led_brightness;
		uint16_t hue; //!< Most LEDs won't have option to change color.  EEPROM is large enough anyway.
	};
	LedParameters* getLedParameters(LED_DEVICE led);
private:
	int _address;
	struct DeviceParameters
	{
		LED_DEVICE selected_led;
		LedParameters led_parameters[MAX_LED];
	};
	DeviceParameters _led; //!< Actual object that will be stored in EEPROM

};
