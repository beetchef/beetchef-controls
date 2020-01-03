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
L Device:R R3
U 1 1 5DED73BC
P 2150 1800
F 0 "R3" V 2050 1800 50  0000 C CNN
F 1 "10K" V 2150 1800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2080 1800 50  0001 C CNN
F 3 "~" H 2150 1800 50  0001 C CNN
	1    2150 1800
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5DED86E5
P 2650 1800
F 0 "R2" V 2550 1800 50  0000 C CNN
F 1 "10K" V 2650 1800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2580 1800 50  0001 C CNN
F 3 "~" H 2650 1800 50  0001 C CNN
	1    2650 1800
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5DED8BE7
P 3300 2350
F 0 "R1" V 3200 2350 50  0000 C CNN
F 1 "10K" V 3300 2350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3230 2350 50  0001 C CNN
F 3 "~" H 3300 2350 50  0001 C CNN
	1    3300 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	2300 1800 2500 1800
Wire Wire Line
	2000 1800 1850 1800
Wire Wire Line
	1850 1800 1850 2350
Wire Wire Line
	1850 2350 2200 2350
Wire Wire Line
	2800 1800 2950 1800
Wire Wire Line
	2600 2350 2950 2350
Connection ~ 2950 1800
Wire Wire Line
	2950 1800 3100 1800
Connection ~ 2950 2350
Wire Wire Line
	2950 2350 3150 2350
Wire Wire Line
	3500 1800 3600 1800
Wire Wire Line
	3600 1800 3600 2350
Wire Wire Line
	3600 2350 3450 2350
$Comp
L power:GND #PWR02
U 1 1 5DEE751D
P 3600 2950
F 0 "#PWR02" H 3600 2700 50  0001 C CNN
F 1 "GND" H 3605 2777 50  0000 C CNN
F 2 "" H 3600 2950 50  0001 C CNN
F 3 "" H 3600 2950 50  0001 C CNN
	1    3600 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2950 3600 2850
Connection ~ 3600 2350
Wire Wire Line
	1850 2950 1850 2850
Connection ~ 1850 2350
$Comp
L power:+5V #PWR01
U 1 1 5DEE8C0A
P 1850 2950
F 0 "#PWR01" H 1850 2800 50  0001 C CNN
F 1 "+5V" H 1865 3123 50  0000 C CNN
F 2 "" H 1850 2950 50  0001 C CNN
F 3 "" H 1850 2950 50  0001 C CNN
	1    1850 2950
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DEE799E
P 1950 2850
F 0 "#FLG0101" H 1950 2925 50  0001 C CNN
F 1 "PWR_FLAG" V 1950 2978 50  0000 L CNN
F 2 "" H 1950 2850 50  0001 C CNN
F 3 "~" H 1950 2850 50  0001 C CNN
	1    1950 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 2850 1850 2850
Connection ~ 1850 2850
Wire Wire Line
	1850 2850 1850 2600
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5DEE917C
P 3500 2850
F 0 "#FLG0102" H 3500 2925 50  0001 C CNN
F 1 "PWR_FLAG" V 3500 2977 50  0000 L CNN
F 2 "" H 3500 2850 50  0001 C CNN
F 3 "~" H 3500 2850 50  0001 C CNN
	1    3500 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 2850 3600 2850
Connection ~ 3600 2850
Wire Wire Line
	3600 2850 3600 2600
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 5DEEBFC9
P 2050 2600
F 0 "J1" H 2130 2642 50  0000 L CNN
F 1 "A0" H 2130 2551 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2050 2600 50  0001 C CNN
F 3 "~" H 2050 2600 50  0001 C CNN
	1    2050 2600
	1    0    0    -1  
$EndComp
Connection ~ 1850 2600
Wire Wire Line
	1850 2600 1850 2350
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5DEEE014
P 3400 2600
F 0 "J2" H 3550 2550 50  0000 C CNN
F 1 "GND" H 3550 2650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3400 2600 50  0001 C CNN
F 3 "~" H 3400 2600 50  0001 C CNN
	1    3400 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	2950 1800 2950 2350
Connection ~ 3600 2600
Wire Wire Line
	3600 2600 3600 2350
$Comp
L Switch:SW_Push SW1
U 1 1 5DEE3BBA
P 3300 1800
F 0 "SW1" H 3300 2085 50  0000 C CNN
F 1 "SW1" H 3300 1994 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3300 2000 50  0001 C CNN
F 3 "~" H 3300 2000 50  0001 C CNN
	1    3300 1800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5DEDADC4
P 2400 2350
F 0 "SW2" H 2400 2635 50  0000 C CNN
F 1 "SW2" H 2400 2544 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2400 2550 50  0001 C CNN
F 3 "~" H 2400 2550 50  0001 C CNN
	1    2400 2350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
