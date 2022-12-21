#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


#define SERVO_NUM             16

//PCA9685   
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
int lerpServo(float mux, int src, int dst) { return (int)(src * (1.0 - mux) + dst * mux); }

int pulseWidth(int angle, bool reverse)
{
  int pulse_wide, analog_value;
  if (reverse) angle = 180-angle;
  pulse_wide   = map(angle, 0, 180, USMIN, USMAX);
  analog_value = int(float(pulse_wide) / 1000000 * SERVO_FREQ * 4096);
  return analog_value;
}

void ServoSet(int servo, int degree)
{
  //setServoPulse(servo, 0.001);
  int analog_value = pulseWidth(degree,false);
  Serial.print(F("Pulse width="));
  Serial.println(analog_value);
  pwm.setPWM(servo,0,analog_value);

  delay(100);
}

void ServoSetAll(int degree)
{
  Serial.print(F("Setting servos, "));
  for (int servo=0;servo<SERVO_NUM;servo++)
  {
    ServoSet(servo,degree);
  }  
  Serial.print(F("="));
  Serial.print(degree);
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("ServoTest started"));
  pwm.begin();
  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't
   * that precise. You can 'calibrate' this by tweaking this number until
   * you get the PWM update frequency you're expecting!
   * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
   * is used for calculating things like writeMicroseconds()
   * Analog servos run at ~50 Hz updates, It is importaint to use an
   * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
   * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
   *    the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
   *    expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and
   * affects the calculations for the PWM update frequency. 
   * Failure to correctly set the int.osc value will cause unexpected PWM results
   */
  //pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
  Serial.print(SERVO_NUM);
  Serial.print(F(" servos at "));
  Serial.print(SERVO_FREQ);
  Serial.print(F("hz"));
}

void loop()
{
  while (Serial.available())    
  {
    int ch = Serial.read();
    switch (ch)
    {
      case '?': Serial.println(F("? { \\ }")); break;
      case '{': ServoSetAll(60);break;
      case '\\':ServoSetAll(90);break;
      case '}': ServoSetAll(120);break;
    }
  }
}
