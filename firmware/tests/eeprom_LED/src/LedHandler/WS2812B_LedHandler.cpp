#include "WS2812B_LedHandler.h"

WS2812B_LedHandler::WS2812B_LedHandler(byte &brightness, uint16_t &hue, byte ledPin) : LedHandler(brightness),
                                                                                       _hue(&hue),
                                                                                       _ledPin(ledPin)
{
    if (brightness > MAX_BRIGHTNESS)
    {
        brightness = MAX_BRIGHTNESS;
    }
    if (brightness < MIN_BRIGHTNESS)
    {
        brightness = MIN_BRIGHTNESS;
    }
    _pixels = Adafruit_NeoPixel(1, _ledPin, NEO_GRB + NEO_KHZ800);
    _pixels.begin();
}

bool WS2812B_LedHandler::increaseBrightness()
{
    *_brightness = (MAX_BRIGHTNESS - *_brightness > BRIGHTNESS_INCREASE_STEP) ? *_brightness + BRIGHTNESS_INCREASE_STEP : MAX_BRIGHTNESS;
    turnOn();
    return *_brightness != MAX_BRIGHTNESS;
}

void WS2812B_LedHandler::setMinimumBrightness()
{
    *_brightness = MIN_BRIGHTNESS;
    turnOn();
}

void WS2812B_LedHandler::turnOn()
{
    _pixels.setPixelColor(0, _pixels.ColorHSV(*_hue, DEFAULT_SATURATION, *_brightness));
    _pixels.show();
}

void WS2812B_LedHandler::turnOff()
{
    _pixels.clear();
    _pixels.show();
}

bool WS2812B_LedHandler::setHue(uint16_t hue)
{
    *_hue = hue;
    return true;
}