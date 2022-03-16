#pragma once

#include "LedHandler/LedHandler.h"
#include "NonVolatileParameters.h"

class LED_Controller
{
public:
    LED_Controller(NonVolatileParameters &nvp);
    void showNextLed();
    bool increaseBrightness();
    void setMinimumBrightness();
private:
    LedHandler *_ledCollection[NonVolatileParameters::MAX_LED] = {};
    NonVolatileParameters::LED_DEVICE *_current_LED = nullptr;
};
