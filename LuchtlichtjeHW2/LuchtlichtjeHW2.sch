EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:LuchtlichtjeHW2-cache
EELAYER 25 0
EELAYER END
$Descr A4 8268 11693 portrait
encoding utf-8
Sheet 1 1
Title "Luchtlichtje 1.1"
Date "2018-06-29"
Rev "0.2"
Comp "Pieter Vander Vennet"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X15 J?
U 1 1 5B363896
P 3150 3200
F 0 "J?" H 3150 4000 50  0000 C CNN
F 1 "CONN_01X15" V 3250 3200 50  0000 C CNN
F 2 "" H 3150 3200 50  0001 C CNN
F 3 "" H 3150 3200 50  0001 C CNN
	1    3150 3200
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X15 J?
U 1 1 5B363969
P 2700 3200
F 0 "J?" H 2700 4000 50  0000 C CNN
F 1 "CONN_01X15" V 2800 3200 50  0000 C CNN
F 2 "" H 2700 3200 50  0001 C CNN
F 3 "" H 2700 3200 50  0001 C CNN
	1    2700 3200
	1    0    0    -1  
$EndComp
Text Label 2350 2500 0    60   ~ 0
A0
Text Label 3500 3400 0    60   ~ 0
3V
Text Label 3500 3300 0    60   ~ 0
GND
Text Label 1650 2500 0    60   ~ 0
A0
Text Label 1600 2800 0    60   ~ 0
3V
Text Label 1600 3100 0    60   ~ 0
GND
$Comp
L R R?
U 1 1 5B363B65
P 1400 2950
F 0 "R?" V 1480 2950 50  0000 C CNN
F 1 "10K" V 1400 2950 50  0000 C CNN
F 2 "" V 1330 2950 50  0001 C CNN
F 3 "" H 1400 2950 50  0001 C CNN
	1    1400 2950
	1    0    0    -1  
$EndComp
$Comp
L R_PHOTO R?
U 1 1 5B363C10
P 1400 2650
F 0 "R?" H 1450 2700 50  0000 L CNN
F 1 "R_PHOTO" H 1450 2650 50  0000 L TNN
F 2 "" V 1450 2400 50  0001 L CNN
F 3 "" H 1400 2600 50  0001 C CNN
	1    1400 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2500 2500 2500
Wire Wire Line
	3500 3400 3350 3400
Wire Wire Line
	3500 3300 3350 3300
Wire Wire Line
	1400 2800 1600 2800
Wire Wire Line
	1600 3100 1400 3100
Wire Wire Line
	1400 2500 1650 2500
$EndSCHEMATC
