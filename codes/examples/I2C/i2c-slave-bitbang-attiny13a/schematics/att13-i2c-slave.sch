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
L Connector:Raspberry_Pi_2_3 J1
U 1 1 5EC873DB
P 3100 3600
F 0 "J1" H 3100 5081 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 3100 4990 50  0000 C CNN
F 2 "" H 3100 3600 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 3100 3600 50  0001 C CNN
	1    3100 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 5EC8CCDA
P 3000 1650
F 0 "#PWR02" H 3000 1500 50  0001 C CNN
F 1 "+5V" H 3015 1823 50  0000 C CNN
F 2 "" H 3000 1650 50  0001 C CNN
F 3 "" H 3000 1650 50  0001 C CNN
	1    3000 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5EC8E7AA
P 2700 5300
F 0 "#PWR01" H 2700 5050 50  0001 C CNN
F 1 "GND" H 2705 5127 50  0000 C CNN
F 2 "" H 2700 5300 50  0001 C CNN
F 3 "" H 2700 5300 50  0001 C CNN
	1    2700 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 4900 2700 5300
$Comp
L MCU_Microchip_ATtiny:ATtiny13-20PU U1
U 1 1 5EC8F1E2
P 6050 3450
F 0 "U1" H 5521 3496 50  0000 R CNN
F 1 "ATtiny13-20PU" H 5521 3405 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6050 3450 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc2535.pdf" H 6050 3450 50  0001 C CNN
	1    6050 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5EC90395
P 7550 4600
F 0 "D1" V 7589 4482 50  0000 R CNN
F 1 "LED1" V 7498 4482 50  0000 R CNN
F 2 "" H 7550 4600 50  0001 C CNN
F 3 "~" H 7550 4600 50  0001 C CNN
	1    7550 4600
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D2
U 1 1 5EC9258F
P 8200 4600
F 0 "D2" V 8239 4482 50  0000 R CNN
F 1 "LED2" V 8148 4482 50  0000 R CNN
F 2 "" H 8200 4600 50  0001 C CNN
F 3 "~" H 8200 4600 50  0001 C CNN
	1    8200 4600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5EC93D22
P 7550 5250
F 0 "#PWR07" H 7550 5000 50  0001 C CNN
F 1 "GND" H 7555 5077 50  0000 C CNN
F 2 "" H 7550 5250 50  0001 C CNN
F 3 "" H 7550 5250 50  0001 C CNN
	1    7550 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4750 7550 5250
$Comp
L power:GND #PWR010
U 1 1 5EC94B4A
P 8200 5250
F 0 "#PWR010" H 8200 5000 50  0001 C CNN
F 1 "GND" H 8205 5077 50  0000 C CNN
F 2 "" H 8200 5250 50  0001 C CNN
F 3 "" H 8200 5250 50  0001 C CNN
	1    8200 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 4750 8200 5250
$Comp
L Device:R R1
U 1 1 5EC94E66
P 7550 4100
F 0 "R1" H 7620 4146 50  0000 L CNN
F 1 "1K" H 7620 4055 50  0000 L CNN
F 2 "" V 7480 4100 50  0001 C CNN
F 3 "~" H 7550 4100 50  0001 C CNN
	1    7550 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5EC95ACB
P 8200 4100
F 0 "R2" H 8270 4146 50  0000 L CNN
F 1 "1K" H 8270 4055 50  0000 L CNN
F 2 "" V 8130 4100 50  0001 C CNN
F 3 "~" H 8200 4100 50  0001 C CNN
	1    8200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4250 7550 4450
Wire Wire Line
	8200 4250 8200 4450
Wire Wire Line
	7550 3150 7550 3950
Wire Wire Line
	6650 3450 8200 3450
Wire Wire Line
	8200 3450 8200 3950
Wire Wire Line
	4300 3000 3900 3000
$Comp
L power:+5V #PWR05
U 1 1 5EC985B8
P 6050 1650
F 0 "#PWR05" H 6050 1500 50  0001 C CNN
F 1 "+5V" H 6065 1823 50  0000 C CNN
F 2 "" H 6050 1650 50  0001 C CNN
F 3 "" H 6050 1650 50  0001 C CNN
	1    6050 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1650 6050 2850
