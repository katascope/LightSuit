#!/usr/bin/python3
import jetson.inference
import jetson.utils

import argparse
import sys
import os

#servos
from adafruit_servokit import ServoKit
import board
import busio
import time
import preeservos as servos
import select

if os.name == 'nt':
    print('NT version')
    import kbwin as kb
else:
    print('Linux version')
    import kblinux as kb

print("Pree Initializing...")
print("Wrists:" + str(servos.ServoWrists));
print("u - situp")
print("c - center")
print("w - wrists")
print("s - standup")
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

age = 0
ageStarted = time.time()
ageState = 0
ageFirstState =0
tick = 0
focus = ""
state = "waking"
WAIT = 10
loop = "none"
override = ""
activekb = True
numPeople = 0

def trackCentering(width,height,pplRects):
 minY = height
 minX = width
 maxX = 0
 for rect in pplRects:
  print(str(rect.Left) + " " + str(rect.Bottom) + " " + str(rect.Right) + " " + str(rect.Top))
  if (rect.Top < minY):
   minY = rect.Top
  if (rect.Left < minX):
   minX = rect.Left
  if (rect.Right > maxX):
   maxX = rect.Right

 print("Track:" + str(minY) + ":" + str(minX)+"/"+str(maxX))
 tiltY = 0
 if (minY > height/10):
  servos.ChangeFrontLeftWrist(10)
  servos.ChangeFrontRightWrist(10)
  tiltY = 1
 elif (minY == 0):
  servos.ChangeFrontLeftWrist(-10)
  servos.ChangeFrontRightWrist(-10)
  tiltY = -1

 print("MINY:" + str(minY) + " tilt: " + str(tiltY))

# process frames until the user exits
while True:
  # capture the next image
  img = input.Capture()

  if (activekb):
    os.system('clear')

  # detect objects in the image (with overlay)
  detections = net.Detect(img, overlay=opt.overlay)

  numPeople = 0
  pplRects = []
  for detection in detections:
    name = net.GetClassDesc(detection.ClassID)
    if (name == "person" or name == "dog" or name == "cat"):
      pplRects.append(detection)
      numPeople = numPeople + 1

  things = ""
  if (len(detections) > 0):
   for detection in detections:
    name = net.GetClassDesc(detection.ClassID)
    things = things + " " + name
   if (len(things) > 0):
    things = " (" + things + " )"
  
  tick = tick + 1
  #time.sleep(0.1)
  key = None
  age = int(time.time() - ageStarted)
  ageState = int(time.time() - ageFirstState)
  
  print("Pree age " +str(age)+ ", epoch="+str(tick) + ", " + state + "(" + str(ageState) + "/" + str(int(WAIT))+ "), sees " + str(numPeople) + " beings" + things + ", auto " + str(not activekb) + ", subloop " + loop + " " + focus + "."+ override + " eyes:" + str(img.width) + "," + str(img.height))

  #trackCentering(img.width, img.height, pplRects)
  #+ ", servos:" + servos.GetServoDescShort())
  #print("Servos:\n" + servos.GetServoDescLong())

  # render the image
  output.Render(img)

  # update the title bar
#output.SetStatus("{:s} | Network {:.0f} FPS".format(opt.network, net.GetNetworkFPS()))

  # print out performance info
