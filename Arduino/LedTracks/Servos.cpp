#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Servos.h"
#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

//PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void ServoStartup()
{
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates
}

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(analog_value);
  return analog_value;
}

void ServoGo(int degree)
{
  for (int servo=0;servo<16;servo++)
  {
    int pulse=pulseWidth(degree);
    pwm.setPWM(servo,0,pulse);
    Serial.print(F("Servo"));
    Serial.print(servo);
    Serial.print(F(", deg="));
    Serial.print(degree);
    Serial.println();
    Serial.print(F(", pulse="));
    Serial.print(pulse);
  } 
}
