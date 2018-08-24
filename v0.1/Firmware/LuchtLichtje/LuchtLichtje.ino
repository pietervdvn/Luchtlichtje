#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>

/** 
 * 2018-08-19 (Working for prototype version)
 * Use Arduino IDE
 * ESP8266 by ESP8266 Community v. 2.3.0
 * Board: NodeMCU (12E)
 * CPU Freq: 80Mhz
 * Flash size: 4M (3M SPiffs)
 * Upload speed: 115200
 */

// WIFI DETAILS


// TYPE YOUR WIFI SSID HERE:
#define WIFIAP "fri3d-legacy"
// TYPE YOUR WIFI PASSWORD HERE
#define WIFIPASS "fri3dcamp"
// SEARCH A SENSOR ON luftdaten.info
// CLICK IT
// LOOK FOR SENSOR ID IN THE TABLE APPEARING RIGHT
// CHANGE IT ON THE END (do not remove the trailing slash)
#define SENSOR "http://api.luftdaten.info/v1/sensor/12988/"





// Time between two updates, in minutes
#define UPDATE_TIMEOUT 15
// Time in seconds between retries when failed. Should be a multiple of 4
#define RETRY_TIMEOUT 12

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
// ---------------------- WIFI STUFF

ESP8266WiFiMulti WiFiMulti;

// -------------------------- Status tracking

#define CONNECTING 0
#define UP_TO_DATE 1

#define NOT_CONNECTED 2
#define HTTP_ERR 3
#define PARSE_ERR 4

// Color encodings
#define EXTREMELY_GOOD 0 // Double green
#define VERY_GOOD 1 // single, lowest green
#define GOOD 2 // single, highest green

#define LOW_AVG 3 // lowest yellow
#define AVG 4 // TWO_YELLOWS
#define HIGH_AVG 5 // Highest yellow

#define BAD 6 // lowest red
#define VERY_BAD 7// highest red
#define EXTREMELY_BAD 8// two red

#define OFF 9

#define USE_SERIAL Serial

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



// ------------------------------------------- MAIN PROGRAM --------------------------------


void setup() {
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFIAP, WIFIPASS);


 USE_SERIAL.begin(115200);

  initLeds(); 
  startAnimation();
}


void loop() {
  USE_SERIAL.println("Updating");
  float pm10, pm25;
  int status = NOT_CONNECTED;
  int retries = 8;
  while(status !=  UP_TO_DATE && retries > 0){
    USE_SERIAL.printf("Attempting update. %d retries left\n", retries);
    status = update(&pm10, &pm25);
    if(status != UP_TO_DATE){
      showError(status, 8-retries);
      delay(500);
    }
    retries --;
  }

  if(status != UP_TO_DATE){
    USE_SERIAL.write("Update failed\n");
    for(int i = 0; i < RETRY_TIMEOUT; i++){
      showError(status,i);
      delay(1000);
      USE_SERIAL.printf("Retrying in %d\n", RETRY_TIMEOUT - i);
    }    return;
  }

  USE_SERIAL.printf("PM2.5: %d; PM10: %d\n",(int) pm25,(int) pm10);
  // We are up to date. Lets show the bars!
  // We draw one of them, show it for 5ms and hide it again. Then, we show the other bar.
  // The inner loop does this 200 times (one second)

  allLedsOff();
 int m = 0; 
 for(int m = 0; m < UPDATE_TIMEOUT; m++){ 
    for(int s = 0; s < 60; s++){
      if(s % 15 == 0){
        USE_SERIAL.printf("Next update in %d:%2d\n", UPDATE_TIMEOUT - 1 - m, 60 - s);
      }
      for(int ms = 0; ms < 100; ms++){
        allLedsOff();
        showEncoding(mapState(pm25, barema25), LEFT);
        delay(5);
        allLedsOff();
        showEncoding(mapState(pm10, barema10), RIGHT);
        delay(5);
      }
    }
  }
  // Power both rails while updating...
  digitalWrite(LEFTH, HIGH);
  digitalWrite(LEFTL, HIGH);
  
}






