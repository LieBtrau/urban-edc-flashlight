#pragma once

#include "LedHandler.h"
#include <Adafruit_NeoPixel.h>

class WS2812B_LedHandler : public LedHandler
{
private:
    const byte MIN_BRIGHTNESS=10;
    const byte MAX_BRIGHTNESS=255;
    const byte BRIGHTNESS_INCREASE_STEP=10;
    const byte DEFAULT_SATURATION=255;
    Adafruit_NeoPixel _pixels;
    uint16_t *_hue = nullptr;
    byte _ledPin;

public:
    WS2812B_LedHandler(byte &brightness, uint16_t &hue, byte ledPin);
    bool increaseBrightness();
    void setMinimumBrightness();
    void turnOn();
    void turnOff();
    bool setHue(uint16_t hue);
};
