/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#ifndef SERVOS_DEF
#define SERVOS_DEF

#define SERVO_LEFT_BACK_HIP     0x0
#define SERVO_LEFT_BACK_ELBOW   0x1
#define SERVO_LEFT_BACK_FOOT    0x2
#define SERVO_LEFT_EAR          0x3
#define SERVO_LEFT_FRONT_HIP    0x4
#define SERVO_LEFT_FRONT_ELBOW  0x5
#define SERVO_LEFT_FRONT_FOOT   0x6
#define SERVO_LEFT_RESERVED     0x7
#define SERVO_RIGHT_BACK_HIP    0x8
#define SERVO_RIGHT_BACK_ELBOW  0x9
#define SERVO_RIGHT_BACK_FOOT   0xA
#define SERVO_RIGHT_EAR         0xB
#define SERVO_RIGHT_FRONT_HIP   0xC
#define SERVO_RIGHT_FRONT_ELBOW 0xD
#define SERVO_RIGHT_FRONT_FOOT  0xE
#define SERVO_TAIL              0xF

#define SERVO_NUM               16

struct ServoStatus
{
  int id;
  int min;
  int degree;
  int max;
};

const int POSE_ZERO[SERVO_NUM] { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };
const int POSE_CENTER[SERVO_NUM] { 90,90,90,90, 90,90,90,90, 90,90,90,90, 90,90,90,90 };
const int POSE_MAX[SERVO_NUM]  { 180,180,180,180, 180,180,180,180, 180,180,180,180, 180,180,180,180 };
const int POSE_SIT[SERVO_NUM]  { 90,90,90,90, 90,90,90,90, 90,90,90,90, 90,90,90,90 };

void ServoStartup();
void ServoSet(int servo, int degree);
void ServoSetAll(int degree);
void ServoPoseLerp(float lerp, const int *servostateOrig, const int *servostateDest);
void ServoPose(const int *servostate);

#endif
