#!/usr/bin/python3.7

import serial
with serial.Serial('/dev/ttyACM0', 9600, timeout=10) as ser:  
    while True:
        print(ser.readline())
