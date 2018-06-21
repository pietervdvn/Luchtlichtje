#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

int outputpins[9] = {D0, D1, D2, D3, D4, D5, D6, D7, D8};


int update(float* pm10, float* pm25){
  if(WiFiMulti.run() != WL_CONNECTED) {
    USE_SERIAL.print("[HTTP] wifi not connected...\n");
    return 3;
  }
  
  HTTPClient http;

  USE_SERIAL.print("[HTTP] begin...\n");
  // configure traged server and url
  http.begin("http://api.luftdaten.info/v1/sensor/7245/");
   
  USE_SERIAL.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode <= 0) {
    http.end();
    USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    return 1;
  }

  
  // HTTP header has been send and Server response header has been handled
  USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

  // file not found at server or other problem
  if(httpCode != HTTP_CODE_OK) {
    USE_SERIAL.printf("[HTTP] GET... returned error status code: %d\n", httpCode);
    http.end();
    return 2;
  }
  
  String payload = http.getString();
  USE_SERIAL.println("Got the payload");
  StaticJsonBuffer<2400> jsonBuffer;
  JsonArray& root = jsonBuffer.parseArray(payload);
  if (!root[0].success()) {
    USE_SERIAL.println("parseObject() failed");
    USE_SERIAL.println(payload);
    return 4;
  }

  *pm10 = (root[0]["sensordatavalues"][0]["value"].as<float>() + root[1]["sensordatavalues"][0]["value"].as<float>())/2;
  *pm25 = (root[0]["sensordatavalues"][1]["value"].as<float>() + root[1]["sensordatavalues"][1]["value"].as<float>())/2;

  http.end();
  return 0;
}

void setup() {
    USE_SERIAL.begin(9600);
    USE_SERIAL.println("Setting up");

    USE_SERIAL.println("ID is:");
    USE_SERIAL.println(ESP.getChipId());

    for(int i = 0; i < 9; i++){
      pinMode(outputpins[i], OUTPUT);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("keuken", "elfjuli9");
 
    delay(3000);
        
  
}

void loop() {
    int updateTimeoutMinutes = 15;

    USE_SERIAL.println("Updating");
    int status = 1;
    float pm10, pm25;
    int retries = 10;
    while(status !=  0 && retries > 0){
      status = update(&pm10, &pm25);
      if(status != 0){
        delay(1000);
      }
      USE_SERIAL.printf("Status is %d\n", status);
    }

    if(status != 0){
      USE_SERIAL.printf("Could not update");
       return;
    }
      
    
      
    // We are up to date. Lets show the bars!
    // We draw one of them, show it for 5ms and hide it again. Then, we show the other bar.
    // The inner loop does this 200 times (one second)

    USE_SERIAL.printf("Concentration of PM10 is %f, PM2.5 is %f\n", pm25, pm10);
    delay(60*60*10);
}