#net.PrintProfilerTimes()

  # exit on input/output EOS
  if not input.IsStreaming() or not output.IsStreaming():
     break

  if (activekb):
   state = ""
   print("Servos:" + servos.GetServoDescShort())
   print("u - situp")
   print("d - sitdn")
   print("z - zero")
   print("c - coosh")
   print("v - coosh2")
   print("m - menacing")
   print("s - standup")
   print("e - bellyflop")
   print("` - autonomous")
   print("t - trot")
   print("1/2/3/4/5 - go dn/up")
   print("----Direct Commands----")
   print("w - select all wrists")
   print("a - select all arms")
   print("h - select all hips")
   print("fw/bw - select front/back wrists")
   print("lw/rw - select left/right wrists");
   print("fa/ba - select front/back arms")
   print("la/ra - select left/right arms");
   print("fh/bh - select front/back hips")
   print("lh/rh - select left/right hips");
   print("flw(uwd) - front left wrist up/mid/down")
   print("frw(uwd) - front right wrist up/mid/down")
   print("blw(uwd) - back left wrist up/mid/down")
   print("brw(uwd) - back right wrist up/mid/down")
   print("fla(uwd) - front left arm up/mid/down")
   print("fra(uwd) - front right arm up/mid/down")
   print("bla(uwd) - back left arm up/mid/down")
   print("bra(uwd) - back right arm up/mid/down")
   print("flh(uwd) - front left wrist up/mid/down")
   print("frh(uwd) - front right wrist up/mid/down")
   print("blh(uwd) - back left wrist up/mid/down")
   print("brh(uwd) - back right wrist up/mid/down")
   print("iop - tail")
   key = kb.kbfunc()
   if (key is not None and len (key) > 0):
    ch = key[0].upper()
    if (ch == 'Q'):
        exit()
    if (ch == '[' or ch == ']' or ch == ',' or ch == '.'):
        val = 10
        val2 = 10
        if (ch == ']'):
            val = -10
            val2 = -10
        if (ch == ','):
            val = 10
            val2 = -10
        if (ch == '.'):
            val = -10
            val2 = 10

        if (focus == "W"):
           servos.ChangeFrontLeftWrist(val)
           servos.ChangeBackLeftWrist(val)
           servos.ChangeFrontRightWrist(val2)
           servos.ChangeBackRightWrist(val2)
        if (focus == "A"):
           servos.ChangeFrontLeftArm(val)
           servos.ChangeBackLeftArm(val)
           servos.ChangeFrontRightArm(val2)
           servos.ChangeBackRightArm(val2)
        if (focus == "H"):
           servos.ChangeFrontLeftHip(val)
           servos.ChangeBackLeftHip(val)
           servos.ChangeFrontRightHip(val2)
           servos.ChangeBackRightHip(val2)

        if (focus == "LW"):
           servos.ChangeFrontLeftWrist(val)
           servos.ChangeBackLeftWrist(val)
        if (focus == "RW"):
           servos.ChangeFrontRightWrist(val)
           servos.ChangeBackRightWrist(val)
        if (focus == "LA"):
           servos.ChangeFrontLeftArm(val)
           servos.ChangeBackLeftArm(val)
        if (focus == "RA"):
           servos.ChangeFrontRightArm(val)
           servos.ChangeBackRightArm(val)
        if (focus == "LH"):
           servos.ChangeFrontLeftHip(val)
           servos.ChangeBackLeftHip(val)
        if (focus == "RH"):
           servos.ChangeFrontRightHip(val)
           servos.ChangeBackRightHip(val)

        if (focus == "FW"):
           servos.ChangeFrontLeftWrist(val)
           servos.ChangeFrontRightWrist(val)
        if (focus == "BW"):
           servos.ChangeBackLeftWrist(val)
           servos.ChangeBackRightWrist(val)
        if (focus == "FA"):
           servos.ChangeFrontLeftArm(val)
           servos.ChangeFrontRightArm(val)
        if (focus == "BA"):
           servos.ChangeBackLeftArm(val)
           servos.ChangeBackRightArm(val)
        if (focus == "FH"):
           servos.ChangeFrontLeftHip(val)
           servos.ChangeFrontRightHip(val)
        if (focus == "BH"):
           servos.ChangeBackLeftHip(val)
           servos.ChangeBackRightHip(val)

        if (focus == "FLW"):
           servos.ChangeFrontLeftWrist(val)
        if (focus == "FLA"):
           servos.ChangeFrontLeftArm(val)
        if (focus == "FLH"):
           servos.ChangeFrontLeftHip(val)
        if (focus == "FRW"):
           servos.ChangeFrontRightWrist(val)
        if (focus == "FRA"):
           servos.ChangeFrontRightArm(val)
        if (focus == "FRH"):
           servos.ChangeFrontRightHip(val)
        if (focus == "BLW"):
           servos.ChangeBackLeftWrist(val)
        if (focus == "BLA"):
           servos.ChangeBackLeftArm(val)
        if (focus == "BLH"):
           servos.ChangeBackLeftHip(val)
        if (focus == "BRW"):
           servos.ChangeBackRightWrist(val)
        if (focus == "BRA"):
           servos.ChangeBackRightArm(val)
        if (focus == "BRH"):
           servos.ChangeBackRightHip(val)

    if (ch == 'W'):            
        focus = "W"
    if (ch == 'A'):
        focus = "A"
    if (ch == 'H'):
        focus = 'H'
    if (len(key) == 2 and ch == 'L' and key[1].upper() == 'W'):            
        focus = "LW"
    if (len(key) == 2 and ch == 'R' and key[1].upper() == 'W'):            
        focus = "RW"
    if (len(key) == 2 and ch == 'L' and key[1].upper() == 'A'):            
        focus = "LA"
    if (len(key) == 2 and ch == 'R' and key[1].upper() == 'A'):            
        focus = "RA"
    if (len(key) == 2 and ch == 'L' and key[1].upper() == 'H'):            
        focus = "LH"
    if (len(key) == 2 and ch == 'R' and key[1].upper() == 'H'):            
        focus = "RH"
    if (len(key) == 2 and ch == 'F' and key[1].upper() == 'W'):            
        focus = "FW"
    if (len(key) == 2 and ch == 'B' and key[1].upper() == 'W'):            
        focus = "BW"
    if (len(key) == 2 and ch == 'F' and key[1].upper() == 'A'):            
        focus = "FA"
    if (len(key) == 2 and ch == 'B' and key[1].upper() == 'A'):            
        focus = "BA"
    if (len(key) == 2 and ch == 'F' and key[1].upper() == 'H'):            
        focus = "FH"
    if (len(key) == 2 and ch == 'B' and key[1].upper() == 'H'):            
        focus = "BH"

    if (len(key) == 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'W'):            
        focus = "FLW"
    if (len(key) == 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'A'):            
        focus = "FLA"
    if (len(key) == 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'H'):            
        focus = "FLH"
    if (len(key) == 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'W'):            
        focus = "FRW"
    if (len(key) == 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'A'):            
        focus = "FRA"
    if (len(key) == 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'H'):            
        focus = "FRH"
    if (len(key) == 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'W'):            
        focus = "BLW"
    if (len(key) == 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'A'):            
        focus = "BLA"
    if (len(key) == 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'H'):            
        focus = "BLH"
    if (len(key) == 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'W'):            
        focus = "BRW"
    if (len(key) == 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'A'):            
        focus = "BRA"
    if (len(key) == 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'H'):            
        focus = "BRH"

    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'W' and key[3].upper() == 'U'):            
     servos.FrontLeftWristUp()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'W' and key[3].upper() == 'M'):            
     servos.FrontLeftWristMid()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'W' and key[3].upper() == 'D'):            
     servos.FrontLeftWristDown()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'W' and key[3].upper() == 'U'):            
     servos.FrontRightWristUp()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'W' and key[3].upper() == 'M'):            
     servos.FrontRightWristMid()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'W' and key[3].upper() == 'D'):            
     servos.FrontRightWristDown()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'W' and key[3].upper() == 'U'):            
     servos.BackLeftWristUp()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'W' and key[3].upper() == 'M'):            
     servos.BackLeftWristMid()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'W' and key[3].upper() == 'D'):            
     servos.BackLeftWristDown()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'W' and key[3].upper() == 'U'):            
     servos.BackRightWristUp()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'W' and key[3].upper() == 'M'):            
     servos.BackRightWristMid()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'W' and key[3].upper() == 'D'):            
     servos.BackRightWristDown()

    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'A' and key[3].upper() == 'U'):            
     servos.FrontLeftArmUp()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'A' and key[3].upper() == 'M'):            
     servos.FrontLeftArmMid()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'A' and key[3].upper() == 'D'):            
     servos.FrontLeftArmDown()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'A' and key[3].upper() == 'U'):            
     servos.BackLeftArmUp()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'A' and key[3].upper() == 'M'):            
     servos.BackLeftArmMid()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'A' and key[3].upper() == 'D'):            
     servos.BackLeftArmDown()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'A' and key[3].upper() == 'U'):            
     servos.FrontRightArmUp()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'A' and key[3].upper() == 'M'):            
     servos.FrontRightArmMid()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'A' and key[3].upper() == 'D'):            
     servos.FrontRightArmDown()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'A' and key[3].upper() == 'U'):            
     servos.BackRightArmUp()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'A' and key[3].upper() == 'M'):            
     servos.BackRightArmMid()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'A' and key[3].upper() == 'D'):            
     servos.BackRightArmDown()

    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'H' and key[3].upper() == 'U'):            
     servos.FrontLeftHipUp()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'H' and key[3].upper() == 'M'):            
     servos.FrontLeftHipMid()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'L' and key[2].upper() == 'H' and key[3].upper() == 'D'):            
     servos.FrontLeftHipDown()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'H' and key[3].upper() == 'U'):            
     servos.BackLeftHipUp()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'H' and key[3].upper() == 'M'):            
     servos.BackLeftHipMid()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'L' and key[2].upper() == 'H' and key[3].upper() == 'D'):            
     servos.BackLeftHipDown()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'H' and key[3].upper() == 'U'):            
     servos.FrontRightHipUp()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'H' and key[3].upper() == 'M'):            
     servos.FrontRightHipMid()
    if (len(key) > 3 and ch == 'F' and key[1].upper() == 'R' and key[2].upper() == 'H' and key[3].upper() == 'D'):            
     servos.FrontRightHipDown()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'H' and key[3].upper() == 'U'):            
     servos.BackRightHipUp()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'H' and key[3].upper() == 'M'):            
     servos.BackRightHipMid()
    if (len(key) > 3 and ch == 'B' and key[1].upper() == 'R' and key[2].upper() == 'H' and key[3].upper() == 'D'):            
     servos.BackRightHipDown()

    if (key[0].upper() == 'E'):            
     servos.PoseCode("39 159 119 139 19 59 39 159 59 139 19 119")
    if (key[0].upper() == 'M'):            
     servos.PoseCode("119 129 119 59 49 59 119 129 59 59 49 119")
    if (key[0].upper() == 'C'):            
     servos.PoseCode("48 158 88 128 18 88 38 158 88 139 18 88")

    zen = 1
    if (key[0].upper() == 'J'):
     servos.LerpScript(
     """48 158 88 128 18 88 38 158 88 139 18 88,1
     77 157 87 96 17 87 67 157 87 106 17 87,1
     96 135 86 74 36 86 86 135 86 84 36 86,1
     77 157 87 96 17 87 67 157 87 106 17 87,1
     48 158 88 128 18 88 38 158 88 139 18 88,1""")

    zen =0.2
    if (key[0].upper() == 'K'):
     servos.PoseCode("48 158 88 128 18 88 38 158 88 139 18 88")
     time.sleep(zen)
     servos.LerpCode("77 157 87 96 17 87 67 157 87 106 17 87",2)
     time.sleep(zen)
     servos.PoseCode("48 158 88 128 18 88 38 158 88 139 18 88")

    if (key[0].upper() == '1'):            
     servos.PoseCode("48 158 88 128 18 88 38 158 88 139 18 88")
    if (key[0].upper() == '2'):            
     servos.PoseCode("57 157 87 117 17 87 47 157 87 127 17 87")
    if (key[0].upper() == '3'):
     servos.PoseCode("67 157 87 106 17 87 57 157 87 116 17 87")
    if (key[0].upper() == '4'):
     servos.PoseCode("77 157 87 96 17 87 67 157 87 106 17 87")
    if (key[0].upper() == '5'):
     servos.PoseCode("96 135 86 74 36 86 86 135 86 84 36 86")
    if (key[0].upper() == '6'):
     servos.PoseCode("157 106 87 11 68 87 147 106 87 22 68 87")
    if (key[0].upper() == '0'):
     time.sleep(1)

    if (key[0].upper() == 'V'):            
     servos.PoseCoosh2()
    if (key[0].upper() == 'Z'):            
     servos.PoseZero()
    if (key[0].upper() == 'U'):
     servos.PoseSitUp()
    if (key[0].upper() == 'D'):
     servos.PoseSitDown()
    if (key[0].upper() == 'S'):
     servos.PoseStandUp()
    if (key[0].upper() == 'I'):
     servos.PoseTailDown()
    if (key[0].upper() == 'O'):
     servos.PoseTailMid()
    if (key[0].upper() == 'P'):
     servos.PoseTailUp()
    if (key[0].upper() == '`'):
     activekb = False
     state = "waking"
     ageState = 0
    if (key[0].upper() == 'T'):
     if (len(override) > 0):
      override = ""
     else:
      override = "trot"


  if (override == "trot"):
     if (int(tick) % 2== 0):
      servos.PoseCode("48 158 88 128 18 88 38 158 88 139 18 88")
     if (int(tick) % 2== 1):
      servos.PoseCode("77 157 87 96 17 87 67 157 87 106 17 87")


  if (state == "waking"):
    ageFirstState = time.time() 
    state = "lonely"
    servos.PoseHipsZero()
    servos.PoseCoosh()
    servos.PoseTailDown()
    ageState = 0

  if (state == "lonely"):
    if (ageState == 0):
      ageFirstState = time.time() - 1
      ageState = 1
      servos.PoseHipsZero()
      servos.PoseCoosh()
    ageExcited = 0
    servos.PoseTailDown()
    if (numPeople > 0):
      state = "excited"
      ageState = 0

  if (state == "centering"):
    if (ageState == 0):
      ageFirstState = time.time() - 1
      ageState = 1
      trackCentering()

  if (state == "excited"):
    if (ageState == 0):
      ageFirstState = time.time() - 1
      ageState = 1
    
    if ((int(ageState) % 2)== 0):
     servos.PoseTailMid()
    if ((int(ageState) % 2)== 1):
     servos.PoseTailDown()

    trackCentering(img.width, img.height, pplRects)
    if (ageState > WAIT):
      servos.PoseCoosh()
      state = "curious"
      ageState = 0
    #  servos.PoseSitDown()
    if (numPeople == 0):
      state = "lonely"
      servos.PoseCoosh()
      ageState = 0

  if (state == "curious"):
    if (ageState == 0):
      ageFirstState = time.time() - 1
      ageState = 1
    
    if ((int(ageState) % 2)== 0):
     servos.PoseTailUp()
     servos.PoseCoosh()
    if ((int(ageState) % 2)== 1):
     servos.PoseTailDown()
     servos.PoseCoosh2()

    if (ageState > WAIT):
      state = "active"
      ageState = 0
      servos.PoseZero()
    if (numPeople == 0):
      state = "lonely"
      ageState = 0

  if (state == "active"):
    if (ageState == 0):
      ageFirstState = time.time() - 1
      ageState = 1
      #servos.PoseZero()
      if (numPeople == 1):
        servos.PoseFrontLeftHipOut()
        time.sleep(1)
    
    if (numPeople == 1):
     loop = "paw_wave"
    if (numPeople == 2):
     loop = "paw_waves"
    if (numPeople > 2):
     loop = "see_people"
     #servos.PoseSitUp()

    if (loop == "paw_wave"):
     if ((int(ageState) % 2)== 0):
      servos.PoseWavePawFLUp()
     if ((int(ageState) % 2)== 1):
      servos.PoseWavePawFLMid()
    
    if (loop == "paw_waves"):
     if ((int(ageState) % 2)== 0):
      servos.PoseWavePawFLUp()
      servos.PoseWavePawFRUp()
     if ((int(ageState) % 2)== 1):
      servos.PoseWavePawFLMid()
      servos.PoseWavePawFRMid()
    if (loop == "see_people"):
     if (numPeople == 1):
      servos.PoseWavePawFLUp()
      servos.PoseWavePawFRMid()
      servos.PoseWavePawBLMid()
      servos.PoseWavePawBRMid()
     if (numPeople == 2):
      servos.PoseWavePawFRUp()
      servos.PoseWavePawBLMid()
      servos.PoseWavePawBRMid()
     if (numPeople == 3):
      servos.PoseWavePawBLUp()
      servos.PoseWavePawBRMid()
     if (numPeople > 3):
      servos.PoseWavePawBRUp()
    
    servos.PoseTailUp()
    
    if (numPeople == 0):
      servos.PoseWavePawFLMid()
      servos.PoseWavePawFRMid()
      servos.PoseWavePawBLMid()
      servos.PoseWavePawBRMid()
      servos.PoseSitDown()
      servos.PoseZero()
      state = "lonely"
      ageState = 0
    elif (ageState > WAIT):
      state = "rising"
      ageState = 0


  if (state == "rising"):
    if (ageState == 0):
      ageFirstState = time.time() - 1
      ageState = 1
      servos.PoseHipsZero()
      #servos.PoseSitUp()
      servos.PoseCode("56 157 87 115 17 87 56 157 87 115 17 87")#almost cooched
   
    if ((int(ageState) % 2)== 0):
     servos.PoseTailUp()
    if ((int(ageState) % 2)== 1):
     servos.PoseTailDown()

    if (ageState > WAIT):
     if (numPeople == 0):
      servos.PoseSitDown()
      servos.PoseZero()
      state = "lonely"
      ageState = 0
     else: 
      state = "standing"
      ageState = 0

  if (state == "standing"):
    if (ageState == 0):
      ageFirstState = time.time() - 1
      ageState = 1
      #servos.PoseHipsZero()
      #servos.PoseSitDown()
      servos.PoseCoosh()
      #servos.PoseCode("56 157 87 115 17 87 56 157 87 115 17 87")#almost cooched
      #servos.PoseCode("78 158 78 96 18 98 78 158 98 96 18 78")#risen position
    
    if ((int(ageState) % 2)== 0):
     servos.PoseTailUp()
    if ((int(ageState) % 2)== 1):
     servos.PoseTailDown()

    trackCentering(img.width, img.height, pplRects)

    if (ageState > WAIT):
     if (numPeople == 0):
      servos.PoseCode("56 157 87 115 17 87 56 157 87 115 17 87")#almost cooched
      servos.PoseCoosh()
      state = "lonely"
      ageState = 0







servos.DisableServos()

