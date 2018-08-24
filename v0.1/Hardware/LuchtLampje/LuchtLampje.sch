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
LIBS:LuchtLampje-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Luchtlampje 1.0"
Date "2018-05-14"
Rev "0.1"
Comp "Pieter Vander Vennet"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED D1
U 1 1 5AF1F71B
P 3300 4600
F 0 "D1" H 3300 4700 50  0000 C CNN
F 1 "GREEN" H 3300 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3300 4600 50  0001 C CNN
F 3 "" H 3300 4600 50  0001 C CNN
	1    3300 4600
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X15 ESP_D1
U 1 1 5AF1F7A0
P 3350 2150
F 0 "ESP_D1" H 3350 2950 50  0000 C CNN
F 1 "CONN_01X15" V 3450 2150 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x15_Pitch2.54mm" H 3350 2150 50  0001 C CNN
F 3 "" H 3350 2150 50  0001 C CNN
	1    3350 2150
	-1   0    0    1   
$EndComp
$Comp
L POT RV1
U 1 1 5AF1F95F
P 6200 6350
F 0 "RV1" V 6025 6350 50  0000 C CNN
F 1 "POT 10K" V 6100 6350 50  0000 C CNN
F 2 "Potentiometers:Potentiometer_Trimmer_Piher_PT-6v_Horizontal_MountLS" H 6200 6350 50  0001 C CNN
F 3 "" H 6200 6350 50  0001 C CNN
	1    6200 6350
	1    0    0    -1  
$EndComp
Text Label 3700 2850 0    60   ~ 0
Arr2_Low
Text Label 3700 2750 0    60   ~ 0
Arr2_High
Text Label 3700 2550 0    60   ~ 0
Arr1_Low
Text Label 3700 2650 0    60   ~ 0
Arr1_High
Text Label 3700 2150 0    60   ~ 0
Green_Control
Text Label 3700 2050 0    60   ~ 0
Yellow_Control
Text Label 3700 1950 0    60   ~ 0
Red_Control
Text Label 4850 5750 1    60   ~ 0
Green_Control
$Comp
L LED D2
U 1 1 5AF37804
P 3700 4600
F 0 "D2" H 3700 4700 50  0000 C CNN
F 1 "GREEN" H 3700 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3700 4600 50  0001 C CNN
F 3 "" H 3700 4600 50  0001 C CNN
	1    3700 4600
	0    -1   -1   0   
$EndComp
$Comp
L LED D3
U 1 1 5AF3787E
P 4250 4600
F 0 "D3" H 4250 4700 50  0000 C CNN
F 1 "YELLOW" H 4250 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 4250 4600 50  0001 C CNN
F 3 "" H 4250 4600 50  0001 C CNN
	1    4250 4600
	0    -1   -1   0   
$EndComp
$Comp
L LED D4
U 1 1 5AF378BD
P 4700 4600
F 0 "D4" H 4700 4700 50  0000 C CNN
F 1 "YELLOW" H 4700 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 4700 4600 50  0001 C CNN
F 3 "" H 4700 4600 50  0001 C CNN
	1    4700 4600
	0    -1   -1   0   
$EndComp
$Comp
L Q_NPN_BCE Q2
U 1 1 5AF378EC
P 6100 5750
F 0 "Q2" H 6300 5800 50  0000 L CNN
F 1 "NPN_Green" H 6300 5700 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Wide" H 6300 5850 50  0001 C CNN
F 3 "" H 6100 5750 50  0001 C CNN
	1    6100 5750
	1    0    0    -1  
$EndComp
Text Label 5800 5750 1    60   ~ 0
Yellow_Control
$Comp
L LED D5
U 1 1 5AF37DF9
P 5250 4600
F 0 "D5" H 5250 4700 50  0000 C CNN
F 1 "RED" H 5250 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 5250 4600 50  0001 C CNN
F 3 "" H 5250 4600 50  0001 C CNN
	1    5250 4600
	0    -1   -1   0   
$EndComp
$Comp
L LED D6
U 1 1 5AF37E4C
P 5700 4600
F 0 "D6" H 5700 4700 50  0000 C CNN
F 1 "RED" H 5700 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 5700 4600 50  0001 C CNN
F 3 "" H 5700 4600 50  0001 C CNN
	1    5700 4600
	0    -1   -1   0   
