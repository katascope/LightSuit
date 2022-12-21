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
  String name;
  int id;
  int min;
  int degree;
  int max;
  bool reverse;
};

#define ORIGIN_HIP   90
#define ORIGIN_ELBOW 90
#define ORIGIN_FOOT  90
#define ORIGIN_EARS  90
#define ORIGIN_TAIL  90
#define RANGE_HIP    20
#define RANGE_ELBOW  20
#define RANGE_FOOT   20
#define RANGE_EARS   20
#define RANGE_TAIL   20
#define RANGE_HIP_MIN    (ORIGIN_HIP-RANGE_HIP)
#define RANGE_HIP_MAX    (ORIGIN_HIP+RANGE_HIP)
#define RANGE_ELBOW_MIN  (ORIGIN_ELBOW-RANGE_ELBOW)
#define RANGE_ELBOW_MAX  (ORIGIN_ELBOW+RANGE_ELBOW)
#define RANGE_FOOT_MIN   (ORIGIN_FOOT-RANGE_FOOT)
#define RANGE_FOOT_MAX   (ORIGIN_FOOT+RANGE_FOOT)
#define RANGE_EARS_MIN   (ORIGIN_EARS-RANGE_EARS)
#define RANGE_EARS_MAX   (ORIGIN_EARS+RANGE_EARS)
#define RANGE_TAIL_MIN   (ORIGIN_TAIL-RANGE_TAIL)
#define RANGE_TAIL_MAX   (ORIGIN_TAIL+RANGE_TAIL)

const int POSE_ZERO[SERVO_NUM] {   RANGE_HIP_MIN,RANGE_ELBOW_MIN,RANGE_FOOT_MIN,0, RANGE_HIP_MIN,RANGE_ELBOW_MIN,RANGE_FOOT_MIN,0, RANGE_HIP_MIN,RANGE_ELBOW_MIN,RANGE_FOOT_MIN,0, RANGE_HIP_MIN,RANGE_ELBOW_MIN,RANGE_FOOT_MIN,0 };
const int POSE_CENTER[SERVO_NUM] { ORIGIN_HIP,ORIGIN_ELBOW,ORIGIN_FOOT,ORIGIN_EARS, ORIGIN_HIP,ORIGIN_ELBOW,ORIGIN_FOOT,ORIGIN_EARS, ORIGIN_HIP,ORIGIN_ELBOW,ORIGIN_FOOT,ORIGIN_EARS, ORIGIN_HIP,ORIGIN_ELBOW,ORIGIN_FOOT,ORIGIN_TAIL };
const int POSE_MAX[SERVO_NUM]  {   RANGE_HIP_MAX,RANGE_ELBOW_MAX,RANGE_FOOT_MAX,0, RANGE_HIP_MAX,RANGE_ELBOW_MAX,RANGE_FOOT_MAX,0, RANGE_HIP_MAX,RANGE_ELBOW_MAX,RANGE_FOOT_MAX,0, RANGE_HIP_MAX,RANGE_ELBOW_MAX,RANGE_FOOT_MAX,0  };

void ServoStartup();
void ServoSet(int servo, int degree);
void ServoSetAll(int degree);
void ServoPoseLerp(float lerp, const int *servostateOrig, const int *servostateDest);
void ServoPose(const int *servostate);

#endif
