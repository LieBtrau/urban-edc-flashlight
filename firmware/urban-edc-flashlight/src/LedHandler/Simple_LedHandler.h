#pragma once

#include "LedHandler.h"

class Simple_LedHandler : public LedHandler
{
private:
   const byte brightnessLevels[6] = {1, 4, 16, 64, 255};
    byte _enablePin;
    byte _pwmPin;
public:
    Simple_LedHandler();
    void set(byte id, LedHandler &nextLed, byte &brightnessLevel, byte& ledMode, byte enablePin, byte pwmPin);
    bool increaseBrightness();
    void setMinimumBrightness();
    void turnOn();
    void turnOff();
};
