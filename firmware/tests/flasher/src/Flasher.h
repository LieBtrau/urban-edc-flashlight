#pragma once

#include "Arduino.h"
#include "AsyncDelay.h"
#include "NonVolatileParameters.h"

class Flasher
{
private:
    typedef enum
    {
        FLASH_INIT,
        LED_IS_OFF,
        LED_IS_ON,
        FLASH_INTERCYCLE
    } FLASH_STATE;
    struct Led_setting
    {
        int led_on_time = 0;
        int led_off_time = 0;
        int flash_count = 0;
        int inter_cycle_time = 0;
    };
    void (*_turnOn)() = nullptr;
    void (*_turnOff)() = nullptr;
    AsyncDelay _timer;
    bool _isLedOn = false;
    FLASH_STATE _flash_state = FLASH_INIT;
    Led_setting led_setting;
    byte _cycleCounter = 0;

public:
    Flasher(/* args */);
    ~Flasher();
    void loop();
    void setLedMode(NonVolatileParameters::LED_MODE led_mode);
    void setTurnOnHandler(void (*callback)());
    void setTurnOffHandler(void (*callback)());
};
