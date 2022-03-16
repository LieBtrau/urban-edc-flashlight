#include "Simple_LedHandler.h"

Simple_LedHandler::Simple_LedHandler(byte &brightnessLevel, byte enablePin, byte pwmPin) : LedHandler(brightnessLevel),
                                                                           _enablePin(enablePin),
                                                                           _pwmPin(pwmPin)
{
    if (brightnessLevel >= sizeof(brightnessLevels))
    {
        *_brightness = sizeof(brightnessLevels) - 1;
    }
    pinMode(_enablePin, OUTPUT);
}

bool Simple_LedHandler::increaseBrightness()
{
    *_brightness = (*_brightness) < (sizeof(brightnessLevels) - 1) ? (*_brightness) + 1 : (sizeof(brightnessLevels) - 1);
    turnOn();
    return *_brightness != sizeof(brightnessLevels) - 1;
}

void Simple_LedHandler::setMinimumBrightness()
{
    *_brightness = 0;
    turnOn();
}

void Simple_LedHandler::turnOn()
{
    digitalWrite(_enablePin, HIGH);
    analogWrite(_pwmPin, brightnessLevels[*_brightness]);
}

void Simple_LedHandler::turnOff()
{
    digitalWrite(_enablePin, LOW);
    analogWrite(_pwmPin, 0);
}
