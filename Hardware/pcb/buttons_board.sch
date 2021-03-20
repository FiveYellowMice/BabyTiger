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
L power:GND #PWR?
U 1 1 602BA980
P 4050 3500
F 0 "#PWR?" H 4050 3250 50  0001 C CNN
F 1 "GND" H 4055 3327 50  0000 C CNN
F 2 "" H 4050 3500 50  0001 C CNN
F 3 "" H 4050 3500 50  0001 C CNN
	1    4050 3500
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 602BB4A2
P 7450 3700
F 0 "SW1" H 7450 3985 50  0000 C CNN
F 1 "BTN_L" H 7450 3894 50  0000 C CNN
F 2 "" H 7450 3900 50  0001 C CNN
F 3 "~" H 7450 3900 50  0001 C CNN
	1    7450 3700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 602BBA77
P 6650 3700
F 0 "SW2" H 6650 3985 50  0000 C CNN
F 1 "BTN_X" H 6650 3894 50  0000 C CNN
F 2 "" H 6650 3900 50  0001 C CNN
F 3 "~" H 6650 3900 50  0001 C CNN
	1    6650 3700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 602BBD8F
P 5850 3700
F 0 "SW3" H 5850 3985 50  0000 C CNN
F 1 "BTN_O" H 5850 3894 50  0000 C CNN
F 2 "" H 5850 3900 50  0001 C CNN
F 3 "~" H 5850 3900 50  0001 C CNN
	1    5850 3700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 602BC02B
P 5050 3700
F 0 "SW4" H 5050 3985 50  0000 C CNN
F 1 "BTN_R" H 5050 3894 50  0000 C CNN
F 2 "" H 5050 3900 50  0001 C CNN
F 3 "~" H 5050 3900 50  0001 C CNN
	1    5050 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 602BFF78
P 7250 3950
F 0 "C1" H 7365 3996 50  0000 L CNN
F 1 "0.1µF" H 7365 3905 50  0000 L CNN
F 2 "" H 7288 3800 50  0001 C CNN
F 3 "~" H 7250 3950 50  0001 C CNN
	1    7250 3950
	1    0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 602C055D
P 6450 3950
F 0 "C2" H 6565 3996 50  0000 L CNN
F 1 "0.1µF" H 6565 3905 50  0000 L CNN
F 2 "" H 6488 3800 50  0001 C CNN
F 3 "~" H 6450 3950 50  0001 C CNN
	1    6450 3950
	1    0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 602C0787
P 5650 3950
F 0 "C3" H 5765 3996 50  0000 L CNN
F 1 "0.1µF" H 5765 3905 50  0000 L CNN
F 2 "" H 5688 3800 50  0001 C CNN
F 3 "~" H 5650 3950 50  0001 C CNN
	1    5650 3950
	1    0    0    1   
$EndComp
$Comp
L Device:C C4
U 1 1 602C0953
P 4850 3950
F 0 "C4" H 4965 3996 50  0000 L CNN
F 1 "0.1µF" H 4965 3905 50  0000 L CNN
F 2 "" H 4888 3800 50  0001 C CNN
F 3 "~" H 4850 3950 50  0001 C CNN
	1    4850 3950
	1    0    0    1   
$EndComp
Wire Wire Line
	7250 3350 7250 3700
Wire Wire Line
	6450 3350 6450 3700
Wire Wire Line
	5650 3350 5650 3700
Wire Wire Line
	4850 3350 4850 3700
$Comp
L Device:R R3
U 1 1 602C8FDE
P 7650 4300
F 0 "R3" H 7580 4254 50  0000 R CNN
F 1 "6.6kΩ" H 7580 4345 50  0000 R CNN
F 2 "" V 7580 4300 50  0001 C CNN
F 3 "~" H 7650 4300 50  0001 C CNN
	1    7650 4300
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 602C9658
P 4100 4150
F 0 "R2" H 4170 4196 50  0000 L CNN
F 1 "1kΩ" H 4170 4105 50  0000 L CNN
F 2 "" V 4030 4150 50  0001 C CNN
F 3 "~" H 4100 4150 50  0001 C CNN
	1    4100 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 602C9C88
