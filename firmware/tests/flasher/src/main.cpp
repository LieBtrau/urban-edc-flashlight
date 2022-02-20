/**
 * @brief Flasher with simple state machine (34 bytes RAM, 1102 bytes flash)
 * 
 * Good state machine : https://github.com/cotestatnt/YA_FSM
 * 2nd choice: https://github.com/jonblack/arduino-fsm
 * 3rd choice: https://github.com/jrullan/StateMachine
 * 	But this will likely use much more RAM & flash.
 */

#include <Arduino.h>
#include "Flasher.h"

const byte LED_PIN = PIN_B0;
Flasher flasher;

void led_on()
{
	digitalWrite(LED_PIN, HIGH);
}

void led_off()
{
	digitalWrite(LED_PIN, LOW);
}

void setup()
{
	// OSCCAL -= 5; // 999.178kHz
	// Serial.begin(4800);
	// // Disable Serial RX
	// ACSR &= ~(1 << ACIE);
	// ACSR |= ~(1 << ACD);
	// while (!Serial)
	// {
	// 	; // wait for serial port to connect. Needed for native USB port only
	// }
	// delay(2000);
	// Serial.println("ready");

	pinMode(LED_PIN, OUTPUT);
	flasher.setTurnOffHandler(led_off);
	flasher.setTurnOnHandler(led_on);
	flasher.setLedMode(0);
}

void loop()
{
	flasher.loop();
}