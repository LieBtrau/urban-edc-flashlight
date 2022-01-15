/**
 * @file NonVolatileParameters.cpp
 * @author Christoph Tack (you@domain.com)
 * @brief Providing storage for device parameters.
 * I know that EEPROM.get() and EEPROM.put() could also be used to write a struct to the EEPROM, but my implementation of EEPROM-
 * anything checks the validity of the data stored in EEPROM using a 16-bit CRC.
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "NonVolatileParameters.h"
#include "EEPROMAnything.h"

NonVolatileParameters::NonVolatileParameters(int address) : _address(address)
{
    DeviceParameters tempLed;
    if(EEPROM_readAnything(address, tempLed))
    {
        _led = tempLed;
        return;
    }
    Serial.println("No valid data in EEPROM");
}

void NonVolatileParameters::store() const
{
    EEPROM_writeAnything(_address, _led);
}

NonVolatileParameters::LedParameters* NonVolatileParameters::getLedParameters(LED_DEVICE led)
{
    return &_led.led_parameters[led];
}