#pragma once

#include "Arduino.h"

class LedHandler
{
public:
	LedHandler(){};
	LedHandler(byte &brightnessLevel);
	virtual bool increaseBrightness() = 0; //<! Returns false when max brightness reached
	virtual void setMinimumBrightness() = 0;
	virtual void turnOn() = 0;
	virtual void turnOff() = 0;

protected:
	byte *_brightnessLevel = nullptr;
};
