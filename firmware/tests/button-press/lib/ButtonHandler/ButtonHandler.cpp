/**
 * @file ButtonHandler.cpp
 * @author Christoph Tack (you@domain.com)
 * @brief This file handles everything about the button.  Count key presses and make distinction between short and long presses.
 * @version 0.1
 * @date 2022-01-07
 * 
 * @copyright Copyright (c) 2022
 * 
 * It polls the button and returns what event has occurred: nothing, long push, single short push, double push or triple push.
 */
#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(byte pinNr) : _pinNr(pinNr)
{
}

ButtonHandler::~ButtonHandler()
{
}

void ButtonHandler::init()
{
    _button_bounce.attach(_pinNr, INPUT_PULLUP);
    _button_bounce.interval(5); // interval in ms
}

ButtonHandler::BUTTON_ACTION ButtonHandler::loop()
{
    _button_bounce.update();
    switch (button_state)
    {
    case WAITING_FOR_FIRST_PRESS:
        if (_button_bounce.fell())
        {
            _button_count_interval.start(1000, AsyncDelay::MILLIS);
            button_push_count = 0;
            button_state = WAITING_FOR_BUTTON_RELEASE;
            return BT_START_OF_PRESS;
        }
        return BT_NO_ACTION;
    case WAITING_FOR_BUTTON_RELEASE:
        if (_button_bounce.rose())
        {
            button_push_count++;
        }
        if (_button_count_interval.isExpired())
        {
            button_state = COUNT_PRESSES;
        }
        return BT_NO_ACTION;
    case COUNT_PRESSES:
        button_state = WAITING_FOR_FIRST_PRESS;
        switch (button_push_count)
        {
        case 0:
            return BT_SINGLE_LONG_PUSH;
        case 1:
            return BT_SINGLE_SHORT_PUSH;
        case 2:
            return BT_DOUBLE_SHORT_PUSH;
        case 3:
        default:
            return BT_TRIPLE_SHORT_PUSH;
        }
        break;
    default:
        return BT_NO_ACTION;
    }
}