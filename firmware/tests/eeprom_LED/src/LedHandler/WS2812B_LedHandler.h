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
    WS2812B_LedHandler();
    void set(byte id, LedHandler &nextLed, byte &brightnessLevel, byte& ledMode,Adafruit_NeoPixel &pixel, uint16_t hue);
    bool increaseBrightness();
    void setMinimumBrightness();
    void turnOn();
    void turnOff();
};
