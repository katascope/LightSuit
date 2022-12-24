/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#include "Emotion.h"
#include "Cmd.h"

struct Emotion emotions[EMOTION_NUM] =
{
    { EMOTION_LO, EMOTION_LO, EMOTION_LO, F("distressed"),     F("retreat"),  F("glow red,say whimper,motion retreat") },
    { EMOTION_HI, EMOTION_LO, EMOTION_LO, F("lonely"),         F("whimper"),  F("glow yellow,say whimper,pose wait") },
    { EMOTION_MX, EMOTION_LO, EMOTION_LO, F("alone"),          F("search"),   F("glow blue,say hunt,motion search") },
    { EMOTION_LO, EMOTION_LO, EMOTION_HI, F("aggressive"),     F("growl"),    F("glow red,say growl,pose fight") },
    { EMOTION_HI, EMOTION_LO, EMOTION_HI, F("sad"),            F("paw"),      F("glow yellow,say mrewl,motion pawshake") },
    { EMOTION_MX, EMOTION_LO, EMOTION_HI, F("resigned"),       F("stare"),    F("glow blue,say nothing,pose wait") },
    { EMOTION_LO, EMOTION_LO, EMOTION_MX, F("uncomfortable"),  F("wait"),     F("glow red,say hmewl,pose wait") },
    { EMOTION_HI, EMOTION_LO, EMOTION_MX, F("mopey"),          F("mope"),     F("glow yellow,say nothing,pose wait") },
    { EMOTION_MX, EMOTION_LO, EMOTION_MX, F("interested"),     F("watch"),    F("glow blue,say nothing,pose wait") },

    { EMOTION_LO, EMOTION_HI, EMOTION_LO, F("shy"),            F("cower"),    F("") },
    { EMOTION_HI, EMOTION_HI, EMOTION_LO, F("detached"),       F("search"),   F("") },
    { EMOTION_MX, EMOTION_HI, EMOTION_LO, F("skeptical"),      F("search"),   F("") },
    { EMOTION_LO, EMOTION_HI, EMOTION_HI, F("unsure"),         F("whine"),    F("") },
    { EMOTION_HI, EMOTION_HI, EMOTION_HI, F("centered"),       F("nothing"),  F("") },
    { EMOTION_MX, EMOTION_HI, EMOTION_HI, F("focused"),        F("continue"), F("") },
    { EMOTION_LO, EMOTION_HI, EMOTION_MX, F("hesitant"),       F("wait"),     F("") },
    { EMOTION_HI, EMOTION_HI, EMOTION_MX, F("engaged"),        F("be"),       F("") },
    { EMOTION_MX, EMOTION_HI, EMOTION_MX, F("decisive"),       F("be"),       F("") },

    { EMOTION_LO, EMOTION_MX, EMOTION_LO, F("shy"),            F("mewl"),     F("") },
    { EMOTION_HI, EMOTION_MX, EMOTION_LO, F("calm"),           F("mew"),      F("") },
    { EMOTION_MX, EMOTION_MX, EMOTION_LO, F("nice"),           F("sing"),     F("") },
    { EMOTION_LO, EMOTION_MX, EMOTION_HI, F("waiting"),        F("wait"),     F("") },
    { EMOTION_HI, EMOTION_MX, EMOTION_HI, F("happy"),          F("be"),       F("") },
    { EMOTION_MX, EMOTION_MX, EMOTION_HI, F("proud"),          F("be"),       F("") },
    { EMOTION_LO, EMOTION_MX, EMOTION_MX, F("curious"),        F("wait"),     F("") },
    { EMOTION_HI, EMOTION_MX, EMOTION_MX, F("playful"),        F("play"),     F("") },
    { EMOTION_MX, EMOTION_MX, EMOTION_MX, F("ecstastic"),      F("be"),       F("") },
};

const Emotion *FeelingToName(float confidence, float positivity, float engagement)
{
    for (int i = 0; i < EMOTION_NUM; i++)
    {
        Emotion *e = &emotions[i];
        if (confidence <= e->confidence 
            && positivity <= e->positivity
            && engagement <= e->engagement)
            return e;
    }
    return NULL;
}

EmotionalPoint::EmotionalPoint()
{
}

EmotionalPoint::EmotionalPoint(float c, float p, float e)
{
  Confidence = c;
  Positivity = p;
  Engagement = e;
}

EmotionalCore::EmotionalCore()
{  
}

void EmotionalCore::Poll(struct FxController &fxc)
{
  if (fxc.fxState != FxState_PlayingTrack)
  {
    if (current.Engagement <= 0.11) UserCommandExecute(fxc, Cmd_ColorMagenta);
    else if (current.Engagement <= 0.31) UserCommandExecute(fxc, Cmd_ColorGreen);
    else if (current.Engagement <= 0.61) UserCommandExecute(fxc, Cmd_ColorYellow);
    else if (current.Engagement <= 0.71) UserCommandExecute(fxc, Cmd_ColorOrange);
    else UserCommandExecute(fxc, Cmd_ColorRed);
  }
}

String EmotionalCore::GetCurrentFeelingName()
{ 
  return FeelingToName(current.Confidence, current.Positivity, current.Engagement)->feeling;
}

void EmotionalCore::Print()
{
  Serial.print(F("["));
  Serial.print((int)(current.Confidence*100.0f));
  Serial.print(F("% "));
  Serial.print((int)(current.Positivity*100.0f));
  Serial.print(F("% "));
  Serial.print((int)(current.Engagement*100.0f));
  Serial.print(F("%]="));
  Serial.print(GetCurrentFeelingName());
}
