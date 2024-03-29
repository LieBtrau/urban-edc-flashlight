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
#include "pins.h"

static LedHandler *selected_LED = nullptr;

static void turnLedOff()
{
	selected_LED->turnOff();
	digitalWrite(PIN_DISABLE_LED, HIGH);
}

static void turnLedOn()
{
	digitalWrite(PIN_DISABLE_LED, LOW);
	selected_LED->turnOn();
}

LED_Controller::LED_Controller(NonVolatileParameters &nvp)
{
	NonVolatileParameters::LedParameters *lp;
	_pixels = Adafruit_NeoPixel(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

	// COB-array instantiation
	lp = nvp.getLedParameters(0);
	_ledCob.set(0, _ledUv, lp->led_brightness, lp->led_mode, PIN_EN_COB_ARRAY, PIN_PWM);

	// UV-LED instantiation
	lp = nvp.getLedParameters(1);
	_ledUv.set(1, _ledRgbRed, lp->led_brightness, lp->led_mode, PIN_EN_UV_STRING, PIN_PWM);

	// RGB-LED Red instantiation
	lp = nvp.getLedParameters(2);
	_ledRgbRed.set(2, _ledRgbGreen, lp->led_brightness, lp->led_mode, _pixels, 0);

	// RGB-LED Green instantiation
	lp = nvp.getLedParameters(3);
	_ledRgbGreen.set(3, _ledCob, lp->led_brightness, lp->led_mode, _pixels, 21845); //=65536/3

	selected_LED = &_ledCob;
	_selectedLedIndex = nvp.getSelectedLed();
	while (selected_LED->getId() != *_selectedLedIndex)
	{
		selected_LED = selected_LED->getNextLed();
		if (selected_LED == &_ledCob)
		{
			// we've had all LEDs and found no match
			*_selectedLedIndex = 0;
			break;
		}
	}

	_flasher.setTurnOnHandler(turnLedOn);
	_flasher.setTurnOffHandler(turnLedOff);
	_flasher.setLedMode(*selected_LED->getFlashingMode());
}

void LED_Controller::begin()
{
	pinMode(PIN_DISABLE_LED, OUTPUT);
	turnLedOn();
	_pixels.begin();
	_pixels.clear();
	_pixels.show();
}

void LED_Controller::showNextLed()
{
	turnLedOff();

	selected_LED = selected_LED->getNextLed();
	*_selectedLedIndex = selected_LED->getId();
	_flasher.setLedMode(*selected_LED->getFlashingMode());
}

bool LED_Controller::increaseBrightness()
{
	return selected_LED->increaseBrightness();
}

void LED_Controller::setMinimumBrightness()
{
	return selected_LED->setMinimumBrightness();
}

bool LED_Controller::nextFlashingMode()
{
	byte *currentFlashMode = selected_LED->getFlashingMode();
	if (*currentFlashMode < MAX_LED_MODE)
	{
		(*currentFlashMode)++;
	}
	_flasher.setLedMode(*currentFlashMode);
	return *currentFlashMode != MAX_LED_MODE;
}

void LED_Controller::disableFlashing()
{
	byte *currentFlashMode = selected_LED->getFlashingMode();
	*currentFlashMode = 0;
	_flasher.setLedMode(*currentFlashMode);
}

void LED_Controller::loop()
{
	if (_isEnabled)
	{
		_flasher.loop();
	}
}

void LED_Controller::onOffControl(bool isOn)
{
	_isEnabled = isOn;
	if (!_isEnabled)
	{
		turnLedOff();
	}
}

bool LED_Controller::isLedOn() const
{
	return _isEnabled;
}