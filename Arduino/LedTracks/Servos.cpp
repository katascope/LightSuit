#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Servos.h"
const int SERVOMIN = 150; // this is the 'minimum' pulse length count (out of 4096)
const int SERVOMAX = 600; // this is the 'maximum' pulse length count (out of 4096)
//PCA9685

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

void ServoStartup()
{
  pwm1.begin();
  pwm1.setPWMFreq(1600);  // This is the maximum PWM frequency  
}

void ServoGo(int degree)
{
  int pulselength = map(degree, 0, 180, SERVOMIN, SERVOMAX);
  int servo = 0;
  if (servo==0)
  {
    Serial.print("throtd=");
    Serial.print(degree);
    Serial.print(" ");  
  }
  pwm1.setPWM(servo,0,pulselength);
 
}
