#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Servos.h"
#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

//PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

struct ServoStatus servoInfo[SERVO_NUM] =
{
 { SERVO_LEFT_BACK_HIP,     0, -1, 180 },
 { SERVO_LEFT_BACK_ELBOW,   0, -1, 180 },
 { SERVO_LEFT_BACK_FOOT,    0, -1, 180 },
 { SERVO_LEFT_EAR,          0, -1, 180 },
 { SERVO_LEFT_FRONT_HIP,    0, -1, 180 },
 { SERVO_LEFT_FRONT_ELBOW,  0, -1, 180 },
 { SERVO_LEFT_FRONT_FOOT,   0, -1, 180 },
 { SERVO_LEFT_RESERVED,     0, -1, 180 },
 { SERVO_RIGHT_BACK_HIP,    0, -1, 180 },
 { SERVO_RIGHT_BACK_ELBOW,  0, -1, 180 },
 { SERVO_RIGHT_BACK_FOOT,   0, -1, 180 },
 { SERVO_RIGHT_EAR,         0, -1, 180 },
 { SERVO_RIGHT_FRONT_HIP,   0, -1, 180 },
 { SERVO_RIGHT_FRONT_ELBOW, 0, -1, 180 },
 { SERVO_RIGHT_FRONT_FOOT,  0, -1, 180 },
 { SERVO_TAIL,              0, -1, 180 }
};

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
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
  int pulse=pulseWidth(degree);
  servoInfo[servo].degree = degree;
  pwm.setPWM(servo,0,pulse);
  Serial.print(F("Servo"));
  Serial.print(servo);
  Serial.print(F("="));
  Serial.print(degree);

  Serial.print(F(",wait 1 sec"));
  Serial.println();
  delay(1000);
/*  Serial.print(servo);
  Serial.print(F(", deg="));
  Serial.print(degree);
  Serial.println();
  Serial.print(F(", pulse="));
  Serial.print(pulse);*/
}

void ServoSetAll(int degree)
{
  for (int servo=0;servo<SERVO_NUM;servo++)
  {
    ServoSet(servo,degree);
  }  
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
        ServoSet(servo,degree);
      }
  }   
}
