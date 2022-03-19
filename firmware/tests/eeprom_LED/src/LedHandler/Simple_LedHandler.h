#pragma once

#include "LedHandler.h"

class Simple_LedHandler : public LedHandler
{
private:
    const byte brightnessLevels[6] = {1, 3, 9, 27, 81, 243};
    byte _enablePin;
    byte _pwmPin;

public:
    Simple_LedHandler(){};
    Simple_LedHandler(byte &brightnessLevel, byte enablePin, byte pwmPin);
    void operator=(const Simple_LedHandler &);     // assignment operator
    bool increaseBrightness();
    void setMinimumBrightness();
    void turnOn();
    void turnOff();
};
