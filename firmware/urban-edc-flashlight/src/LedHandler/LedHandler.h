#pragma once

#include "Arduino.h"

class LedHandler
{
public:
	LedHandler();
	virtual bool increaseBrightness() = 0; //<! Returns false when max brightness reached
	virtual void setMinimumBrightness() = 0;
	virtual void turnOn() = 0;
	virtual void turnOff() = 0;
	byte getId() const;
	LedHandler *getNextLed() const; //<! for linkedlist functionality
    byte* getFlashingMode();
protected:
	void set(byte& ledMode);
	byte _id = 0;
	LedHandler *_nextLed = nullptr;
	byte *_brightnessLevel = nullptr;
private:
	byte *_ledMode = nullptr;
};
