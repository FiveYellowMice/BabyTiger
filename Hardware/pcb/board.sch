EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L custom:NodeMCU_DevKit_v2 U1
U 1 1 602B83B4
P 3000 4250
F 0 "U1" H 3000 5615 50  0000 C CNN
F 1 "NodeMCU_DevKit_v2" H 3000 5524 50  0000 C CNN
F 2 "custom:NodeMCU_DevKit_v2" H 3000 4250 50  0001 C CNN
F 3 "" H 3000 4250 50  0001 C CNN
	1    3000 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 602F942A
P 1600 5750
F 0 "#PWR0101" H 1600 5600 50  0001 C CNN
F 1 "+5V" V 1615 5878 50  0000 L CNN
F 2 "" H 1600 5750 50  0001 C CNN
F 3 "" H 1600 5750 50  0001 C CNN
	1    1600 5750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 4900 2100 4900
Wire Wire Line
	2100 4900 2100 5750
Connection ~ 2100 5750
$Comp
L power:GND #PWR0102
U 1 1 602FD8A0
P 1950 4800
F 0 "#PWR0102" H 1950 4550 50  0001 C CNN
F 1 "GND" V 1955 4672 50  0000 R CNN
F 2 "" H 1950 4800 50  0001 C CNN
F 3 "" H 1950 4800 50  0001 C CNN
	1    1950 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	2350 4800 1950 4800
$Comp
L custom:Arduino_Nano U2
U 1 1 6030D120
P 8750 4650
F 0 "U2" H 8750 5665 50  0000 C CNN
F 1 "Arduino_Nano" H 8750 5574 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 8750 4650 50  0001 C CNN
F 3 "" H 8750 4650 50  0001 C CNN
	1    8750 4650
	1    0    0    -1  
$EndComp
$Comp
L custom:BME280_Breakout U6
U 1 1 6030E985
P 5000 2600
F 0 "U6" H 5228 2588 50  0000 L CNN
F 1 "BME280_Breakout" H 5228 2497 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5000 2600 50  0001 C CNN
F 3 "" H 5000 2600 50  0001 C CNN
	1    5000 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2950 4850 4900
$Comp
L power:GND #PWR0103
U 1 1 6031C348
P 4950 3050
F 0 "#PWR0103" H 4950 2800 50  0001 C CNN
F 1 "GND" H 4955 2877 50  0000 C CNN
F 2 "" H 4950 3050 50  0001 C CNN
F 3 "" H 4950 3050 50  0001 C CNN
	1    4950 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 2950 4950 3050
Wire Wire Line
	2100 5750 6450 5750
Wire Wire Line
	5900 3400 5550 3400
Wire Wire Line
	5550 4900 4850 4900
$Comp
L power:GND #PWR0104
U 1 1 60333E5F
P 5850 3500
F 0 "#PWR0104" H 5850 3250 50  0001 C CNN
F 1 "GND" V 5855 3372 50  0000 R CNN
F 2 "" H 5850 3500 50  0001 C CNN
F 3 "" H 5850 3500 50  0001 C CNN
	1    5850 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 3500 5900 3500
Connection ~ 4850 4900
Wire Wire Line
	3650 4900 4850 4900
$Comp
L custom:DS1307_Breakout U5
U 1 1 6034219D
P 7550 2000
F 0 "U5" H 8078 1988 50  0000 L CNN
F 1 "DS1307_Breakout" H 8078 1897 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 7550 2000 50  0001 C CNN
F 3 "" H 7550 2000 50  0001 C CNN
	1    7550 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3400 6950 3400
Connection ~ 6950 5750
Wire Wire Line
	6950 5750 7650 5750
$Comp
L power:GND #PWR0105
U 1 1 6034D8B0
P 6650 3500
F 0 "#PWR0105" H 6650 3250 50  0001 C CNN
F 1 "GND" V 6655 3372 50  0000 R CNN
F 2 "" H 6650 3500 50  0001 C CNN
F 3 "" H 6650 3500 50  0001 C CNN
	1    6650 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6650 3500 6600 3500
$Comp
L power:GND #PWR0106
U 1 1 6035464D
P 7750 3000
F 0 "#PWR0106" H 7750 2750 50  0001 C CNN
F 1 "GND" H 7755 2827 50  0000 C CNN
F 2 "" H 7750 3000 50  0001 C CNN
F 3 "" H 7750 3000 50  0001 C CNN
	1    7750 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 2900 7750 3000
Wire Wire Line
	7650 2900 7650 5750
Connection ~ 7650 5750
Wire Wire Line
	9400 4200 9400 5750
Wire Wire Line
	7650 5750 9400 5750
$Comp
L power:GND #PWR0107
U 1 1 6036CB1E
P 9250 4000
F 0 "#PWR0107" H 9250 3750 50  0001 C CNN
F 1 "GND" V 9255 3872 50  0000 R CNN
F 2 "" H 9250 4000 50  0001 C CNN
F 3 "" H 9250 4000 50  0001 C CNN
	1    9250 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9250 4000 9200 4000
