#include "LedHandler.h"

LedHandler::LedHandler()
{
}

byte LedHandler::getId() const
{
    return _id;
}

LedHandler *LedHandler::getNextLed() const
{
    return _nextLed;
}

void LedHandler::set(byte &ledMode)
{
    _ledMode = &ledMode;
}

byte* LedHandler::getFlashingMode()
{
    return _ledMode;
}
