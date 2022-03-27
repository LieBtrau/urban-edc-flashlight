#pragma once

#include "LedHandler/LedHandler.h"
#include "LedHandler/WS2812B_LedHandler.h"
#include "LedHandler/Simple_LedHandler.h"

#include "NonVolatileParameters.h"
#include <Adafruit_NeoPixel.h>
#include "Flasher.h"

class LED_Controller
{
public:
    LED_Controller(NonVolatileParameters &nvp);
    void begin();
    void showNextLed();
    bool increaseBrightness();
    void setMinimumBrightness();
    bool nextFlashingMode();
    void disableFlashing();
    void loop();
    void onOffControl(bool isOn);
private:
    const byte MAX_LED_MODE = 3;
    byte *_selectedLedIndex = nullptr;
    Adafruit_NeoPixel _pixels;
    // creating the LEDs as members here avoids using dynamically allocating the objects, which doesn't work well on attiny.
    Simple_LedHandler _ledCob, _ledUv;
    WS2812B_LedHandler _ledRgbRed, _ledRgbGreen;
    Flasher _flasher;
    bool _isEnabled = false;
};
