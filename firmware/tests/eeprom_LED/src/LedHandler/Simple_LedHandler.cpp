#include "Simple_LedHandler.h"

Simple_LedHandler::Simple_LedHandler(byte &brightnessLevel, byte enablePin, byte pwmPin) : LedHandler(brightnessLevel),
                                                                                           _enablePin(enablePin),
                                                                                           _pwmPin(pwmPin)
{
    if (brightnessLevel >= sizeof(brightnessLevels))
    {
        *_brightnessLevel = sizeof(brightnessLevels) - 1;
    }
    pinMode(_enablePin, OUTPUT);
}

void Simple_LedHandler::operator=(const Simple_LedHandler &oldobject)
{
    _brightnessLevel = oldobject._brightnessLevel;
    _enablePin = oldobject._enablePin;
    _pwmPin = oldobject._pwmPin;
}

bool Simple_LedHandler::increaseBrightness()
{
    *_brightnessLevel = (*_brightnessLevel) < (sizeof(brightnessLevels) - 1) ? (*_brightnessLevel) + 1 : (sizeof(brightnessLevels) - 1);
    turnOn();
    return *_brightnessLevel != sizeof(brightnessLevels) - 1;
}

void Simple_LedHandler::setMinimumBrightness()
{
    *_brightnessLevel = 0;
    turnOn();
}

void Simple_LedHandler::turnOn()
{
    digitalWrite(_enablePin, HIGH);
    analogWrite(_pwmPin, brightnessLevels[*_brightnessLevel]);
}

void Simple_LedHandler::turnOff()
{
    digitalWrite(_enablePin, LOW);
    analogWrite(_pwmPin, 0);
}
