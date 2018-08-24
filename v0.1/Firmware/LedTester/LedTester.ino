#include <Arduino.h>

/** 
 * Should be working working 2018-08-19
 * Use Arduino IDE
 * ESP8266 by ESP8266 Community v. 2.2.0
 * Board: NodeMCU (12E)
 * CPU Freq: 80Mhz
 * Flash size: 4M (3M SPiffs)
 * Upload speed: 115200
 */

// ---------------------------------------- PIN DEFINTIONS FOR LEDS ------------------------------------------

#define RIGHTH D0
#define RIGHTL D1

#define LEFTH D3
#define LEFTL D2

#define GREEN D5
#define YELLOW D6
#define RED D7

#define LEFT 0
#define RIGHT 1

#define posPinL 4
// should be HIGH to work
int posPins[posPinL] = {LEFTH, LEFTL, RIGHTH, RIGHTL}; 
#define negPinL 3
// should be low to work
int negPins[negPinL] = {RED, YELLOW, GREEN}; 


#define USE_SERIAL Serial

// ------------------------------------------- MAIN PROGRAM --------------------------------


void setup() {
 USE_SERIAL.begin(115200);
  initLeds(); 
}


void loop() {
  USE_SERIAL.printf("Testing leds");

for(int i = 0; i < 6; i ++){

  setLed(true, i,LEFT);
  delay(1000);
  setLed(false, i,LEFT);
  delay(1000);
    setLed(true, i,RIGHT);
  delay(1000);
  setLed(false, i,RIGHT);
  delay(1000);
}
}





// ----------------------------------------- LED CONTROL --------------------------------------------

/** Number: the number of the led, with 0 being red, 2 being yellow and 4 being green
 *  Series: 0 = left; 1 = right
 */
void setLed(boolean status, int number, int series){
  series = (number % 2) == 0 ?  posPins[series*2] : posPins[series*2 + 1];
  int pin = negPins[number/2];

  digitalWrite(pin, status ? LOW : HIGH);
  digitalWrite(series, status ? HIGH : LOW); 
}

void initLeds(){
  for(int i = 0; i < negPinL; i++){
    pinMode(negPins[i], OUTPUT);
  }
  for(int i = 0; i < posPinL; i++){
    pinMode(posPins[i], OUTPUT);
  }
  allLedsOff();
}

void allLedsOff(){
  for(int i = 0; i < 6; i++){
    setLed(false, i, LEFT);
    setLed(false, i, RIGHT);
  }
}



