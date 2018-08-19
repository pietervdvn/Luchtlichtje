# Luchtlichtje
Source code of the ESP8266 driven Air Quality Indicator

A small ESP/Arduino Project, showing lights indicating the air quality.

Data comes from luftdaten.info


## Flashing a Luchtlichtje

- Download the latest arduino IDE
- Open 'File -> Preferences', add "http://arduino.esp8266.com/stable/package_esp8266com_index.json" to the field "Additional board manager URLs"
- Open 'Tools -> Board -> Boards Manager'
- Once loaded, search for 'ESP' in the bar in the right-upper-hand
- Click esp8266 by "ESP8266 community", install version 2.3.0 (_not_ latest!)
- With tools, select the right values. These are documented in the source code themselve
