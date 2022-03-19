#include "LedHandler.h"

LedHandler::LedHandler()
{
}

byte LedHandler::getId() const
{
    return _id;
}

LedHandler* LedHandler::getNextLed() const
{
    return _nextLed;
}