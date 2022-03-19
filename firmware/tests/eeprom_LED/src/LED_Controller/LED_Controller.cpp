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
	lp = nvp.getLedParameters(0);
	_ledCob.set(0, _ledUv, lp->led_brightness, PIN_PB0, PIN_PA5);

	// UV-LED instantiation
	lp = nvp.getLedParameters(1);
	_ledUv.set(1, _ledRgbRed, lp->led_brightness, PIN_PB0, PIN_PA6);

	// RGB-LED Red instantiation
	lp = nvp.getLedParameters(2);
	_ledRgbRed.set(2, _ledRgbGreen, lp->led_brightness, _pixels, 0);

	// RGB-LED Green instantiation
	lp = nvp.getLedParameters(3);
	_ledRgbGreen.set(3, _ledCob, lp->led_brightness, _pixels, 21845);//=65536/3

	_selected_LED = &_ledCob;
	while (_selected_LED->getId() != *nvp.getSelectedLed())
	{
		_selected_LED = _selected_LED->getNextLed();
		if (_selected_LED == &_ledCob)
		{
			// we've had all LEDs and found no match
			break;
		}
	}
}

void LED_Controller::begin()
{
	_pixels.begin();
}

void LED_Controller::showNextLed()
{
	_selected_LED->turnOff();

	_selected_LED = _selected_LED->getNextLed();

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