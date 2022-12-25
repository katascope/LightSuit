#! /usr/bin/python3
import time
import Adafruit_SSD1306   # This is the driver chip for the Adafruit PiOLED
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import serial
import subprocess
import oled as oled

oled.OledInitialize()
tick = 0

with serial.Serial('/dev/ttyACM0', 9600, timeout=10) as ser:  
    ser.write(str.encode('ready\r\n'))
    while True:
        tick = tick + 1;

        line = ser.readline()
        print(line)
        oled.OledRender(tick,line)
    
        # 1.0 = 1 second; The divisor is the desired updates (frames) per second
        time.sleep(1.0/4)
