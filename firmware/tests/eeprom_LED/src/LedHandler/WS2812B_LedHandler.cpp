#include "WS2812B_LedHandler.h"

WS2812B_LedHandler::WS2812B_LedHandler(Adafruit_NeoPixel &pixel, byte &brightness, uint16_t hue) : LedHandler(brightness),
                                                                                                    _pixels(&pixel),
                                                                                                    _hue(hue)
{
    if (brightness > MAX_BRIGHTNESS)
    {
        brightness = MAX_BRIGHTNESS;
    }
    if (brightness < MIN_BRIGHTNESS)
    {
        brightness = MIN_BRIGHTNESS;
    }
}

WS2812B_LedHandler::WS2812B_LedHandler(const WS2812B_LedHandler &oldobject)
{
    _brightnessLevel = oldobject._brightnessLevel;
    _pixels = oldobject._pixels;
    _hue = oldobject._hue;
}

void WS2812B_LedHandler::operator=(const WS2812B_LedHandler &oldobject)
{
    _brightnessLevel = oldobject._brightnessLevel;
    _pixels = oldobject._pixels;
    _hue = oldobject._hue;
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