$Comp
L custom:Generic_Bidirectional_LevelShifter U4
U 1 1 6030FF30
P 6250 3450
F 0 "U4" V 5775 3450 50  0000 C CNN
F 1 "Generic_Bidirectional_LevelShifter" V 5866 3450 50  0000 C CNN
F 2 "Package_DIP:DIP-12_W10.16mm" H 6250 3500 50  0001 C CNN
F 3 "" H 6250 3500 50  0001 C CNN
	1    6250 3450
	0    1    1    0   
$EndComp
$Comp
L Device:Buzzer BZ1
U 1 1 60379018
P 6200 4800
F 0 "BZ1" V 6251 4952 50  0000 L CNN
F 1 "Buzzer" V 6160 4952 50  0000 L CNN
F 2 "Buzzer_Beeper:MagneticBuzzer_ProSignal_ABT-410-RC" V 6175 4900 50  0001 C CNN
F 3 "~" V 6175 4900 50  0001 C CNN
	1    6200 4800
	0    1    -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 60383170
P 6200 5350
F 0 "R3" V 6407 5350 50  0000 C CNN
F 1 "15k??" V 6316 5350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6130 5350 50  0001 C CNN
F 3 "~" H 6200 5350 50  0001 C CNN
	1    6200 5350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 60383C71
P 4450 4500
F 0 "R2" V 4657 4500 50  0000 C CNN
F 1 "660??" V 4566 4500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4380 4500 50  0001 C CNN
F 3 "~" H 4450 4500 50  0001 C CNN
	1    4450 4500
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_BJT:BC549 Q1
U 1 1 60384DAC
P 4650 5250
F 0 "Q1" V 4885 5250 50  0000 C CNN
F 1 "BC549C" V 4976 5250 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4850 5175 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BC550-D.pdf" H 4650 5250 50  0001 L CNN
	1    4650 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 4500 4300 4500
Wire Wire Line
	4600 4500 4650 4500
Wire Wire Line
	4650 4500 4650 5050
Wire Wire Line
	6050 5350 5950 5350
Wire Wire Line
	6300 4900 6450 4900
Wire Wire Line
	6450 5350 6350 5350
Wire Wire Line
	6100 4900 5950 4900
Connection ~ 5950 5350
Wire Wire Line
	5950 5350 4850 5350
Wire Wire Line
	6450 5350 6450 5750
Connection ~ 6450 5350
Connection ~ 6450 5750
Wire Wire Line
	6450 5750 6950 5750
Wire Wire Line
	5950 4900 5950 5350
Wire Wire Line
	6450 4900 6450 5350
$Comp
L power:GND #PWR0108
U 1 1 603B2588
P 4300 5350
F 0 "#PWR0108" H 4300 5100 50  0001 C CNN
F 1 "GND" V 4305 5222 50  0000 R CNN
F 2 "" H 4300 5350 50  0001 C CNN
F 3 "" H 4300 5350 50  0001 C CNN
	1    4300 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 5350 4300 5350
$Comp
L custom:WS2818B_Matrix_16x16 U3
U 1 1 603B8365
P 9850 2600
F 0 "U3" H 10078 2588 50  0000 L CNN
F 1 "WS2818B_Matrix_16x16" H 10078 2497 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9850 2600 50  0001 C CNN
F 3 "" H 9850 2600 50  0001 C CNN
	1    9850 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 603C8D26
P 9750 3000
F 0 "#PWR0109" H 9750 2750 50  0001 C CNN
F 1 "GND" H 9755 2827 50  0000 C CNN
F 2 "" H 9750 3000 50  0001 C CNN
F 3 "" H 9750 3000 50  0001 C CNN
	1    9750 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 2900 9750 3000
Wire Wire Line
	9850 3250 9850 2900
Wire Wire Line
	8300 4600 8000 4600
Wire Wire Line
	8000 4050 8000 3250
Wire Wire Line
	8000 4600 8000 4350
$Comp
L Device:R R1
U 1 1 603CA427
P 8000 4200
F 0 "R1" H 8070 4246 50  0000 L CNN
F 1 "470??" H 8070 4155 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7930 4200 50  0001 C CNN
F 3 "~" H 8000 4200 50  0001 C CNN
	1    8000 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3250 9850 3250
$Comp
L Device:C C1
U 1 1 603FDB72
P 1650 6350
F 0 "C1" H 1765 6396 50  0000 L CNN
F 1 "1??F" H 1765 6305 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 1688 6200 50  0001 C CNN
F 3 "~" H 1650 6350 50  0001 C CNN
	1    1650 6350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3900 4200 3650 4200
Wire Wire Line
	4000 4300 3650 4300
Wire Wire Line
	4100 4400 3650 4400
$Comp
L Switch:SW_Push SW1
U 1 1 604FEC3B
P 5900 6350
F 0 "SW1" V 5946 6302 50  0000 R CNN
F 1 "RESET" V 5855 6302 50  0000 R CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 5900 6550 50  0001 C CNN
F 3 "~" H 5900 6550 50  0001 C CNN
	1    5900 6350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9200 4100 9300 4100
Wire Wire Line
	9300 4100 9300 6050
Wire Wire Line
	2350 4700 2250 4700
