#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Adafruit_NeoPixel pixels(1, PIN_PB1, NEO_GRB + NEO_KHZ800);

void setup()
{
	OSCCAL-=5;
	pixels.begin(); 
	pixels.clear(); 
	Serial.begin(4800);
    //Disable Serial RX
    ACSR &=~(1<<ACIE);
    ACSR |=~(1<<ACD);
	Serial.print("Hello");
}

void loop()
{
	for (long i = 0; i < 65536; i+=10)
	{ 
		pixels.setPixelColor(0, pixels.gamma32(pixels.ColorHSV(i,255,64)));
		pixels.show(); // Send the updated pixel colors to the hardware.
	}
}