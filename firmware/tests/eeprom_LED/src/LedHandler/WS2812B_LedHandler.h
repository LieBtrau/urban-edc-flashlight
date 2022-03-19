#pragma once

#include "LedHandler.h"
#include <Adafruit_NeoPixel.h>

class WS2812B_LedHandler : public LedHandler
{
private:
    const byte MIN_BRIGHTNESS = 10;
    const byte MAX_BRIGHTNESS = 255;
    const byte BRIGHTNESS_INCREASE_STEP = 10;
    const byte DEFAULT_SATURATION = 255;
    Adafruit_NeoPixel *_pixels;
    uint16_t _hue = 0;

public:
    WS2812B_LedHandler(){};
    WS2812B_LedHandler(Adafruit_NeoPixel &pixel, byte &brightnessLevel, uint16_t hue);
    WS2812B_LedHandler(const WS2812B_LedHandler &); // copy constructor
    void operator=(const WS2812B_LedHandler &);     // assignment operator
    bool increaseBrightness();
    void setMinimumBrightness();
    void turnOn();
    void turnOff();
};
