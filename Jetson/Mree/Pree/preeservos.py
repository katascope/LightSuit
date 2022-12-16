#!/usr/bin/python3

# SDA = pin.SDA_1
# SCL = pin.SCL_1
# SDA_1 = pin.SDA
# SCL_1 = pin.SCL

from adafruit_servokit import ServoKit
import board
import busio
import time
import sys

# On the Jetson Nano
# Bus 0 (pins 28,27) is board SCL_1, SDA_1 in the jetson board definition file
# Bus 1 (pins 5, 3) is board SCL, SDA in the jetson definition file
# Default is to Bus 1; We are using Bus 0, so we need to construct the busio first ...
print("Initializing Servos")
i2c_bus0=(busio.I2C(board.SCL_1, board.SDA_1))
print("Initializing Servos::ServoKit")
kit = ServoKit(channels=16, i2c=i2c_bus0)
kit.frequency = 60

#kit = ServoKit(channels=16, i2c=i2c_bus0)
# kit[0] is the bottom servo
# kit[1] is the top servo
print("Initializing Servos OK")

#for servo in servos :
#    print("Servo 1 = " + servo)

#for degree in sweep :
#    kit.servo[0].angle=degree
#    kit.servo[0].angle=degree
    # kit.servo[1].angle=degree
    # time.sleep(0.01)

SFrontLeftHip = 4
SFrontLeftArm = 5
SFrontLeftWrist = 6
SFrontRightHip = 8
SFrontRightArm = 9
SFrontRightWrist = 10
SBackLeftHip = 0
SBackLeftArm = 1
SBackLeftWrist = 2
SBackRightHip = 12
SBackRightArm = 13
SBackRightWrist = 14
STail = 15

ServoFrontLeft  = [ SFrontLeftWrist, SFrontLeftArm, SFrontLeftHip ]
ServoFrontRight = [ SFrontRightWrist, SFrontRightArm, SFrontRightHip ]
ServoBackLeft   = [ SBackLeftWrist, SBackLeftArm, SBackLeftHip ]
ServoBackRight  = [ SBackRightWrist, SBackRightArm, SBackRightHip ]

#ServoHips = [SFrontLeftHip, SFrontRightHip, SBackLeftHip, SBackRightHip]
#ervoHips = [SFrontLeftHip]
ServoAll = [
        SFrontLeftWrist,
        SFrontLeftArm,
        SFrontLeftHip,

        SFrontRightWrist,
        SFrontRightArm,
        SFrontRightHip,
        
        SBackLeftWrist,
        SBackLeftArm,
        SBackLeftHip,

        SBackRightWrist,
        SBackRightArm,
        SBackRightHip

        ]

ServoWrists = [SFrontLeftWrist, SBackLeftWrist]
ServoHips = [SFrontLeftHip, SFrontRightHip, SBackLeftHip, SBackRightHip]

#wrists 40 to 180 #Wrists 'center' at 150
#hips 30 to 140 #hips 'center' at ?
record = [90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90]

def GetServoDescLong():
 desc = " FrontLeft:\n"
 desc += "  H " + str(int(kit.servo[SFrontLeftHip].angle)) + "\n"
 desc += "  A " + str(int(kit.servo[SFrontLeftArm].angle)) + "\n"
 desc += "  W " + str(int(kit.servo[SFrontLeftWrist].angle)) + "\n"
 desc += " FrontRight:\n"
 desc += "  H " + str(int(kit.servo[SFrontRightHip].angle)) + "\n"
 desc += "  A " + str(int(kit.servo[SFrontRightArm].angle)) + "\n"
 desc += "  W " + str(int(kit.servo[SFrontRightWrist].angle)) + "\n"
 desc += " BackLeft:\n"
 desc += "  H " + str(int(kit.servo[SBackLeftHip].angle)) + "\n"
 desc += "  A " + str(int(kit.servo[SBackLeftArm].angle)) + "\n"
 desc += "  W " + str(int(kit.servo[SBackLeftWrist].angle)) + "\n"
 desc += " BackRight:\n"
 desc += "  H " + str(int(kit.servo[SBackRightHip].angle)) + "\n"
 desc += "  A " + str(int(kit.servo[SBackRightArm].angle)) + "\n"
 desc += "  W " + str(int(kit.servo[SBackRightWrist].angle)) + "\n"
 return desc

