/* ------------------------------ PIN DEFINTIONS FOR LEDS ------------------------------ */

#define BRIGHTNESS_PIN A0

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




/*
 * As per http://www.who.int/mediacentre/factsheets/fs313/en/
 * and per http://ec.europa.eu/environment/air/quality/standards.htm
 * WHO allows a daily mean of 25µg, and a yearly mean of 10µg (PM2.5)
 * EU allows a yearly mean of 25µg (PM2.5)
 *
 * IN practice: seldom over 50
 *
 * WHO allows a daily mean of 50µg and a yearly mean of 20µg (PM10)
 * EU allows a daily mean of 50µg, and a yearly mean of 40µg (PM10)
 *
 * The color coding: over the yearly WHO norm -> yellow; over the yearly EU-norm -> red

 */

float* barema25 = new float[9] {0, /*GOOD:*/5,  7.5, 10, /*AVG*/ 15,   20,   25,/*BAD*/ 35, 45};
float* barema10 = new float[9] {0, /*GOOD:*/7.5, 15, 20, /*AVG*/ 26.6, 33.3, 40,/*BAD*/ 50, 80};
float pm10 = 0;
float pm25 = 0;

// The current brightness. This value floats slowly (~20/sec max)
int brightness = 1000;


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

// Blinks the leds in an error-indicating sequence
// Takes 3 seconds to complete
void showError(int status, int phase){

  allLedsOff();
  int baseLed = 4;

  if(status == NOT_CONNECTED){
    baseLed = 2;
  }
  if(status == HTTPS_ERR){
    baseLed = 0;
  }
  if(status == PARSE_ERR){
    baseLed = 1;
  }

  if(status == AP_SETUP_ERR){
    baseLed = 4;
  }

  switch(phase % 4){
    case(0): setLed(true, baseLed, LEFT);break;
    case(1): setLed(true, baseLed, RIGHT);break;
    case(2): setLed(true, baseLed+1, RIGHT);break;
    case(3): setLed(true, baseLed+1, LEFT);break;

  }
}

void startAnimation(){
  for(int i = 0; i < 6; i ++){
    setLed(true, i,LEFT);
    setLed(true, i,RIGHT);
    delay(750);
    setLed(false, i,LEFT);
    setLed(false, i,RIGHT);
  }
}

void drawPmValue(){
      // The fraction of time that a single led should be powered
      // Number of milliseconds that a led should be on
      int cycletime = 5;
      for(int ms = 0; ms < 100; ms++){

        int msOn = (int) (cycletime * brightness / 1000);
        if(msOn > cycletime){
          showEncoding(mapState(pm25, barema25), LEFT);
          delay(cycletime);
        }
        if(msOn < 1){
          msOn = 1;
        }
        allLedsOff();
        delay(cycletime - msOn);
        showEncoding(mapState(pm25, barema25), LEFT);
        delay(msOn);


        allLedsOff();
        delay(cycletime - msOn);
        showEncoding(mapState(pm10, barema10), RIGHT);
        delay(msOn);
        updateBrightness();
    }
 }

void animate(int seconds){

    if(status != UP_TO_DATE) {
        showError(status, seconds);
    }else{
        drawPmValue();
    }

}