// ------------------------------------------------------------- UPDATE DATA -------------------------------------------------


int update(float* pm10, float* pm25){
  if(WiFiMulti.run() != WL_CONNECTED) {
    USE_SERIAL.print("[HTTP] wifi not connected...\n");
    return NOT_CONNECTED;
  }
  
  HTTPClient http;

  USE_SERIAL.print("[HTTP] begin...\n");
  // configure server and sho
  http.begin(SENSOR);
   
  USE_SERIAL.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  USE_SERIAL.printf("[HTTP] Get Done \n");
  USE_SERIAL.printf("[HTTP] Get code is %d\n", httpCode);
  // httpCode will be negative on error
  if(httpCode <= 0) {
    USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    return HTTP_ERR;
  }

  // HTTP header has been send and Server response header has been handled
  USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

  // file not found at server or other problem
  if(httpCode != HTTP_CODE_OK) {
    USE_SERIAL.printf("[HTTP] GET... returned error status code: %d\n", httpCode);
    http.end();
    return HTTP_ERR;
  }
  
  String payload = http.getString();
  USE_SERIAL.println("Got the payload");
  StaticJsonBuffer<3000> jsonBuffer;
  JsonArray& root = jsonBuffer.parseArray(payload);
  if (!root[0].success()) {
    USE_SERIAL.println("parseObject() failed");
    USE_SERIAL.println(payload);
    return PARSE_ERR;
  }

  *pm10 = (root[0]["sensordatavalues"][0]["value"].as<float>() + root[1]["sensordatavalues"][0]["value"].as<float>())/2;
  *pm25 = (root[0]["sensordatavalues"][1]["value"].as<float>() + root[1]["sensordatavalues"][1]["value"].as<float>())/2;

  http.end();
  return UP_TO_DATE;
}

// Blinks the leds in an error-indicating sequence
// Takes 3 seconds to complete
void showError(int status, int phase){

  allLedsOff();
  int baseLed = 4;

  if(status == NOT_CONNECTED){
    baseLed = 2;
  }
  if(status == HTTP_ERR){
    baseLed = 0;
  }
  if(status == PARSE_ERR){
    baseLed = 1;
  }

  switch(phase % 4){
    case(0): setLed(true, baseLed, LEFT);break;
    case(1): setLed(true, baseLed, RIGHT);break;
    case(2): setLed(true, baseLed+1, RIGHT);break;
    case(3): setLed(true, baseLed+1, LEFT);break;
    
  }
}


// ----------------------------------------- LED CONTROL --------------------------------------------

/**
 * This function calculates the state of the PM, given the barema
 */
int mapState(float value, float* barema){
  for(int state = 1; state < OFF; state++){
    if(barema[state] > value){
       return state - 1;
    }
  }
  return EXTREMELY_BAD;
}



void showEncoding(int encoding, int series){
  switch(encoding){
    case(EXTREMELY_GOOD): setLed(true, 4, series); setLed(true, 5, series); break;
    case(VERY_GOOD): setLed(true, 5, series); break;
    case(GOOD): setLed(true, 4, series); break;
    
    case(LOW_AVG): setLed(true, 3, series); break;
    case(AVG): setLed(true, 3, series); setLed(true, 2, series); break;
    case(HIGH_AVG): setLed(true, 2, series); break;
    
    case(BAD): setLed(true, 1, series); break;
    case(VERY_BAD): setLed(true, 0, series); break;
    case(EXTREMELY_BAD): setLed(true, 0, series); setLed(true, 1, series); break;
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

void startAnimation(){
  for(int i = 0; i < 6; i ++){
    setLed(true, i,LEFT);
    setLed(true, i,RIGHT);
    delay(750);
    setLed(false, i,LEFT);
    setLed(false, i,RIGHT);
  }
}




