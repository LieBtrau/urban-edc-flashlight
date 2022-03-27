#include "Flasher.h"

Flasher::Flasher(/* args */)
{
}

Flasher::~Flasher()
{
}

void Flasher::setLedMode(byte flash_count)
{
    _flash_count = flash_count;
    _flash_state = FLASH_INIT;
}

void Flasher::loop()
{
    switch (_flash_state)
    {
    case FLASH_INIT:
        _flash_state = WAITING_TO_TURN_ON;
        _timer.expire();
        _cycleCounter = _flash_count;
        break;
    case WAITING_TO_TURN_ON:
        if (_timer.isExpired())
        {
            if (_turnOn != nullptr)
            {
                _turnOn();
            }
            if (_flash_count > 0)
            {
                _timer.start(led_on_time, AsyncDelay::MILLIS);
                _flash_state = WAITING_TO_TURN_OFF;
            }
        }
        break;
    case WAITING_TO_TURN_OFF:
        if (_timer.isExpired())
        {
            if (_turnOff != nullptr)
            {
                _turnOff();
            }
            if (_cycleCounter > 0 && --_cycleCounter > 0)
            {
                _timer.start(led_off_time, AsyncDelay::MILLIS);
                _flash_state = WAITING_TO_TURN_ON;
            }
            else
            {
                _flash_state = FLASH_INTERCYCLE;
                _timer.start(inter_cycle_time, AsyncDelay::MILLIS);
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
