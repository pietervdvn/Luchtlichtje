#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
// #include <ESP8266HTTPClient.h>

#include <math.h>
#include <ArduinoJson.h>

#include <EEPROM.h>


String Header;
// Set web server port number to 80
WiFiServer server(80);

String wifi_ssid = "";
String wifi_password = "";
String wifi_ssid_2 = "";
String wifi_password_2 = "";
String hostname = "luchtlichtje";

int sensor_id = 59878;

int status = 0 /*NOT_YET_LOADED*/;

#define ACCESS_POINT_MODE 1
int mode = 0;

void writeStringToEEPROM(int addrOffset, const String &strToWrite)
 {
    byte len = strToWrite.length();
    EEPROM.write(addrOffset, len);
    for (int i = 0; i < len; i++)
    {
        EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
    }
    EEPROM.commit();
    Serial.print("Written string to eeprom: index: ");
    Serial.print(addrOffset);
    Serial.print("; length: ");
    Serial.print(len);
 }
 
  void writeIntToEEProm(int addrOffset, int value)
  {
    byte len = 4;
    for(int i = 0; i < len; i++){
        EEPROM.write(addrOffset + i, value % 256);
        value = value / 256;
    }
    EEPROM.commit();
  }
  
    int readIntFromEEProm(int addrOffset)
    {
      byte len = 4;
      int value = 0;
      for(int i = 3; i >= 0; i--){
          value = value * 256;
          value += EEPROM.read(addrOffset + i);
      }
      return value;
    }
    
  
 
 String readStringFromEEPROM(int addrOffset) {
   int newStrLen = EEPROM.read(addrOffset);
   char data[newStrLen + 1];
   for (int i = 0; i < newStrLen; i++)
   {
     data[i] = EEPROM.read(addrOffset + 1 + i);
   }
   data[newStrLen] = '\0';
   return String(data);
 }



#define WIFI_SSID_LOCATION 10
#define WIFI_PASSWORD_LOCATION 265
#define HOSTNAME_LOCATION 522
#define WIFI_SSID_2_LOCATION 778
#define WIFI_PASSWORD_2_LOCATION 1034
#define SENSOR_ID_LOCATION 1290

void setup() {
    Serial.begin(115200);
    initLeds();
    startAnimation();


    /*
    * We save 5 strings of max 255 chars:
    * wifi_ssid (*2)
    * wifi_password (*2)
    * hostname
    *
    * Furthermore, we save a telltale-string at location 0 namely "traffic_light" in order to see if things are initialized already
    * At last, we save one extra int for the luftdaten-id
    */
    EEPROM.begin(256*5 + 10 + 4);
    delay(150);
    String telltale = readStringFromEEPROM(1);
    Serial.println("Telltale is:");
    Serial.println(telltale);
    if(telltale.length() == 7 && telltale.equals("rainbow")){
      sensor_id = readIntFromEEProm(SENSOR_ID_LOCATION);
      Serial.printf("This device has run the Luchtlichtje-light code before. Loaded sensor ID: %d\n", sensor_id);

    }else{
      Serial.println("Initializing EEPROM");
      writeStringToEEPROM(WIFI_SSID_LOCATION, "");
      writeStringToEEPROM(WIFI_PASSWORD_LOCATION, "");
      writeStringToEEPROM(WIFI_SSID_2_LOCATION, "");
      writeStringToEEPROM(WIFI_PASSWORD_2_LOCATION, "");
      writeStringToEEPROM(HOSTNAME_LOCATION, "luchtlichtje");
      writeIntToEEProm(SENSOR_ID_LOCATION, 0);

      writeStringToEEPROM(1, "rainbow");
      Serial.println("Init done");
    }
    setupWifi();
      // Set time via NTP, as required for x.509 validation
    if(WiFi.status() == WL_CONNECTED){
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    time_t now = time(nullptr);
    while (now < 1676426912) { // a random timestamp from the past
        Serial.println("Waiting for time to set correctly...");
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    Serial.print("Current time: ");
    Serial.print(asctime(&timeinfo));
    }

}

bool accessPointStarted = false;
void setupAccessPoint(){
    if(accessPointStarted){
        return;
    }
    accessPointStarted = true;
    mode = ACCESS_POINT_MODE;
    hostname = "luchtlichtje";
    WiFi.softAP(hostname+"_setup");
    server.begin();
    Serial.println("AP setup done. Connect on 192.168.4.1");
}


void attemptToConnectWith(String ssid, String password, int secondsToWait){
    if(ssid.length() == 0){
        return;
    }
    Serial.print("Attempting to connect to wifi ");
    Serial.println(ssid);
    WiFi.begin(ssid,password);
    int count = 10 * 60; //Attempt to connect for one minute
    int maxCount = count;
    unsigned long time = millis();
    unsigned long seconds = time / 1000;

    while (WiFi.status() != WL_CONNECTED && count >= 0) {
        delay(100);
        animate(seconds);
        count --;
        Serial.print(".");
        if(count % 100 == 0){
            Serial.print("\nAttempting to connect with ");
            Serial.print(wifi_ssid);
            Serial.print(" ");
            Serial.print(password);
            Serial.print(" (");
            Serial.print(count / 10);
            Serial.println(" seconds left)");
        }
    }
}

// Connect to Wi-Fi network with SSID and password
void setupWifi(){

    
    wifi_ssid = readStringFromEEPROM(WIFI_SSID_LOCATION);
    hostname = readStringFromEEPROM(HOSTNAME_LOCATION);
    WiFi.hostname(hostname);
    if(wifi_ssid != ""){
        wifi_password = readStringFromEEPROM(WIFI_PASSWORD_LOCATION);

        Serial.println("Trying primary wifi network: " + wifi_ssid);
        attemptToConnectWith(wifi_ssid, wifi_password, 20);
    }

    wifi_ssid_2 = readStringFromEEPROM(WIFI_SSID_2_LOCATION);
    if(wifi_ssid != "" &&  WiFi.status() != WL_CONNECTED){

        Serial.println("Trying secondary wifi network: " + wifi_ssid_2);
        wifi_password_2 = readStringFromEEPROM(WIFI_PASSWORD_2_LOCATION);
        attemptToConnectWith(wifi_ssid_2, wifi_password_2, 20);
    }

    if(WiFi.status() != WL_CONNECTED){
        // We reached a timeout
        Serial.println("Waiting for wifi connection: timeout. Using AP-mode");
        setupAccessPoint();
        return;
    }

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  mode = 0;
  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  AdvertiseServices();
  
  server.begin();

}


void loop(){
    unsigned long time = millis();
    unsigned long seconds = time / 1000;

    if(mode == ACCESS_POINT_MODE && (millis() / 1000) % 120 == 0){
        setupWifi();
        status = 5 /*AP_SETUP_ERR*/;
    }else{
        update_pm(seconds);
    }
    animate(seconds);
    handleClient(server.available());   // Listen for incoming clients
    MDNS.update();
}


void AdvertiseServices() {
   
   if (MDNS.begin(hostname))
   {
     // Add service to MDNS-SD
     MDNS.addService("http", "tcp", 80);
     MDNS.update(); 
     Serial.println("Local domain registered!");
   }
   
 }
 
