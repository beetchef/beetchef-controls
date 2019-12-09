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
L Device:R R?
U 1 1 5DED73BC
P 2200 1800
F 0 "R?" V 2100 1800 50  0000 C CNN
F 1 "10K" V 2200 1800 50  0000 C CNN
F 2 "" V 2130 1800 50  0001 C CNN
F 3 "~" H 2200 1800 50  0001 C CNN
	1    2200 1800
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DED86E5
P 2650 1800
F 0 "R?" V 2550 1800 50  0000 C CNN
F 1 "10K" V 2650 1800 50  0000 C CNN
F 2 "" V 2580 1800 50  0001 C CNN
F 3 "~" H 2650 1800 50  0001 C CNN
	1    2650 1800
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DED8BE7
P 3300 2350
F 0 "R?" V 3200 2350 50  0000 C CNN
F 1 "10K" V 3300 2350 50  0000 C CNN
F 2 "" V 3230 2350 50  0001 C CNN
F 3 "~" H 3300 2350 50  0001 C CNN
	1    3300 2350
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5DEDADC4
P 2200 2350
F 0 "SW?" H 2200 2635 50  0000 C CNN
F 1 "SW_Push" H 2200 2544 50  0000 C CNN
F 2 "" H 2200 2550 50  0001 C CNN
F 3 "~" H 2200 2550 50  0001 C CNN
	1    2200 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1800 2500 1800
Wire Wire Line
	2050 1800 1850 1800
Wire Wire Line
	1850 1800 1850 2350
Wire Wire Line
	1850 2350 2000 2350
$Comp
L Switch:SW_Push SW?
U 1 1 5DEE3BBA
P 3300 1800
F 0 "SW?" H 3300 2085 50  0000 C CNN
F 1 "SW_Push" H 3300 1994 50  0000 C CNN
F 2 "" H 3300 2000 50  0001 C CNN
F 3 "~" H 3300 2000 50  0001 C CNN
	1    3300 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 1800 2950 1800
Wire Wire Line
	2400 2350 2950 2350
Wire Wire Line
	2950 1800 2950 2350
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
L power:GND #PWR?
U 1 1 5DEE751D
P 3600 2700
F 0 "#PWR?" H 3600 2450 50  0001 C CNN
F 1 "GND" H 3605 2527 50  0000 C CNN
F 2 "" H 3600 2700 50  0001 C CNN
F 3 "" H 3600 2700 50  0001 C CNN
	1    3600 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2700 3600 2350
Connection ~ 3600 2350
$Comp
L power:+5V #PWR?
U 1 1 5DEE8C0A
P 1850 2700
F 0 "#PWR?" H 1850 2550 50  0001 C CNN
F 1 "+5V" H 1865 2873 50  0000 C CNN
F 2 "" H 1850 2700 50  0001 C CNN
F 3 "" H 1850 2700 50  0001 C CNN
	1    1850 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	1850 2700 1850 2350
Connection ~ 1850 2350
$EndSCHEMATC