def GetServoDescShort():
 desc = ""
 for servo in ServoBackLeft:
  desc = desc + " " + str(int(kit.servo[servo].angle))
 for servo in ServoBackRight:
  desc = desc + " " + str(int(kit.servo[servo].angle))
 for servo in ServoFrontLeft:
  desc = desc + " " + str(int(kit.servo[servo].angle))
 for servo in ServoFrontRight:
  desc = desc + " " + str(int(kit.servo[servo].angle))
 return desc

def Set(servos,value):
 for servo in servos:
  kit.servo[servo].angle = value
  record[servo] = value

def Change(servos,value):
 for servo in servos:
  kit.servo[servo].angle += value
  if (kit.servo[servo].angle < 10):
    kit.servo[servo].angle = 30
  if (kit.servo[servo].angle > 160):
    kit.servo[servo].angle = 160
  record[servo] = kit.servo[servo].angle

def PoseCode(code):
 parts = code.split()
 Set([SBackLeftWrist],int(parts[0]))
 Set([SBackLeftArm],int(parts[1]))
 Set([SBackLeftHip],int(parts[2]))
 Set([SBackRightWrist],int(parts[3]))
 Set([SBackRightArm],int(parts[4]))
 Set([SBackRightHip],int(parts[5]))
 Set([SFrontLeftWrist],int(parts[6]))
 Set([SFrontLeftArm],int(parts[7]))
 Set([SFrontLeftHip],int(parts[8]))
 Set([SFrontRightWrist],int(parts[9]))
 Set([SFrontRightArm],int(parts[10]))
 Set([SFrontRightHip],int(parts[11]))

def GetServoDescShort():
 desc = ""
 for servo in ServoBackLeft:
  desc = desc + " " + str(int(kit.servo[servo].angle))
 for servo in ServoBackRight:
  desc = desc + " " + str(int(kit.servo[servo].angle))
 for servo in ServoFrontLeft:
  desc = desc + " " + str(int(kit.servo[servo].angle))
 for servo in ServoFrontRight:
  desc = desc + " " + str(int(kit.servo[servo].angle))
 return desc

def lerp(mux, v1, v2):
 return ((1 - mux) * v1 + mux* v2)

def Set(servos,value):
 for servo in servos:
  kit.servo[servo].angle = value
  record[servo] = value
#  time.sleep(0.1)

def Go(servos,value):
 stride = 1
 if (value < 90):
  stride = -1
 for servo in servos:
  for i in range(90,value,stride):
   kit.servo[servo].angle = value
   record[servo] = value

def LerpCode(code, ms):
 parts = code.split()
 toValues = [90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90]
 toValues[SBackLeftWrist]=int(parts[0])
 toValues[SBackLeftArm]=int(parts[1])
 toValues[SBackLeftHip]=int(parts[2])
 toValues[SBackRightWrist]=int(parts[3])
 toValues[SBackRightArm]=int(parts[4])
 toValues[SBackRightHip]=int(parts[5])
 toValues[SFrontLeftWrist]=int(parts[6])
 toValues[SFrontLeftArm]=int(parts[7])
 toValues[SFrontLeftHip]=int(parts[8])
 toValues[SFrontRightWrist]=int(parts[9])
 toValues[SFrontRightArm]=int(parts[10])
 toValues[SFrontRightHip]=int(parts[11])

 fromValues = [90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90]
 for servo in ServoAll:
   fromValues[servo] = record[servo]

 print("LerpCode:" + code+ " over " + str(ms))

 progress = 0
 for loop in range(ms*100):
  mux = loop / ms / 100
  for servo in ServoAll:
   lerpValue = lerp(mux,fromValues[servo],toValues[servo])
   kit.servo[servo].angle = lerpValue
   record[servo] = lerpValue
  time.sleep(0.01)

