#include <Arduino.h>

/** 
 * Should be working working 2018-09-18
 * Use Arduino IDE
 * ESP8266 by ESP8266 Community v. 2.2.0
 * Board: NodeMCU (12E)
 * CPU Freq: 80Mhz
 * Flash size: 4M (3M SPiffs)
 * Upload speed: 115200
 */

#define BRIGHTNESS_PIN A0
#define USE_SERIAL Serial

// ------------------------------------------- MAIN PROGRAM --------------------------------


void setup() {
 USE_SERIAL.begin(115200);
 USE_SERIAL.printf("Brightness tester");
}


void loop() {
  int light = analogRead(BRIGHTNESS_PIN);
  USE_SERIAL.printf("Brightness reads %d\n", light);
  delay(100);
}







