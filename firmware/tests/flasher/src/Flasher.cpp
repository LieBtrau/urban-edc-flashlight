#include "Flasher.h"

Flasher::Flasher(/* args */)
{
}

Flasher::~Flasher()
{
}

void Flasher::setLedMode(NonVolatileParameters::LED_MODE led_mode)
{
    switch (led_mode)
    {
    case NonVolatileParameters::CONTINUOUSLY_ON:
        led_setting.flash_count = 0;
        led_setting.inter_cycle_time = 0;
        led_setting.led_off_time = 0;
        led_setting.led_on_time = -1;
        break;
    case NonVolatileParameters::SINGLE_FLASH:
        led_setting.flash_count = 0;
        led_setting.inter_cycle_time = 900;
        led_setting.led_off_time = 100;
        led_setting.led_on_time = 100;
        break;
    case NonVolatileParameters::TRIPLE_FLASH:
        led_setting.flash_count = 3;
        led_setting.inter_cycle_time = 500;
        led_setting.led_off_time = 100;
        led_setting.led_on_time = 100;
        break;
    default:
        break;
    }
    _flash_state = FLASH_INIT;
}

void Flasher::loop()
{
    switch (_flash_state)
    {
    case FLASH_INIT:
        _flash_state = LED_IS_OFF;
        _timer.expire();
        _cycleCounter = led_setting.flash_count;
        break;
    case LED_IS_OFF:
        if (_timer.isExpired())
        {
            if (_turnOn != nullptr)
            {
                _turnOn();
            }
            if (led_setting.led_on_time > 0)
            {
                _timer.start(led_setting.led_on_time, AsyncDelay::MILLIS);
                _flash_state = LED_IS_ON;
            }
        }
        break;
    case LED_IS_ON:
        if (_timer.isExpired())
        {
            if (_turnOff != nullptr)
            {
                _turnOff();
            }
            if (_cycleCounter > 0 && --_cycleCounter > 0)
            {
                _timer.start(led_setting.led_off_time, AsyncDelay::MILLIS);
                _flash_state = LED_IS_OFF;
            }
            else
            {
                _flash_state = FLASH_INTERCYCLE;
                _timer.start(led_setting.inter_cycle_time, AsyncDelay::MILLIS);
            }
        }
        break;
    case FLASH_INTERCYCLE:
        if (_timer.isExpired())
        {
            _flash_state = FLASH_INIT;
        }
        break;
    default:
        break;
    }
}

void Flasher::setTurnOnHandler(void (*callback)())
{
    _turnOn = callback;
}

void Flasher::setTurnOffHandler(void (*callback)())
{
    _turnOff = callback;
}
