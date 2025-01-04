#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h>
#include <EEPROM.h>


// SEARCH A SENSOR ON luftdaten.info
// CLICK IT
// LOOK FOR SENSOR ID IN THE TABLE APPEARING RIGHT
// FILL IT IN DURING INITAL WIFIMANAGER SETUP
// The new api is: https://data.sensor.community/airrohr/v1/filter/area={lat},{lon},{radius in KM}

String luftdaten_host = "data.sensor.community";
String luftdaten_path = "/airrohr/v1/sensor/";

// If you have a v2.0 board, put this to true
#define USE_BRIGHTNESS true

int last_update_time = 0;

void update_pm(int time) {
    if(sensor_id <= 0){
        status = HTTPS_ERR;
        return;
    }
    if(last_update_time != 0 && last_update_time + UPDATE_TIMEOUT >+ time){
        // still up to date
        return;
    }
    Serial.printf("Time to update! last update: %d, time: %d\n",last_update_time,time);
    Serial.printf("Attempting update. status is %d\n", status);
    if(update() == UP_TO_DATE){
        last_update_time = time + 1;
        status = UP_TO_DATE;
        return;
    }
    delay(250);
    Serial.write("Update failed\n");
}

// ----------------------------------------------------------- READ BRIGHTNESS -------------------------------------------


void updateBrightness(){
  int readBrightness = analogRead(BRIGHTNESS_PIN);
  // Serial.printf("Brightness read: %d current: %d\n", readBrightness, brightness);
  if(brightness > readBrightness){
    brightness -= 1;
  }else if (brightness < readBrightness){
    brightness += 1;
  }
}




// ------------------------------------------------------------- UPDATE DATA -------------------------------------------------


int update(){

  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("[HTTP] wifi ");
    Serial.print(" not connected...\n");
    return NOT_CONNECTED;
  }
  Serial.print("[HTTP] Wifi is connected: ");
  Serial.print(WiFi.status());
  Serial.print("\n\n");
  
  WiFiClient client; // Use an old-skool HTTP (not secure). Worst case: the wrong light burns

  if (!client.connect(luftdaten_host, 80)) {
    Serial.println("connection failed to host " + luftdaten_host + " on port 80; status is: "+client.status());
    return HTTPS_ERR;
  }

  String url = luftdaten_path + sensor_id + "/"; // Doesn't work without trailing slash
  Serial.println("Attempting to fetch the data; host is " + luftdaten_host + " ; path is "+url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + luftdaten_host + "\r\n" +
               "User-Agent: LUCHTLICHTJE pietervdvn@posteo.net\r\n" +
               "Connection: close\r\n\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
    client.readStringUntil('\n'); // Read the length and discard it
    String payload = client.readString();
    Serial.println("Got the payload");

    DynamicJsonDocument jsonDoc(10000);
    DeserializationError error = deserializeJson(jsonDoc, payload);

    if (error) {
        Serial.println("Failed to parse JSON "+payload);
        Serial.println(error.c_str());
        return PARSE_ERR;
    }

    JsonArray root = jsonDoc.as<JsonArray>();

    // TODO actually read values
    Serial.println("Parsing OK!");
      float newPm10 = (root[0]["sensordatavalues"][0]["value"].as<float>() + root[1]["sensordatavalues"][0]["value"].as<float>()) / 2;
      float newPm25 = (root[0]["sensordatavalues"][1]["value"].as<float>() + root[1]["sensordatavalues"][1]["value"].as<float>()) / 2;
      if(pm10 == 0 && pm25 == 0){
            pm10 = newPm10;
            pm25 = newPm25;
            Serial.printf("(Initial assignment) Read: %f, new value is %f\n", newPm10, pm10);
      }else{
          Serial.printf("Read: %f, old value is %f, ", newPm10, pm10);
            // The new value is calculated by taking into account the previous value as well, to have less effect of outliers
            // The shown sum equals n0/2 + n1/4 + n2/8 + n3/16 ... (the lowest index is the last measurement)
            pm10 = (newPm10 + pm10)/2.0;
            pm25 = (newPm25 + pm25)/2.0;
            Serial.printf("New value is %f\n", pm10);
      }
  Serial.printf("PM2.5: %d; PM10: %d\n",(int) pm25,(int) pm10);

  return UP_TO_DATE;
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

