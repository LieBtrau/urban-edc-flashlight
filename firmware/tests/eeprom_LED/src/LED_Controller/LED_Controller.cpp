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
#include "LedHandler/WS2812B_LedHandler.h"

LED_Controller::LED_Controller(NonVolatileParameters &nvp)
{
	// Global parameters
	_current_LED = nvp.getSelectedLed();

	// RGB-LED instantiation
	NonVolatileParameters::LedParameters *lp = nvp.getLedParameters(NonVolatileParameters::RGB_LED);
	_ledCollection[NonVolatileParameters::RGB_LED] = new WS2812B_LedHandler(lp->led_brightness, lp->hue, PIN_PB1);
}

void LED_Controller::showNextLed()
{
	if (_ledCollection[*_current_LED] != nullptr)
	{
		_ledCollection[*_current_LED]->turnOff();
	}

	// Some extra lines to keep the compiler happy.
	byte selected_led = *_current_LED;
	selected_led = selected_led < NonVolatileParameters::MAX_LED - 1 ? selected_led + 1 : NonVolatileParameters::COB_ARRAY;
	*_current_LED = (NonVolatileParameters::LED_DEVICE)selected_led;

	if (_ledCollection[*_current_LED] != nullptr)
	{
		_ledCollection[*_current_LED]->turnOn();
	}
}