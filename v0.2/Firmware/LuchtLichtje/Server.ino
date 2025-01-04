#define timeoutTime 2000 
unsigned int previousTime = 0;
unsigned int currentTime = 0;


String parseQueryParam(String key, String queryParams){
    key = key + "="; // Add "=" in order to prevent a bigger key to accidentally contain a small key
    int startIndex = queryParams.indexOf(key);
    if(startIndex == -1){
        return "";
    }
    startIndex += key.length();
    queryParams = queryParams.substring(startIndex);
    int endIndex = queryParams.indexOf("&");
    queryParams = queryParams.substring(0, endIndex);
	queryParams.replace("%20", " ");
	


    return queryParams;     
}
bool parseQueryParamString(String key, String queryParams, String* assignto){
    String qp = parseQueryParam(key, queryParams);
    if(qp.length() == 0){
        return false;
    }
    Serial.print("Read and assigned ");
    Serial.print(key);
    *assignto = qp;
    return true;
}


bool parseQueryParamInt(String key, String queryParams, int* assignto){
    String qp = parseQueryParam(key, queryParams);
    if(qp.length() == 0){
        return false;
    }
    Serial.print("Read and assigned ");
    Serial.print(key);
    *assignto = qp.toInt();
    return true;
}

bool parseQueryParamUInt(String key, String queryParams, unsigned int* assignto){
    String qp = parseQueryParam(key, queryParams);
    if(qp.length() == 0){
        return false;
    }
    int uint = qp.toInt();
    if(uint < 0){
        uint = 0;
    }
    *assignto = uint;
    Serial.print("Read and assigned ");
    Serial.print(key);
    Serial.print(": ");
    Serial.println(*assignto);
    return true;  
}

void configure(String qp){
        Serial.println("Configuring...");
        Serial.println(qp);
        
        parseQueryParamInt("sensor", qp, &sensor_id);
      	writeIntToEEProm(SENSOR_ID_LOCATION, sensor_id);
      	Serial.printf("New sensor id is %d\n",sensor_id);
      	pm10 = 0;
      	pm25 = 0;
        last_update_time = 0;
                
        if(parseQueryParamString("ssid", qp, &wifi_ssid)){
            parseQueryParamString("password", qp, &wifi_password);
            parseQueryParamString("hostname", qp, &hostname);
            
            writeStringToEEPROM(WIFI_SSID_LOCATION, wifi_ssid);
            writeStringToEEPROM(WIFI_PASSWORD_LOCATION, wifi_password);
            writeStringToEEPROM(HOSTNAME_LOCATION, hostname);
            Serial.println("Wifi credentials saved into EEProm");
            
            setupWifi();
        }
}

void sendResponse(String path, WiFiClient client){
    if(path.startsWith("configure?")){
       configure(path.substring(path.indexOf("?") + 1));
       client.println("Config OK");
       return;
    }


    
    if(path.startsWith("manifest")){
        client.println(manifest);
        return;
    }

    if(path.startsWith("status")){
        client.println("{");
        client.print("\"ip\":\"");
        client.print(WiFi.localIP());
        client.println("\",");

        client.print("\"wifi\":\"");
        client.print(wifi_ssid);
        client.println("\",");

        client.print("\"wifi_2\":\"");
        client.print(wifi_ssid_2);
        client.println("\",");

        client.print("\"hostname\":\"");
        client.print(hostname);
        client.println("\"");

        client.print("\"sensorid\": ");
        client.printf("%d\n", sensor_id);

        client.print("\"brightness\": ");
        client.printf("%d,\n", brightness);

        client.print("\"sensorid\": ");
        client.printf("%d,\n", sensor_id);

        client.print("\"last_update_time\": ");
        client.printf("%d,\n", last_update_time);

        client.print("\"time'\": ");
        client.printf("%d\n", time);

        client.println("}");

        return;
    }
    if(path.startsWith("logo.svg")){
        client.println(logo);
        return;
    }

    if(mode == ACCESS_POINT_MODE || path.startsWith("setup")){
        client.println(wifiselect);
        return;
    }

    client.println(landing);
}

void handleClient(WiFiClient client){
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    String path = "";
    
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        
        if (c == '\n') {                    // if the byte is a newline character
        
          Serial.print(">");
          Serial.println(currentLine);   
          
          if(currentLine.startsWith("GET")){
            path = currentLine.substring(5);
            path = path.substring(0, path.indexOf(" "));
            Serial.print("Path is: ");
            Serial.println(path);
          }
        
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            if(path.startsWith("manifest")){
                client.println("Content-type:application/json");
            }else{
                client.println("Content-type:text/html");
            }
            client.println("Access-Control-Allow-Origin: *");
            client.println("Connection: close");
            client.println();
            
            sendResponse(path, client);
            
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    currentLine = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}

