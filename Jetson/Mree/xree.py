#!/usr/bin/python3.7
import jetson.inference
import jetson.utils

import argparse
import sys
import os
import time

import time
import Adafruit_SSD1306   # This is the driver chip for the Adafruit PiOLED
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import serial
import subprocess
import oled as oled

from playsound import playsound
playsound("RobofoxSounds/StartUpEnd.mp3",0);

from posedb import PoseDB

tick = 0
pdb = PoseDB("poses.txt")

# parse the command line
parser = argparse.ArgumentParser(description="Locate objects in a live camera stream using an object detection DNN.",
                                 formatter_class=argparse.RawTextHelpFormatter, epilog=jetson.inference.detectNet.Usage() +
                                 jetson.utils.videoSource.Usage() + jetson.utils.videoOutput.Usage() + jetson.utils.logUsage())

parser.add_argument("input_URI", type=str, default="", nargs='?', help="URI of the input stream")
parser.add_argument("output_URI", type=str, default="", nargs='?', help="URI of the output stream")
parser.add_argument("--network", type=str, default="ssd-mobilenet-v2", help="pre-trained model to load (see below for options)")
parser.add_argument("--overlay", type=str, default="box,labels,conf", help="detection overlay flags (e.g. --overlay=box,labels,conf)\nvalid combinations are:  'box', 'labels', 'conf', 'none'")
parser.add_argument("--threshold", type=float, default=0.5, help="minimum detection threshold to use")

is_headless = ["--headless"] if sys.argv[0].find('console.py') != -1 else [""]

try:
  opt = parser.parse_known_args()[0]
except:
  print("")
  parser.print_help()
  sys.exit(0)

# load the object detection network
net = jetson.inference.detectNet(opt.network, sys.argv, opt.threshold)

# create video sources & outputs
input = jetson.utils.videoSource(opt.input_URI, argv=sys.argv)
output = jetson.utils.videoOutput(opt.output_URI, argv=sys.argv+is_headless)

lastPpl = 0;

pplSendTime = time.time()

with serial.Serial('/dev/ttyACM0', 9600, timeout=10) as ser:
# ser.write(str.encode('waking\r\n'))
 playsound("RobofoxSounds/Purr.mp3",0);
 img = input.Capture()
# ser.write(str.encode('ready\r\n'))
#playsound("Sounds/growl.mp3");

 ser.write(str.encode('auto\r\n'))

 while True:
  tick = tick + 1;

  while (ser.in_waiting):
    line = str(ser.readline())
    line = line.lstrip('B').lstrip('b').rstrip('\'').lstrip('\'')
    line = line.rstrip('\\n').rstrip('\\r').lstrip('b')
    line = line.lstrip('B')
    print("SERIAL:"+line)
    if "POSES" in line:
      pdb.write(line)
    if "SHiss" in line:
      playsound("RobofoxSounds/Gasp.mp3",0)
    if "SPu" in line:
      playsound("RobofoxSounds/Purr.mp3",0)
    if "Thun" in line:
      playsound("RobofoxSounds/Mumble.mp3",0)
    if "Bark" in line:
      playsound("RobofoxSounds/Alert.mp3",0)
    if "Nerv" in line:
      playsound("RobofoxSounds/Confused_Error.mp3",0)
    if "SHowl" in line:
      playsound("RobofoxSounds/Scream.mp3",0)
    if "SMeow" in line:
      playsound("RobofoxSounds/RoboMeow.mp3",0)
    if "SGrowl" in line:
      playsound("RobofoxSounds/Bored.mp3",0)
#   if "S*Hu" in line:
#     playsound("RobofoxSounds/Expression_1.mp3",0)
#   if "S*Hd" in line:
#     playsound("RobofoxSounds/Expression_2.mp3",0)
#   if "S*Wu" in line:
#     playsound("RobofoxSounds/Expression_3.mp3",0)
#   if "S*Wd" in line:
#     playsound("RobofoxSounds/Expression_4.mp3",0)
#   if "S*Eu" in line:
#     playsound("RobofoxSounds/Expression_5.mp3",0)
#   if "S*Ed" in line:
#     playsound("RobofoxSounds/Expression_6.mp3",0)

# 1.0 = 1 second; The divisor is the desired updates (frames) per second
  time.sleep(1.0/4)

# process frames until the user exits
#while True:
  # capture the next image
  img = input.Capture()

  os.system('clear')

  # detect objects in the image (with overlay)
  detections = net.Detect(img, overlay=opt.overlay)
  values = net.Detection()

  
  # print the detections
  print("detected {:d} objects in image".format(len(detections)))

  for detection in detections:
    name = net.GetClassDesc(detection.ClassID)
    print("Detect:"+str(detection.ClassID)+ " - " + name)

  numPeople = 0
  pplRects = []
  for detection in detections:
    name = net.GetClassDesc(detection.ClassID)
    if (name == "person" or name == "dog" or name == "cat"):
      pplRects.append(detection)
      numPeople = numPeople + 1

  print("People:"+str(numPeople))

  if ((time.time()-1) > pplSendTime):
   pplRect = {0,0,0,0};
   minX = 11
   minY = 11
   maxX = -1
   maxY = -1
   pplSendTime = time.time()      
   if (len(pplRects) > 0):
    for rect in pplRects:
     sx1 = int((rect.Left   / img.width)*9.9)
     sx2 = int((rect.Right  / img.width)*9.9) 
     sy1 = int((rect.Top    / img.height)*9.9)
     sy2 = int((rect.Bottom / img.height)*9.9)
     if (sx1 < minX):
       minX = sx1
     if (sx2 > maxX):
       maxX = sx2
     if (sy1 < minY):
       minY = sy1
     if (sy2 > maxY):
       maxY = sy2 
    s="!"+str(minX)+str(minY)+str(maxX)+str(maxY)+"\r\n";
   else:
    s="!0000\r\n";
   print("RectStr="+s);
   ser.write( str.encode(s) )

#   if (numPeople == 0):
#   lastPpl = numPeople
#   s="pl"+str(numPeople)
#   ser.write( str.encode(s+"\n") )
#   time.sleep(0.5)
#   ser.write( str.encode(s) )
#   print("sending ppl=" + s)

  # render the image
  output.Render(img)

  # update the title bar
#output.SetStatus("{:s} | Network {:.0f} FPS".format(opt.network, net.GetNetworkFPS()))

  # print out performance info
#net.PrintProfilerTimes()

  # exit on input/output EOS
  if not input.IsStreaming() or not output.IsStreaming():
   break