def LerpScript(script):
 lines = script.split('\n')
 for line in lines:
  parts = line.split(',')
  if (len(parts)==1): # no time
      print("Part:" + parts[0])
      #Set(parts[0])
  else:
   pose = parts[0]
   if (len(pose) < 5):
    time.sleep(int(parts[1]))
   else:
    print("Parts[0]="+parts[0]+"Parts1:"+parts[1]+"'")
    LerpCode(parts[0],int(parts[1]))


def Sweep():
  sweep = range(30,120)
  for servo in ServoHips: #range (0,16):
   print("Setting servo " + str(servo))
   kit.servo[servo].actuation_range = 600
   time.sleep(0.5)
   for degree in sweep :
    print(" sweep servo " + str(degree))
    kit.servo[servo].angle = degree
    record[servo] = value

def PoseZero():
    Set(ServoAll,90)

def PoseHipsZero():
    Set(ServoHips,90)

def PoseFrontLeftHipOut():
    Set([SFrontLeftHip],40)

def PoseCoosh():
 Set([SFrontLeftWrist],40)
 Set([SFrontRightWrist],140)
 Set([SBackLeftWrist],40)
 Set([SBackRightWrist],140)
 Go([SFrontLeftArm],160)
 Go([SFrontRightArm],20)
 Go([SBackLeftArm],160)
 Go([SBackRightArm],20)
def PoseCoosh2():
 Set([SFrontLeftWrist],30)
 Set([SFrontRightWrist],140)
 Set([SBackLeftWrist],30)
 Set([SBackRightWrist],140)
 Go([SFrontLeftArm],160)
 Go([SFrontRightArm],10)
 Go([SBackLeftArm],160)
 Go([SBackRightArm],10)


trot1 = 100
trot2 = 80
def PoseTrot1():
 Set([SFrontLeftWrist],120)
 Set([SFrontRightWrist],60)
 Set([SFrontLeftArm],130)
 Set([SFrontRightArm],50)
 Set([SBackLeftWrist],120)
 Set([SBackRightWrist],60)
 Set([SBackLeftArm],130)
 Set([SBackRightArm],50)

def PoseTrot2():
 Set([SFrontLeftWrist],90)
 Set([SFrontRightWrist],90)
 Set([SFrontLeftArm],120)
 Set([SFrontRightArm],60)
 Set([SBackLeftWrist],120)
 Set([SBackRightWrist],60)
 Set([SBackLeftArm],140)
 Set([SBackRightArm],40)

def PoseStandUp():
 Set([SFrontLeftWrist],120)
 Set([SFrontRightWrist],60)
 time.sleep(0.5)
 Go([SFrontLeftArm],130)
 Go([SFrontRightArm],50)
 Set([SBackLeftWrist],120)
 Set([SBackRightWrist],60)
 time.sleep(0.5)
 Go([SBackLeftArm],130)
 Go([SBackRightArm],50)



def PoseSitUp():
 Set([SBackLeftWrist],90)
 Set([SBackRightWrist],90)
 time.sleep(0.5)
 Go([SBackLeftArm],120)
 Go([SBackRightArm],60)
 Set([SFrontLeftWrist],140)
 Set([SFrontRightWrist],40)
 time.sleep(0.5)
 Go([SFrontLeftArm],130)
 Go([SFrontRightArm],50)

def PoseSitDown():
 Set([SBackLeftWrist],90)
 Set([SBackRightWrist],90)
 time.sleep(0.5)
 Go([SBackLeftArm],90)
 Go([SBackRightArm],90)
 Set([SFrontLeftWrist],90)
 Set([SFrontRightWrist],90)
 time.sleep(0.5)
 Go([SFrontLeftArm],90)
 Go([SFrontRightArm],90)

def PoseWrists():
 print('Pose:Wrists')
 Set([SFrontLeftWrist],140)
 Set([SFrontRightWrist],40)

def PoseWavePawFLUp():
 Go([SFrontLeftWrist],40)
def PoseWavePawFLMid():
 Set([SFrontLeftWrist],90)
def PoseWavePawFRUp():
 Go([SFrontRightWrist],140)
def PoseWavePawFRMid():
 Set([SFrontRightWrist],90)

