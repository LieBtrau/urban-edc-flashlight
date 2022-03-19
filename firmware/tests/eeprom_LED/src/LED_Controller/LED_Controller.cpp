/**
 * @file LED_Controller.cpp
 * @author Christoph Tack (you@domain.com)
 * @brief Controls the different LEDs in this application.  Turning them on, off, flashing, selecting another LED etc...
 * @version 0.1
 * @date 2022-01-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "LED_Controller.h"

LED_Controller::LED_Controller(NonVolatileParameters &nvp)
{
	NonVolatileParameters::LedParameters *lp;
	_pixels = Adafruit_NeoPixel(1, PIN_PB1, NEO_GRB + NEO_KHZ800);

	// COB-array instantiation
	lp = nvp.getLedParameters(NonVolatileParameters::COB_ARRAY);
	_ledCob = Simple_LedHandler(lp->led_brightness, PIN_PB0, PIN_PA5);

	// UV-LED instantiation
	lp = nvp.getLedParameters(NonVolatileParameters::UV_LED);
	_ledUv = Simple_LedHandler(lp->led_brightness, PIN_PB0, PIN_PA6);

	// RGB-LED instantiation
	lp = nvp.getLedParameters(NonVolatileParameters::RGB_LED);
	_ledRgb = WS2812B_LedHandler(_pixels, lp->led_brightness, 0);

_selected_LED_index = nvp.getSelectedLed();
	switch (*_selected_LED_index)
	{
	case NonVolatileParameters::COB_ARRAY:
	default:
		_selected_LED = &_ledCob;
		break;
		;
	case NonVolatileParameters::UV_LED:
		_selected_LED = &_ledUv;
		break;
	case NonVolatileParameters::RGB_LED:
		_selected_LED = &_ledRgb;
		break;
	};
}

void LED_Controller::begin()
{
	_pixels.begin();
}

void LED_Controller::showNextLed()
{
	_selected_LED->turnOff();

	//This could have been implemented using a linked list.
	if (_selected_LED == &_ledCob)
	{
		_selected_LED = &_ledUv;
		//Updating LED index to keep RAM-copy of EEPROM data in sync.
		*_selected_LED_index = NonVolatileParameters::UV_LED;
	}
	else
	{
		if (_selected_LED == &_ledUv)
		{
			_selected_LED = &_ledRgb;
			*_selected_LED_index = NonVolatileParameters::RGB_LED;
		}
		else
		{
			if (_selected_LED == &_ledRgb)
			{
				_selected_LED = &_ledCob;
				*_selected_LED_index = NonVolatileParameters::COB_ARRAY;
			}
		}
	}
	_selected_LED->turnOn();
}

bool LED_Controller::increaseBrightness()
{
	return _selected_LED->increaseBrightness();
}

void LED_Controller::setMinimumBrightness()
{
	return _selected_LED->setMinimumBrightness();
}