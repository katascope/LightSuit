#!/usr/bin/python3.7

import serial

from posedb import PoseDB
pdb = PoseDB("poses.txt")
#quit()

with serial.Serial('/dev/ttyACM0', 9600, timeout=10) as ser:  
    ser.write(str.encode('POSES'))
    while True:
        line = str(ser.readline()).lstrip('b').rstrip('\'').lstrip('\'')
        line = line.rstrip('\\n').rstrip('\\r').rstrip(' ')
        line = str(line)
        if "POSE" in line:
            print(line+"\n")
            pdb.write(line)
        else:
            print("unk\n");
