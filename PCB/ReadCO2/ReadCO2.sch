EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ReadCO2"
Date ""
Rev "3"
Comp "HTL Wiener Neustadt"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v2.x A1
U 1 1 5F5E1216
P 6400 2800
F 0 "A1" H 6400 1711 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 6400 1620 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6400 2800 50  0001 C CIN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 6400 2800 50  0001 C CNN
	1    6400 2800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5F5E1F1D
P 2400 1650
F 0 "J3" H 2318 1225 50  0000 C CNN
F 1 "Conn_01x04" H 2318 1316 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 2400 1650 50  0001 C CNN
F 3 "~" H 2400 1650 50  0001 C CNN
	1    2400 1650
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 5F5E273C
P 1050 1550
F 0 "J1" H 968 1125 50  0000 C CNN
F 1 "Conn_01x05" H 968 1216 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 1050 1550 50  0001 C CNN
F 3 "~" H 1050 1550 50  0001 C CNN
	1    1050 1550
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5F5E2E85
P 1100 3000
F 0 "J2" H 1018 2675 50  0000 C CNN
F 1 "Conn_01x03" H 1018 2766 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1100 3000 50  0001 C CNN
F 3 "~" H 1100 3000 50  0001 C CNN
	1    1100 3000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5F5E3197
P 1650 4350
F 0 "R1" H 1720 4396 50  0000 L CNN
F 1 "R" H 1720 4305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 1580 4350 50  0001 C CNN
F 3 "~" H 1650 4350 50  0001 C CNN
	1    1650 4350
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Optical:LDR03 R2
U 1 1 5F5E3471
P 1650 4650
F 0 "R2" H 1720 4696 50  0000 L CNN
F 1 "LDR03" H 1720 4605 50  0000 L CNN
F 2 "OptoDevice:R_LDR_10x8.5mm_P7.6mm_Vertical" V 1825 4650 50  0001 C CNN
F 3 "http://www.elektronica-componenten.nl/WebRoot/StoreNL/Shops/61422969/54F1/BA0C/C664/31B9/2173/C0A8/2AB9/2AEF/LDR03IMP.pdf" H 1650 4600 50  0001 C CNN
	1    1650 4650
	1    0    0    -1  
$EndComp
Wire Notes Line
	850  950  3050 950 
Wire Notes Line
	3050 950  3050 2150
Wire Notes Line
	3050 2150 850  2150
Wire Notes Line
	850  2150 850  950 
Text Notes 950  2100 0    50   ~ 0
MH-Z19B
Wire Notes Line
	850  2600 3050 2600
Wire Notes Line
	3050 2600 3050 3500
Wire Notes Line
	3050 3500 850  3500
Wire Notes Line
	850  3500 850  2600
Text Notes 1000 3450 0    50   ~ 0
LED-Stripe
Wire Notes Line
	900  4000 3050 4000
Wire Notes Line
	3050 4000 3050 5000
Wire Notes Line
	3050 5000 900  5000
Wire Notes Line
	900  5000 900  4000
Text Notes 950  4950 0    50   ~ 0
light sensor
$Comp
L power:GND #PWR0101
U 1 1 5F5E69A3
P 1650 4800
F 0 "#PWR0101" H 1650 4550 50  0001 C CNN
F 1 "GND" H 1655 4627 50  0000 C CNN
F 2 "" H 1650 4800 50  0001 C CNN
F 3 "" H 1650 4800 50  0001 C CNN
	1    1650 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5F5E6E6D
P 1300 3100
F 0 "#PWR0102" H 1300 2850 50  0001 C CNN
F 1 "GND" H 1305 2927 50  0000 C CNN
F 2 "" H 1300 3100 50  0001 C CNN
F 3 "" H 1300 3100 50  0001 C CNN
	1    1300 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5F5E76B2
P 2600 1650
F 0 "#PWR0103" H 2600 1400 50  0001 C CNN
F 1 "GND" H 2605 1477 50  0000 C CNN
F 2 "" H 2600 1650 50  0001 C CNN
F 3 "" H 2600 1650 50  0001 C CNN
	1    2600 1650
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5F5E7CED
P 2600 1750
F 0 "#PWR0104" H 2600 1600 50  0001 C CNN
F 1 "+5V" V 2615 1878 50  0000 L CNN
F 2 "" H 2600 1750 50  0001 C CNN
F 3 "" H 2600 1750 50  0001 C CNN
	1    2600 1750
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5F5E8C9A
P 1300 2900
F 0 "#PWR0105" H 1300 2750 50  0001 C CNN
F 1 "+5V" H 1315 3073 50  0000 C CNN
F 2 "" H 1300 2900 50  0001 C CNN
F 3 "" H 1300 2900 50  0001 C CNN
	1    1300 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5F5E916D
P 1650 4200
F 0 "#PWR0106" H 1650 4050 50  0001 C CNN
F 1 "+5V" H 1665 4373 50  0000 C CNN
F 2 "" H 1650 4200 50  0001 C CNN
F 3 "" H 1650 4200 50  0001 C CNN
	1    1650 4200
	1    0    0    -1  
$EndComp
Text GLabel 1650 4500 2    50   Input ~ 0
light_sense
Text GLabel 1300 3000 2    50   Input ~ 0
LED_DIn
Text GLabel 1250 1650 2    50   Input ~ 0
CO2RX_uCTX
Text GLabel 1250 1550 2    50   Input ~ 0
CO2TX_uCRX
Text GLabel 6900 3500 2    50   Input ~ 0
light_sense
Text GLabel 5900 2400 0    50   Input ~ 0
LED_DIn
Text GLabel 5900 3300 0    50   Input ~ 0
CO2RX_uCTX
Text GLabel 5900 3200 0    50   Input ~ 0
CO2TX_uCRX
$Comp
L power:+5V #PWR0107
U 1 1 5F5EAE09
P 6600 1800
F 0 "#PWR0107" H 6600 1650 50  0001 C CNN
F 1 "+5V" H 6615 1973 50  0000 C CNN
F 2 "" H 6600 1800 50  0001 C CNN
F 3 "" H 6600 1800 50  0001 C CNN
	1    6600 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5F5EB29E
P 6500 3800
F 0 "#PWR0108" H 6500 3550 50  0001 C CNN
F 1 "GND" H 6505 3627 50  0000 C CNN
F 2 "" H 6500 3800 50  0001 C CNN
F 3 "" H 6500 3800 50  0001 C CNN
	1    6500 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5F5EB98C
P 6400 3800
F 0 "#PWR0109" H 6400 3550 50  0001 C CNN
F 1 "GND" H 6405 3627 50  0000 C CNN
F 2 "" H 6400 3800 50  0001 C CNN
F 3 "" H 6400 3800 50  0001 C CNN
	1    6400 3800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