Wire Wire Line
	2250 4700 2250 6050
$Comp
L power:GND #PWR0116
U 1 1 60553502
P 5900 6600
F 0 "#PWR0116" H 5900 6350 50  0001 C CNN
F 1 "GND" H 5905 6427 50  0000 C CNN
F 2 "" H 5900 6600 50  0001 C CNN
F 3 "" H 5900 6600 50  0001 C CNN
	1    5900 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 6050 5900 6050
Wire Wire Line
	5900 6150 5900 6050
Connection ~ 5900 6050
Wire Wire Line
	5900 6050 9300 6050
Wire Wire Line
	5900 6550 5900 6600
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 60672AA5
P 2750 2150
F 0 "J1" V 2714 2430 50  0000 L CNN
F 1 "Conn_Buttons" V 2623 2430 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 2750 2150 50  0001 C CNN
F 3 "~" H 2750 2150 50  0001 C CNN
	1    2750 2150
	0    1    -1   0   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 6067351B
P 2550 2400
F 0 "#PWR0111" H 2550 2150 50  0001 C CNN
F 1 "GND" H 2555 2227 50  0000 C CNN
F 2 "" H 2550 2400 50  0001 C CNN
F 3 "" H 2550 2400 50  0001 C CNN
	1    2550 2400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2550 2350 2550 2400
Wire Wire Line
	2950 2350 2950 2750
Wire Wire Line
	2950 2750 2250 2750
Wire Wire Line
	2250 2750 2250 3800
Wire Wire Line
	2250 3800 2350 3800
Wire Wire Line
	4100 4400 4100 2450
Wire Wire Line
	4100 2450 2850 2450
Wire Wire Line
	2850 2450 2850 2350
Wire Wire Line
	2750 2350 2750 2550
Wire Wire Line
	2750 2550 4000 2550
Wire Wire Line
	4000 2550 4000 4300
Wire Wire Line
	3900 4200 3900 2650
Wire Wire Line
	3900 2650 2650 2650
Wire Wire Line
	2650 2650 2650 2350
$Comp
L Connector_Generic:Conn_01x01 GND1
U 1 1 606ACE9E
P 1450 6700
F 0 "GND1" V 1322 6780 50  0000 L CNN
F 1 "0V" V 1413 6780 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 1450 6700 50  0001 C CNN
F 3 "~" H 1450 6700 50  0001 C CNN
	1    1450 6700
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 VDD1
U 1 1 606AD4BD
P 1850 6700
F 0 "VDD1" V 1722 6780 50  0000 L CNN
F 1 "+5V" V 1813 6780 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 1850 6700 50  0001 C CNN
F 3 "~" H 1850 6700 50  0001 C CNN
	1    1850 6700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 606B81A3
P 1450 6150
F 0 "#PWR0110" H 1450 5900 50  0001 C CNN
F 1 "GND" H 1455 5977 50  0000 C CNN
F 2 "" H 1450 6150 50  0001 C CNN
F 3 "" H 1450 6150 50  0001 C CNN
	1    1450 6150
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 606B883A
P 1850 6150
F 0 "#PWR0112" H 1850 6000 50  0001 C CNN
F 1 "+5V" H 1865 6323 50  0000 C CNN
F 2 "" H 1850 6150 50  0001 C CNN
F 3 "" H 1850 6150 50  0001 C CNN
	1    1850 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 5750 2100 5750
Wire Wire Line
	1850 6150 1850 6350
Wire Wire Line
	1450 6150 1450 6350
Wire Wire Line
	1500 6350 1450 6350
Connection ~ 1450 6350
Wire Wire Line
	1450 6350 1450 6500
Wire Wire Line
	1800 6350 1850 6350
Connection ~ 1850 6350
Wire Wire Line
	1850 6350 1850 6500
Wire Wire Line
	3650 3600 5050 3600
Wire Wire Line
	5050 2950 5050 3600
Wire Wire Line
	5150 2950 5150 3700
Wire Wire Line
	3650 3700 5150 3700
Wire Wire Line
	5550 3400 5550 4900
Wire Wire Line
	6950 3400 6950 5750
Wire Wire Line
	5150 3700 5900 3700
Connection ~ 5150 3700
Wire Wire Line
	5050 3600 5900 3600
Connection ~ 5050 3600
Wire Wire Line
	6600 3700 7550 3700
Wire Wire Line
	7550 2900 7550 3700
Wire Wire Line
	6600 3600 7450 3600
Wire Wire Line
	7450 2900 7450 3600
Wire Wire Line
	7450 3600 9650 3600
Connection ~ 7450 3600
Wire Wire Line
	9400 4200 9200 4200
Connection ~ 9400 5750
Wire Wire Line
	9400 5750 9950 5750
Wire Wire Line
	7550 3700 9550 3700
Connection ~ 7550 3700
Wire Wire Line
	9950 2900 9950 5750
Wire Wire Line
	9650 3600 9650 4500
Wire Wire Line
	9650 4500 9200 4500
Wire Wire Line
	9550 4600 9200 4600
Wire Wire Line
	9550 3700 9550 4600
$EndSCHEMATC
