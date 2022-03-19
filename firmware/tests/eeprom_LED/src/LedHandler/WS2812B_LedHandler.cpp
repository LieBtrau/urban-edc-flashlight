#include "WS2812B_LedHandler.h"

WS2812B_LedHandler::WS2812B_LedHandler()
{
}

void WS2812B_LedHandler::set(byte id, LedHandler &nextLed, byte &brightness, Adafruit_NeoPixel &pixel, uint16_t hue)

{
    _id = id;
    _nextLed = &nextLed;
    _brightnessLevel = &brightness;
    _pixels = &pixel;
    _hue = hue;
    if (brightness > MAX_BRIGHTNESS)
    {
        brightness = MAX_BRIGHTNESS;
    }
    if (brightness < MIN_BRIGHTNESS)
    {
        brightness = MIN_BRIGHTNESS;
    }
}

bool WS2812B_LedHandler::increaseBrightness()
{
    *_brightnessLevel = (MAX_BRIGHTNESS - *_brightnessLevel > BRIGHTNESS_INCREASE_STEP) ? *_brightnessLevel + BRIGHTNESS_INCREASE_STEP : MAX_BRIGHTNESS;
    turnOn();
    return *_brightnessLevel != MAX_BRIGHTNESS;
}

void WS2812B_LedHandler::setMinimumBrightness()
{
    *_brightnessLevel = MIN_BRIGHTNESS;
    turnOn();
}

void WS2812B_LedHandler::turnOn()
{
    _pixels->setPixelColor(0, _pixels->ColorHSV(_hue, DEFAULT_SATURATION, *_brightnessLevel));
    _pixels->show();
}

void WS2812B_LedHandler::turnOff()
{
    _pixels->clear();
    _pixels->show();
}