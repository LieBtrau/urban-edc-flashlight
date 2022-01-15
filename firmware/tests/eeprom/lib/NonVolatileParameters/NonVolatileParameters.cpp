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
    DeviceParameters temp_params;
    if(EEPROM_readAnything(address, temp_params))
    {
        _device_params = temp_params;
        return;
    }
    Serial.println("No valid data in EEPROM");
}

void NonVolatileParameters::store() const
{
    EEPROM_writeAnything(_address, _device_params);
}

NonVolatileParameters::LedParameters* NonVolatileParameters::getLedParameters(LED_DEVICE led)
{
    return &_device_params.led_parameters[led];
}

NonVolatileParameters::LED_DEVICE* NonVolatileParameters::getSelectedLed()
{
    return &_device_params.selected_led;
}