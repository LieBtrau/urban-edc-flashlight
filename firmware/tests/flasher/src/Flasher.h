#pragma once

#include "Arduino.h"
#include "AsyncDelay.h"

class Flasher
{
private:
    typedef enum
    {
        FLASH_INIT,
        WAITING_TO_TURN_ON,
        WAITING_TO_TURN_OFF,
        FLASH_INTERCYCLE
    } FLASH_STATE;
    const int led_on_time = 100;
    const int led_off_time = 100;
    const int inter_cycle_time = 500;
    byte _flash_count = 0;
    void (*_turnOn)() = nullptr;
    void (*_turnOff)() = nullptr;
    AsyncDelay _timer;
    bool _isLedOn = false;
    FLASH_STATE _flash_state = FLASH_INIT;
    byte _cycleCounter = 0;

public:
    Flasher(/* args */);
    ~Flasher();
    void loop();
    void setLedMode(byte flash_count);
    void setTurnOnHandler(void (*callback)());
    void setTurnOffHandler(void (*callback)());
};
