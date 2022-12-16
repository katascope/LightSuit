#!/usr/bin/env python
# coding: utf-8

# Load the gamepad and time libraries
import Gamepad
import time

# Make our own custom gamepad
# The numbers can be figured out by running the Gamepad script:
# ./Gamepad.py
# Press ENTER without typing a name to get raw numbers for each
# button press or axis movement, press CTRL+C when done
class CustomGamepad(Gamepad.Gamepad):
    def __init__(self, joystickNumber = 0):
        Gamepad.Gamepad.__init__(self, joystickNumber)
        self.axisNames = {
            0: 'LEFT-X',
            1: 'LEFT-Y',
            2: 'RIGHT-X',
            3: 'RIGHT-Y',
            #4: 'L2',
            #5: 'R2',
            6: 'DPAD-X',
            7: 'DPAD-Y'
        }
        self.buttonNames = {
            0:  'A',
            1:  'B',
            2:  '?',
            3:  'X',
            4:  'Y',
            5:  '6',
            6:  'L1',
            7:  'R1',
            8:  'L2',
            9:  'R2',
            10: 'SELECT',
            11: 'START',
            12: '12?',
            13: 'STICKBUTTONL',
            14: 'STICKBUTTONR',
            15: 'STICKBUTTONA',
            16: 'STICKBUTTONX',
            17: 'STICKBUTTONY'
        }
        self._setupReverseMaps()

# Gamepad settings
gamepadType = CustomGamepad
buttonHappy = '3'
buttonBeep = 'L3'
joystickSpeed = 'LEFT-Y'
joystickSteering = 'RIGHT-X'

# Wait for a connection
if not Gamepad.available():
    print('Please connect your gamepad...')
    while not Gamepad.available():
        time.sleep(1.0)
gamepad = gamepadType()
print('Gamepad connected')

# Set some initial state
speed = 0.0
steering = 0.0

# Handle joystick updates one at a time
while gamepad.isConnected():
    # Wait for the next event
    eventType, control, value = gamepad.getNextEvent()
    
    # Determine the type
    #   print("EventType:"+eventType+", " + str(control) + ","+ str(value))
    if eventType == 'BUTTON':
        print(eventType+", " + str(control) + ","+ str(value))
    elif eventType == 'AXIS':
        # Joystick changed
        if control == joystickSpeed:
            # Speed control (inverted)
            speed = -value
        elif control == joystickSteering:
            # Steering control (not inverted)
            steering = value
        #print('%+.1f %% speed, %+.1f %% steering' % (speed * 100, steering * 100))
        print(eventType+", " + str(control) + ","+ str(value))
