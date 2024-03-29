/**
 * @file ButtonHandler.h
 * @author Christoph Tack (you@domain.com)
 * @brief implementation of the Button Handler
 * @version 0.1
 * @date 2022-01-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "Bounce2.h"
#include "AsyncDelay.h"

class ButtonHandler
{
private:
    typedef enum
    {
        WAITING_FOR_FIRST_PRESS,    
        WAITING_FOR_BUTTON_RELEASE,
        COUNT_PRESSES,
        WAITING_FOR_END_LONG_PRESS
    } BUTTON_STATE;
    Bounce _button_bounce;
    AsyncDelay _button_count_interval;
    BUTTON_STATE button_state = WAITING_FOR_FIRST_PRESS;
    byte button_press_count = 0;
    byte _pinNr;

public:
    typedef enum
    {
        BT_NO_ACTION,
        BT_START_OF_PRESS,
        BT_SINGLE_LONG_PRESS,
        BT_SINGLE_SHORT_press,
        BT_DOUBLE_SHORT_press,
        BT_TRIPLE_SHORT_press
    } BUTTON_ACTION;
    ButtonHandler(byte pinNr);
    void init();
    BUTTON_ACTION loop();
    ~ButtonHandler();
};
