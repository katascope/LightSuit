/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Servos.h"
#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50
#define SERVO_DELAY           5 //25

//PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

struct ServoStatus servoInfo[SERVO_NUM] =
{
 { "lbh",       SERVO_LEFT_BACK_HIP,     RANGE_HIP_MIN,   ORIGIN_HIP,   RANGE_HIP_MAX,   false },
 { "lbe",       SERVO_LEFT_BACK_ELBOW,   RANGE_ELBOW_MIN, ORIGIN_ELBOW, RANGE_ELBOW_MAX, true },
 { "lbw",       SERVO_LEFT_BACK_WRIST,   RANGE_WRIST_MIN, ORIGIN_WRIST, RANGE_WRIST_MAX, false },
 { "lear",      SERVO_LEFT_EAR,          RANGE_EARS_MIN,  ORIGIN_EARS,  RANGE_EARS_MAX,  false },
 { "lfh",       SERVO_LEFT_FRONT_HIP,    RANGE_HIP_MIN,   ORIGIN_HIP,   RANGE_HIP_MAX,   true },
 { "lfe",       SERVO_LEFT_FRONT_ELBOW,  RANGE_ELBOW_MIN, ORIGIN_ELBOW, RANGE_ELBOW_MAX, true },
 { "lfw",       SERVO_LEFT_FRONT_WRIST,  RANGE_WRIST_MIN, ORIGIN_WRIST, RANGE_WRIST_MAX, false },
 { "lrsrv",     SERVO_LEFT_RESERVED,     80, 90, 100, false },
 { "rbh",       SERVO_RIGHT_BACK_HIP,    RANGE_HIP_MIN,   ORIGIN_HIP,   RANGE_HIP_MAX,   true  },
 { "rbe",       SERVO_RIGHT_BACK_ELBOW,  RANGE_ELBOW_MIN, ORIGIN_ELBOW, RANGE_ELBOW_MAX, false  },
 { "rbw",       SERVO_RIGHT_BACK_WRIST,  RANGE_WRIST_MIN, ORIGIN_WRIST, RANGE_WRIST_MAX, true  },
 { "rear",      SERVO_RIGHT_EAR,         RANGE_EARS_MIN,  ORIGIN_EARS,  RANGE_EARS_MAX,  false },
 { "rfh",       SERVO_RIGHT_FRONT_HIP,   RANGE_HIP_MIN,   ORIGIN_HIP,   RANGE_HIP_MAX,   false  },
 { "rfe",       SERVO_RIGHT_FRONT_ELBOW, RANGE_ELBOW_MIN, ORIGIN_ELBOW, RANGE_ELBOW_MAX, false  },
 { "rfw" ,      SERVO_RIGHT_FRONT_WRIST, RANGE_WRIST_MIN, ORIGIN_WRIST, RANGE_WRIST_MAX, true  },
 { "tail",      SERVO_TAIL,              RANGE_TAIL_MIN,  ORIGIN_TAIL,  RANGE_TAIL_MAX,  false }
};

void ServosRest()
{
  for (int servo=0;servo<SERVO_NUM;servo++)
  {
    pwm.setPWM(servo, 0, 0 );
  }
}

void ServosPrint()
{
  Serial.print(F("{"));
  for (int servo=0;servo<SERVO_NUM;servo++)
  {
    if (servo != SERVO_LEFT_EAR
      && servo != SERVO_LEFT_RESERVED
      && servo != SERVO_RIGHT_EAR
      && servo != SERVO_TAIL)
      {
        Serial.print(servoInfo[servo].degree);
        Serial.print(F(","));
      }
      else if (servo == SERVO_TAIL) Serial.print(F("-1"));
      else Serial.print(F("-1,"));
  }
  Serial.print(F("}"));
}

int pulseWidth(int angle, bool reverse)
{
  int pulse_wide, analog_value;
  if (reverse) angle = 180-angle;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

int lerpServo(float mux, int src, int dst) { return (int)(src * (1.0 - mux) + dst * mux); }

void ServoStartup()
{
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates  
}

void ServoSet(int servo, int degree)
{
  //Enforce range limits
  if (degree < servoInfo[servo].min) degree = servoInfo[servo].min;
  if (degree > servoInfo[servo].max) degree = servoInfo[servo].max;

  servoInfo[servo].degree = degree;
  int pulse=pulseWidth(degree, servoInfo[servo].reverse);
  pwm.setPWM(servo,0,pulse);
/*  Serial.print(F("Servo"));
  Serial.print(servo);
  Serial.print(F(" "));
  Serial.print(servoInfo[servo].name);
  Serial.print(F("="));
  Serial.print(degree);
  Serial.print(F(",wait 1 sec"));
  Serial.println();*/
  delay(SERVO_DELAY);
}

void ServoSetAll(int degree)
{
  for (int servo=0;servo<SERVO_NUM;servo++)
    ServoSet(servo,degree);
}

void ServoInc(int servo)
{  
  ServoSet(servo,servoInfo[servo].degree+5);
}
void ServoDec(int servo)
{
  ServoSet(servo,servoInfo[servo].degree-5);
}


void ServoPoseLerp(float lerp, const int *servostateOrig, const int *servostateDest)
{
  for (int servo=0;servo<SERVO_NUM;servo++)
  {
    if (servo != SERVO_LEFT_EAR
      && servo != SERVO_LEFT_RESERVED
      && servo != SERVO_RIGHT_EAR
      && servo != SERVO_TAIL)
      {
        int val = lerpServo(lerp, servostateOrig[servo], servostateDest[servo]);      
        ServoSet(servo,val);
      }        
  }
}

void ServoPoseLerpTo(const int *servostateDest, float sec)
{
  //Save first state so can tween properly until end
  int servostateStart[SERVO_NUM] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
  for (int servo=0;servo<SERVO_NUM;servo++)
   servostateStart[servo] = servoInfo[servo].degree;

  int ms = (sec*100)/10;
  //1 second
  for (int i=0;i<ms;i++)//because 5ms delay in each servo call
  {
    float lerp = (float)i/(float)ms;
    for (int servo=0;servo<SERVO_NUM;servo++)
    {
      if (servo != SERVO_LEFT_EAR
        && servo != SERVO_LEFT_RESERVED
        && servo != SERVO_RIGHT_EAR
        && servo != SERVO_TAIL)
        {
          if (servostateDest[servo] != -1)
          {
            int val = lerpServo(lerp, servostateStart[servo], servostateDest[servo]);      
            ServoSet(servo,val);
          }
        }        
    }
  }
}

void ServoPose(const int *servostate)
{
  for (int servo=0;servo<SERVO_NUM;servo++)
  {
    if (servo != SERVO_LEFT_EAR
      && servo != SERVO_LEFT_RESERVED
      && servo != SERVO_RIGHT_EAR
      && servo != SERVO_TAIL)
      {
        int degree = servostate[servo];
        if (degree != -1)
          ServoSet(servo,degree);
      }
  }   
}
