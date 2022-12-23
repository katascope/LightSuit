/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#ifndef EMOTION_DEF
#define EMOTION_DEF
#include <Arduino.h>
#include "Fx.h"

struct Emotion
{
    float confidence;
    float positivity;
    float engagement;
    String feeling;
    String impulse;
    String expression;
};

#define EMOTION_LO 0.3333
#define EMOTION_HI 0.6666
#define EMOTION_MX 1.0000
#define EMOTION_NUM 27

const Emotion *FeelingToName(float confidence, float positivity, float engagement);

class EmotionalPoint
{
public:
    float Confidence = 0.5f; //Confidence
    float Positivity = 0.5f; //Positivity
    float Engagement = 0.5f; //Engagement
    float dirX = 0;
    float dirY = 0;
    float dirZ = 0;
    float spanX = 0;
    float spanY = 0;
    float spanZ = 0;
public:
    EmotionalPoint();
    EmotionalPoint(float c, float p, float e);
};

class EmotionalCore
{
public:
    EmotionalPoint basis;
    EmotionalPoint current;
public:
    EmotionalCore();
    void Poll(struct FxController &fxc);
    String GetCurrentFeelingName();
    void Print();
};

#endif