P 4450 4450
F 0 "R1" V 4243 4450 50  0000 C CNN
F 1 "10kΩ" V 4334 4450 50  0000 C CNN
F 2 "" V 4380 4450 50  0001 C CNN
F 3 "~" H 4450 4450 50  0001 C CNN
	1    4450 4450
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 602CF2E9
P 7250 3150
F 0 "J1" V 7214 3230 50  0000 L CNN
F 1 "Conn_BTN_L" V 7123 3230 50  0000 L CNN
F 2 "" H 7250 3150 50  0001 C CNN
F 3 "~" H 7250 3150 50  0001 C CNN
	1    7250 3150
	0    1    -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 602CFD88
P 6450 3150
F 0 "J2" V 6414 3230 50  0000 L CNN
F 1 "Conn_BTN_X" V 6323 3230 50  0000 L CNN
F 2 "" H 6450 3150 50  0001 C CNN
F 3 "~" H 6450 3150 50  0001 C CNN
	1    6450 3150
	0    1    -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 602D01C5
P 5650 3150
F 0 "J3" V 5614 3230 50  0000 L CNN
F 1 "Conn_BTN_O" V 5523 3230 50  0000 L CNN
F 2 "" H 5650 3150 50  0001 C CNN
F 3 "~" H 5650 3150 50  0001 C CNN
	1    5650 3150
	0    1    -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 602D068E
P 4850 3150
F 0 "J4" V 4814 3230 50  0000 L CNN
F 1 "Conn_BTN_R" V 4723 3230 50  0000 L CNN
F 2 "" H 4850 3150 50  0001 C CNN
F 3 "~" H 4850 3150 50  0001 C CNN
	1    4850 3150
	0    1    -1   0   
$EndComp
Wire Wire Line
	7250 3700 7250 3800
Connection ~ 7250 3700
Wire Wire Line
	6450 3700 6450 3800
Connection ~ 6450 3700
Wire Wire Line
	5650 3700 5650 3800
Connection ~ 5650 3700
Wire Wire Line
	4850 3700 4850 3800
Connection ~ 4850 3700
Wire Wire Line
	7650 3700 7650 4150
Wire Wire Line
	6850 3700 6850 4450
Wire Wire Line
	6850 4450 6050 4450
Wire Wire Line
	5250 3700 5250 4450
Connection ~ 5250 4450
Wire Wire Line
	5250 4450 4600 4450
Wire Wire Line
	6050 3700 6050 4450
Connection ~ 6050 4450
Wire Wire Line
	6050 4450 5250 4450
Wire Wire Line
	4300 4450 4100 4450
Wire Wire Line
	4100 4450 4100 4300
Wire Wire Line
	7650 4450 7650 4600
Wire Wire Line
	7650 4600 3950 4600
Wire Wire Line
	3950 4600 3950 3850
Wire Wire Line
	3950 3850 4100 3850
Wire Wire Line
	4100 3850 4100 4000
Wire Wire Line
	4450 4150 4850 4150
Wire Wire Line
	7250 4150 7250 4100
Wire Wire Line
	6450 4100 6450 4150
Connection ~ 6450 4150
Wire Wire Line
	6450 4150 7250 4150
Wire Wire Line
	5650 4100 5650 4150
Connection ~ 5650 4150
Wire Wire Line
	5650 4150 6450 4150
Wire Wire Line
	4850 4100 4850 4150
Connection ~ 4850 4150
Wire Wire Line
	4850 4150 5650 4150
Wire Wire Line
	4450 4150 4450 3850
Wire Wire Line
	4450 3850 4100 3850
Connection ~ 4100 3850
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 60314298
P 4100 3150
F 0 "J5" V 4064 3062 50  0000 R CNN
F 1 "Conn_GND" V 3973 3062 50  0000 R CNN
F 2 "" H 4100 3150 50  0001 C CNN
F 3 "~" H 4100 3150 50  0001 C CNN
	1    4100 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 3350 4100 3500
Wire Wire Line
	4050 3500 4100 3500
Connection ~ 4100 3500
Wire Wire Line
	4100 3500 4100 3850
$EndSCHEMATC