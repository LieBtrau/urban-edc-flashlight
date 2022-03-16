#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Adafruit_NeoPixel pixels(1, PIN_PB1, NEO_GRB + NEO_KHZ800);

void setup()
{
	OSCCAL -= 5;
	pixels.begin();
	pixels.clear();
	Serial.begin(4800);
	// Disable Serial RX
	ACSR &= ~(1 << ACIE);
	ACSR |= ~(1 << ACD);
	Serial.print("Hello");
	pixels.setPixelColor(0, pixels.Color(255, 0, 0, 0));
	pixels.show(); // Send the updated pixel colors to the hardware.
}

void loop()
{
	for (long hue = 0; hue < 65536; hue += 10)
	{
		for (int i = 0; i < 256; i++)
		{
			pixels.setPixelColor(0, pixels.gamma32(pixels.ColorHSV(hue, 255, i)));
			pixels.show();
			delay(10);
		}
		for (int i = 0; i < 256; i++)
		{
			pixels.setPixelColor(0, pixels.gamma32(pixels.ColorHSV(hue, 255, 255 - i)));
			pixels.show();
			delay(10);
		}
	}
}