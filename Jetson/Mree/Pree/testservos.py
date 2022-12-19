#!/usr/bin/python3.7

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

#wrists 40 to 180 #Wrists 'center' at 150
#hips 30 to 140 #hips 'center' at ?

def Set(servos,value):
 for servo in servos:
  kit.servo[servo].angle = value
  time.sleep(0.1)

def Go(servos,value):
 stride = 1
 if (value < 90):
  stride = -1
 for servo in servos:
  for i in range(90,value,stride):
   kit.servo[servo].angle = value

def Sweep():
  sweep = range(30,120)
  for servo in ServoHips: #range (0,16):
   print("Setting servo " + str(servo))
   kit.servo[servo].actuation_range = 600
   time.sleep(0.5)
   for degree in sweep :
    print(" sweep servo " + str(degree))
    kit.servo[servo].angle = degree

def PoseZero():
    Set(ServoAll,90)

#PoseZeroAll()
#print("Zero'd All")
#time.sleep(3)

#Set([SFrontLeftWrist],140)
#Set([SFrontRightWrist],40)
#Set([SBackLeftWrist],160)
#
#Set([SBackRightWrist],20)

#print("Zeroing servos")
#Zero(ServoAll)

def PoseSitup():
 print("Executing: Situp")
 print("Wrists")
 Set([SBackLeftWrist],90)
 Set([SBackRightWrist],90)
 Go([SBackLeftArm],130)
 Go([SBackRightArm],50)
 print("Arms")
 Set([SFrontLeftWrist],140)
 Set([SFrontRightWrist],40)
 Go([SFrontLeftArm],130)
 Go([SFrontRightArm],50)

def PoseWrists():
 Set([SFrontLeftWrist],140)
 Set([SFrontRightWrist],40)

#print("Args:" + str(sys.argv))
#command = sys.argv[1]
#if (command == "b"):
# PoseSitup()
#if (command == "w"):
# PoseWrists()
#time.sleep(3)
#print("Exiting.")

print('Servos Module OK')