$Comp
L power:GND #PWR06
U 1 1 5EC99188
P 6050 5300
F 0 "#PWR06" H 6050 5050 50  0001 C CNN
F 1 "GND" H 6055 5127 50  0000 C CNN
F 2 "" H 6050 5300 50  0001 C CNN
F 3 "" H 6050 5300 50  0001 C CNN
	1    6050 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 4050 6050 5300
$Comp
L power:GND #PWR04
U 1 1 5EC9997F
P 4450 5300
F 0 "#PWR04" H 4450 5050 50  0001 C CNN
F 1 "GND" H 4455 5127 50  0000 C CNN
F 2 "" H 4450 5300 50  0001 C CNN
F 3 "" H 4450 5300 50  0001 C CNN
	1    4450 5300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5EC9A298
P 4450 4900
F 0 "#PWR03" H 4450 4750 50  0001 C CNN
F 1 "+5V" H 4465 5073 50  0000 C CNN
F 2 "" H 4450 4900 50  0001 C CNN
F 3 "" H 4450 4900 50  0001 C CNN
	1    4450 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5EC9AD86
P 4450 5100
F 0 "C1" H 4565 5146 50  0000 L CNN
F 1 "0.1u" H 4565 5055 50  0000 L CNN
F 2 "" H 4488 4950 50  0001 C CNN
F 3 "~" H 4450 5100 50  0001 C CNN
	1    4450 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 4900 4450 4950
Wire Wire Line
	4450 5250 4450 5300
$Comp
L Connector:AVR-ISP-6 J2
U 1 1 5EC9C59E
P 7700 2150
F 0 "J2" H 7370 2246 50  0000 R CNN
F 1 "AVR-ISP-6" H 7370 2155 50  0000 R CNN
F 2 "" V 7450 2200 50  0001 C CNN
F 3 " ~" H 6425 1600 50  0001 C CNN
	1    7700 2150
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 5ECA29EF
P 7800 1650
F 0 "#PWR08" H 7800 1500 50  0001 C CNN
F 1 "+5V" H 7815 1823 50  0000 C CNN
F 2 "" H 7800 1650 50  0001 C CNN
F 3 "" H 7800 1650 50  0001 C CNN
	1    7800 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3350 6900 3350
Wire Wire Line
	6650 3150 6800 3150
Wire Wire Line
	6650 3250 6700 3250
$Comp
L power:GND #PWR09
U 1 1 5ECA8AF1
P 7800 2550
F 0 "#PWR09" H 7800 2300 50  0001 C CNN
F 1 "GND" H 7805 2377 50  0000 C CNN
F 2 "" H 7800 2550 50  0001 C CNN
F 3 "" H 7800 2550 50  0001 C CNN
	1    7800 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 1950 6700 1950
Wire Wire Line
	6700 1950 6700 3250
Connection ~ 6700 3250
Wire Wire Line
	6700 3250 7400 3250
Wire Wire Line
	7300 2050 6800 2050
Wire Wire Line
	6800 2050 6800 3150
Connection ~ 6800 3150
Wire Wire Line
	6800 3150 7550 3150
Wire Wire Line
	7300 2150 6900 2150
Wire Wire Line
	6900 2150 6900 3350
Wire Wire Line
	7300 2250 7000 2250
Wire Wire Line
	7000 2250 7000 3650
Wire Wire Line
	6650 3650 7000 3650
Wire Wire Line
	7400 3250 7400 2550
Wire Wire Line
	7400 2550 4300 2550
Wire Wire Line
	4300 2550 4300 3000
Wire Wire Line
	6900 3350 7300 3350
Wire Wire Line
	7300 3350 7300 2650
Wire Wire Line
	7300 2650 4400 2650
Wire Wire Line
	4400 2650 4400 3100
Wire Wire Line
	3900 3100 4400 3100
Connection ~ 6900 3350
Wire Wire Line
	3000 1650 3000 2300
$EndSCHEMATC