$EndComp
$Comp
L Q_NPN_BCE Q3
U 1 1 5AF37F94
P 7100 5750
F 0 "Q3" H 7300 5800 50  0000 L CNN
F 1 "NPN_Green" H 7300 5700 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Wide" H 7300 5850 50  0001 C CNN
F 3 "" H 7100 5750 50  0001 C CNN
	1    7100 5750
	1    0    0    -1  
$EndComp
Text Label 6800 5750 1    60   ~ 0
Red_Control
Text Label 3300 4300 1    60   ~ 0
Arr1_High
Text Label 4250 4300 1    60   ~ 0
Arr1_High
Text Label 5250 4300 1    60   ~ 0
Arr1_High
Text Label 3700 4300 1    60   ~ 0
Arr1_Low
Text Label 4700 4300 1    60   ~ 0
Arr1_Low
Text Label 5700 4300 1    60   ~ 0
Arr1_Low
Wire Wire Line
	3700 2550 3550 2550
Wire Wire Line
	3700 2650 3550 2650
Wire Wire Line
	3700 2750 3550 2750
Wire Wire Line
	3700 2850 3550 2850
Wire Wire Line
	3600 1550 3550 1550
Wire Wire Line
	4850 5750 4950 5750
Wire Wire Line
	5250 5550 5250 5350
Wire Wire Line
	3300 4750 3700 4750
Connection ~ 3500 4750
Wire Wire Line
	6200 5200 6200 5550
Wire Wire Line
	4250 4750 4700 4750
Connection ~ 4450 4750
Wire Wire Line
	6200 5950 6200 6200
Wire Wire Line
	5800 5750 5900 5750
Wire Wire Line
	6800 5750 6900 5750
Wire Wire Line
	5250 4750 5700 4750
Wire Wire Line
	7200 5050 7200 5550
Connection ~ 5450 4750
Wire Wire Line
	7200 6050 7200 5950
Wire Wire Line
	5250 5950 5250 6050
Connection ~ 6200 6050
Wire Wire Line
	3300 4300 3300 4450
Wire Wire Line
	5250 4300 5250 4450
Wire Wire Line
	4250 4300 4250 4450
Wire Wire Line
	3700 4300 3700 4450
Wire Wire Line
	5700 4300 5700 4450
Wire Wire Line
	4700 4300 4700 4450
Wire Wire Line
	5250 6050 7200 6050
$Comp
L LED D7
U 1 1 5AF3A73A
P 6500 4600
F 0 "D7" H 6500 4700 50  0000 C CNN
F 1 "GREEN" H 6500 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 6500 4600 50  0001 C CNN
F 3 "" H 6500 4600 50  0001 C CNN
	1    6500 4600
	0    -1   -1   0   
$EndComp
$Comp
L LED D8
U 1 1 5AF3A749
P 6900 4600
F 0 "D8" H 6900 4700 50  0000 C CNN
F 1 "GREEN" H 6900 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 6900 4600 50  0001 C CNN
F 3 "" H 6900 4600 50  0001 C CNN
	1    6900 4600
	0    -1   -1   0   
$EndComp
$Comp
L LED D9
U 1 1 5AF3A750
P 7450 4600
F 0 "D9" H 7450 4700 50  0000 C CNN
F 1 "YELLOW" H 7450 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 7450 4600 50  0001 C CNN
F 3 "" H 7450 4600 50  0001 C CNN
	1    7450 4600
	0    -1   -1   0   
$EndComp
$Comp
L LED D10
U 1 1 5AF3A757
P 7900 4600
F 0 "D10" H 7900 4700 50  0000 C CNN
F 1 "YELLOW" H 7900 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 7900 4600 50  0001 C CNN
F 3 "" H 7900 4600 50  0001 C CNN
	1    7900 4600
	0    -1   -1   0   
$EndComp
$Comp
L LED D11
U 1 1 5AF3A766
P 8450 4600
F 0 "D11" H 8450 4700 50  0000 C CNN
F 1 "RED" H 8450 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 8450 4600 50  0001 C CNN
F 3 "" H 8450 4600 50  0001 C CNN
	1    8450 4600
	0    -1   -1   0   
$EndComp
$Comp
L LED D12
U 1 1 5AF3A76D
P 8900 4600
F 0 "D12" H 8900 4700 50  0000 C CNN
F 1 "RED" H 8900 4500 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 8900 4600 50  0001 C CNN
F 3 "" H 8900 4600 50  0001 C CNN
	1    8900 4600
	0    -1   -1   0   
