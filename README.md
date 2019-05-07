# Luchtlichtje

Source code and hardware spec of the ESP8266 driven Air Quality Indicator "Luchtlichtje" (Dutch for 'air light')

A small ESP/Arduino Project, showing lights indicating the air quality, based on data from luftdaten.info

## API

Get your sensor data at http://api.luftdaten.info/v1/sensor/7245/


## Flashing a Luchtlichtje

- Download the latest arduino IDE
- Open 'File -> Preferences', add "http://arduino.esp8266.com/stable/package_esp8266com_index.json" to the field "Additional board manager URLs"
- Open 'Tools -> Board -> Boards Manager'
- Once loaded, search for 'ESP' in the bar in the right-upper-hand
- Click esp8266 by "ESP8266 community", install version 2.3.0 (_not_ latest!)
- With tools, select the right values. These are documented in the source code themselve
- Change the wifi network name, password and the ID of the sensor you want to follow
- Connect the ESP to your computer and click 'upload'


## Assembly instructions

- Start with placing the resistors. The resistor 'R1'-Brightness takes the XXX-ohm resistor, the other three have 220-ohm resistors.
- Next, place the leds. Be carefull, they have to be oriented correctly: the flattened sides go in the middle. Green leds down, red leds up - just like traffic lights. Solder them neatly and straight.
- Place and solder the header pins on the backside of the board.
- Flash the software on the nodemcu and place it on the backside.
- Gently break the board along the cutlines on the right. If they don't come off, use a knife on the back side of the board.
- These small rectangular break-off pieces can be slided in the main board, to place it on your desk.
- The break-off parts easily fall of the board when lifted. To prevent this, place a piece of wire through the holes in the break-off part and the main board.
- All done! Enjoy your Luchtlichtje.


## Troubleshooting

When booting, the board will test all leds blinking from up to down.
If a led does not blink, check the soldering.
If more then the desired leds burn, some LEDS are soldered in the wrong direction.

If the orange leds start blinking one after another; the board is connecting to the wifi. This will always happen for a few seconds when booting.

If the reds leds are blinking, either luftdaten or your sensor is down. 
