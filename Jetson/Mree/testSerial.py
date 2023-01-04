#!/usr/bin/python3.7

import serial
with serial.Serial('/dev/ttyACM0', 9600, timeout=10) as ser:  
    ser.write(str.encode('POSES'))
    while True:
        line = str(ser.readline()).lstrip('b').rstrip('\'').lstrip('\'')
        line = line.rstrip('\\n').rstrip('\\r').rstrip(' ')
        line = str(line)
        print(line)