def PoseWavePawBLUp():
 Go([SBackLeftWrist],40)
def PoseWavePawBLMid():
 Set([SBackLeftWrist],90)
def PoseWavePawBRUp():
 Go([SBackRightWrist],140)
def PoseWavePawBRMid():
 Set([SBackRightWrist],90)

def PoseTailUp():
 Set([STail],140)

def PoseTailMid():
 Set([STail],90)

def PoseTailDown():
 Set([STail],20)

def FrontLeftWristUp():
 Set([SFrontLeftWrist],30)
def FrontLeftWristMid():
 Set([SFrontLeftWrist],90)
def FrontLeftWristDown():
 Set([SFrontLeftWrist],150)
def BackLeftWristUp():
 Set([SBackLeftWrist],30)
def BackLeftWristMid():
 Set([SBackLeftWrist],90)
def BackLeftWristDown():
 Set([SBackLeftWrist],150)

def FrontRightWristUp():
 Set([SFrontRightWrist],150)
def FrontRightWristMid():
 Set([SFrontRightWrist],90)
def FrontRightWristDown():
 Set([SFrontRightWrist],30)
def BackRightWristUp():
 Set([SBackRightWrist],150)
def BackRightWristMid():
 Set([SBackRightWrist],90)
def BackRightWristDown():
 Set([SBackRightWrist],30)


def FrontLeftArmUp():
 Set([SFrontLeftArm],40)
def FrontLeftArmMid():
 Set([SFrontLeftArm],90)
def FrontLeftArmDown():
 Set([SFrontLeftArm],140)
def BackLeftArmUp():
 Set([SBackLeftArm],40)
def BackLeftArmMid():
 Set([SBackLeftArm],90)
def BackLeftArmDown():
 Set([SBackLeftArm],140)
def FrontRightArmUp():
 Set([SFrontRightArm],140)
def FrontRightArmMid():
 Set([SFrontRightArm],90)
def FrontRightArmDown():
 Set([SFrontRightArm],40)
def BackRightArmUp():
 Set([SBackRightArm],140)
def BackRightArmMid():
 Set([SBackRightArm],90)
def BackRightArmDown():
 Set([SBackRightArm],40)


def FrontLeftHipUp():
 Set([SFrontLeftHip],60)
def FrontLeftHipMid():
 Set([SFrontLeftHip],90)
def FrontLeftHipDown():
 Set([SFrontLeftHip],120)
def BackLeftHipUp():
 Set([SBackLeftHip],120)
def BackLeftHipMid():
 Set([SBackLeftHip],90)
def BackLeftHipDown():
 Set([SBackLeftHip],60)
def FrontRightHipUp():
 Set([SFrontRightHip],120)
def FrontRightHipMid():
 Set([SFrontRightHip],90)
def FrontRightHipDown():
 Set([SFrontRightHip],60)
def BackRightHipUp():
 Set([SBackRightHip],60)
def BackRightHipMid():
 Set([SBackRightHip],90)
def BackRightHipDown():
 Set([SBackRightHip],120)


def ChangeFrontLeftWrist(val):
 Change([SFrontLeftWrist], -val)
def ChangeFrontLeftArm(val):
 Change([SFrontLeftArm], -val)
def ChangeFrontLeftHip(val):
 Change([SFrontLeftHip], -val)
def ChangeFrontRightWrist(val):
 Change([SFrontRightWrist], val)
def ChangeFrontRightArm(val):
 Change([SFrontRightArm], val)
def ChangeFrontRightHip(val):
 Change([SFrontRightHip], val)

def ChangeBackLeftWrist(val):
 Change([SBackLeftWrist], -val)
def ChangeBackLeftArm(val):
 Change([SBackLeftArm], -val)
def ChangeBackLeftHip(val):
 Change([SBackLeftHip], val)
def ChangeBackRightWrist(val):
 Change([SBackRightWrist], val)
def ChangeBackRightArm(val):
 Change([SBackRightArm], val)
def ChangeBackRightHip(val):
 Change([SBackRightHip], -val)


def DisableServos():
 Set(ServoAll,None)

print('Servos Module OK')