$EndComp
Text Label 6500 4300 1    60   ~ 0
Arr2_High
Text Label 7450 4300 1    60   ~ 0
Arr2_High
Text Label 8450 4300 1    60   ~ 0
Arr2_High
Text Label 6900 4300 1    60   ~ 0
Arr2_Low
Text Label 7900 4300 1    60   ~ 0
Arr2_Low
Text Label 8900 4300 1    60   ~ 0
Arr2_Low
Wire Wire Line
	6500 4750 6900 4750
Connection ~ 6700 4750
Wire Wire Line
	7450 4750 7900 4750
Connection ~ 7650 4750
Wire Wire Line
	8450 4750 8900 4750
Connection ~ 8650 4750
Wire Wire Line
	6500 4300 6500 4450
Wire Wire Line
	8450 4300 8450 4450
Wire Wire Line
	7450 4300 7450 4450
Wire Wire Line
	6900 4300 6900 4450
Wire Wire Line
	8900 4300 8900 4450
Wire Wire Line
	7900 4300 7900 4450
Connection ~ 7200 6050
Wire Wire Line
	3550 1950 3700 1950
Wire Wire Line
	3700 2050 3550 2050
Wire Wire Line
	3550 2150 3700 2150
$Comp
L Q_NPN_BCE Q1
U 1 1 5AFA1E11
P 5150 5750
F 0 "Q1" H 5350 5800 50  0000 L CNN
F 1 "NPN_Green" H 5350 5700 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Wide" H 5350 5850 50  0001 C CNN
F 3 "" H 5150 5750 50  0001 C CNN
	1    5150 5750
	1    0    0    -1  
$EndComp
Text Label 3700 2350 0    60   ~ 0
3V
Text Label 3700 2250 0    60   ~ 0
GND
Wire Wire Line
	3550 2350 3700 2350
NoConn ~ 3550 2450
NoConn ~ 3550 1850
NoConn ~ 3550 1750
NoConn ~ 3550 1650
NoConn ~ 3550 1550
NoConn ~ 3550 1450
$Comp
L R R1
U 1 1 5AFA8D7F
P 6350 6500
F 0 "R1" V 6430 6500 50  0000 C CNN
F 1 "1K" V 6350 6500 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6280 6500 50  0001 C CNN
F 3 "" H 6350 6500 50  0001 C CNN
	1    6350 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2250 3700 2250
Text Label 6500 6650 0    60   ~ 0
GND
NoConn ~ 3700 2350
$Comp
L CONN_01X15 ESP_D2
U 1 1 5AFAB4F9
P 4700 2150
F 0 "ESP_D2" H 4700 2950 50  0000 C CNN
F 1 "CONN_01X15" V 4800 2150 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x15_Pitch2.54mm" H 4700 2150 50  0001 C CNN
F 3 "" H 4700 2150 50  0001 C CNN
	1    4700 2150
	-1   0    0    1   
$EndComp
NoConn ~ 4900 2850
NoConn ~ 4900 2750
NoConn ~ 4900 2650
NoConn ~ 4900 2550
NoConn ~ 4900 2450
NoConn ~ 4900 2350
NoConn ~ 4900 2250
NoConn ~ 4900 2150
NoConn ~ 4900 2050
NoConn ~ 4900 1950
NoConn ~ 4900 1850
NoConn ~ 4900 1750
NoConn ~ 4900 1650
NoConn ~ 4900 1550
NoConn ~ 4900 1450
Wire Wire Line
	3500 5350 6700 5350
Wire Wire Line
	3500 5350 3500 4750
Wire Wire Line
	4450 5200 7650 5200
Wire Wire Line
	4450 5200 4450 4750
Wire Wire Line
	5450 5050 8650 5050
Wire Wire Line
	5450 5050 5450 4750
Wire Wire Line
	6700 5350 6700 4750
Connection ~ 5250 5350
Wire Wire Line
	7650 5200 7650 4750
Connection ~ 6200 5200
Wire Wire Line
	8650 5050 8650 4750
Connection ~ 7200 5050
Wire Wire Line
	6500 6650 6350 6650
NoConn ~ 6200 6500
$EndSCHEMATC
