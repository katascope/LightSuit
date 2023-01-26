/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#include "Config.h"
#include "Fx.h"
#include "FxCore.h"
#include "FoxenMind.h"
#include "State.h"
#include "Devices.h"
#include "Servos.h"
#include "Cmd.h"

static FoxenMindState foxenMindState = MIND_STATE_ASLEEP;
static EmotionalCore emotions;

static int pplCount = 0;
void SetPeopleCount(int count)
{
  pplCount = count;
}
int GetPeopleCount()
{
  return pplCount;
}


FoxenMindState GetMindState()
{
  return foxenMindState;  
}
void SetMindState(FoxenMindState state)
{
  foxenMindState = state;
}

void SetMindEngagement(float v)
{
  emotions.current.Engagement = v;
}

void UpdatePalette(struct FxController &fxController)
{
  FxProcessSideFX(fxController);
  
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if ((int)fxController.strip[strip]->fxPaletteUpdateType != 0)
    {
      fxController.strip[strip]->paletteIndex = fxController.strip[strip]->paletteIndex + (fxController.strip[strip]->paletteSpeed * fxController.strip[strip]->paletteDirection);
      if (fxController.strip[strip]->paletteIndex >= fxController.strip[strip]->numleds)
        fxController.strip[strip]->paletteIndex -= fxController.strip[strip]->numleds;
      if (fxController.strip[strip]->paletteIndex < 0)
        fxController.strip[strip]->paletteIndex = fxController.strip[strip]->numleds - 1;
    }
#if ENABLE_NEOPIXEL
    neopixelSetPalette(strip, fxController.strip[strip]->numleds, fxController.strip[strip]->palette, fxController.strip[strip]->paletteIndex);
#endif    
  }
}

static bool peopleRectSeenFlag = false;
bool SetPeopleRectSeenFlag(bool status)
{
  peopleRectSeenFlag = status;  
}
bool GetPeopleRectSeenFlag()
{
  return peopleRectSeenFlag;
}

static int peopleRectX1 = 0;
static int peopleRectY1 = 0;
static int peopleRectX2 = 0;
static int peopleRectY2 = 0;
void SetPeopleRect(int x1, int y1, int x2, int y2)
{
  peopleRectX1 = x1;
  peopleRectY1 = y1;
  peopleRectX2 = x2;
  peopleRectY2 = y2;
}
void GetPeopleRect(int &x1, int &y1, int &x2, int &y2)
{
  x1 = peopleRectX1;
  y1 = peopleRectY1;
  x2 = peopleRectX2;
  y2 = peopleRectY2;
}

void PrintMindState()
{
  Serial.print(DeviceName);  
  switch(foxenMindState)
  {
    case MIND_STATE_ASLEEP:     Serial.print(F("=asleep"));break;
    case MIND_STATE_WAKING:     Serial.print(F("=waking"));break;
    case MIND_STATE_READY:      Serial.print(F("=ready"));break;
    case MIND_STATE_TRACK:      Serial.print(F("=track"));break;
    case MIND_STATE_AUTONOMOUS: Serial.print(F("=auto"));break;
  }
  Serial.print(F(",ppl="));  
  Serial.print(pplCount);
  
  emotions.Print();
  Serial.print(F(","));  
  ServosPrint();
}

#if MREE
#define ColorSleeping Cmd_ColorRainbow
#define ColorWaking Cmd_ColorGreen
#define ColorReady Cmd_ColorBlueMagenta
#define ColorTrack  Cmd_ColorMagenta
#define ColorAuto  Cmd_ColorOrange
#endif

#if PREE
#define ColorSleeping Cmd_ColorRainbow
#define ColorWaking Cmd_ColorGreen
#define ColorReady Cmd_ColorCyanBlue
#define ColorTrack  Cmd_ColorMagenta
#define ColorAuto  Cmd_ColorOrange
#endif

#define ColorAuto_0 Cmd_ColorPulseRed
#define ColorAuto_1 Cmd_ColorPulseYellow
#define ColorAuto_2 Cmd_ColorPulseGreen
#define ColorAuto_N Cmd_ColorRainbow

void PollMindState(struct FxController &fxController)
{
  if (fxController.select)
  {    
  }
  else if (STARTUP_STATE == FxState_TestPattern)
  {
    UserCommandExecute(fxController, Cmd_ColorRainbow);
    UserCommandExecute(fxController, Cmd_SpeedPos);
    UserCommandExecute(fxController, Cmd_Speed1);    
  }  
  else if (fxController.fxState == FxState_PlayingTrack)
  {
  }  
  else if (foxenMindState == MIND_STATE_ASLEEP)
  {
    UserCommandExecute(fxController, ColorSleeping);
    UserCommandExecute(fxController, Cmd_SpeedNeg);
    UserCommandExecute(fxController, Cmd_Speed1);    
    return;
  }
  else if (foxenMindState == MIND_STATE_WAKING)
  {
    UserCommandExecute(fxController, ColorWaking);
    UserCommandExecute(fxController, Cmd_SpeedPos);
    UserCommandExecute(fxController, Cmd_Speed1);    
    return;
  }
  else if (foxenMindState == MIND_STATE_READY)
  {
    UserCommandExecute(fxController, ColorReady);
    UserCommandExecute(fxController, Cmd_SpeedPos);
    if (pplCount == 0) UserCommandExecute(fxController, Cmd_Speed1);    
    else if (pplCount == 1) UserCommandExecute(fxController, Cmd_Speed2);    
    else if (pplCount == 2) UserCommandExecute(fxController, Cmd_Speed3);    
    else UserCommandExecute(fxController, Cmd_Speed4);
    return;
  }
  else if (foxenMindState == MIND_STATE_TRACK)
  {
    UserCommandExecute(fxController, ColorTrack);
    UserCommandExecute(fxController, Cmd_SpeedPos);
    UserCommandExecute(fxController, Cmd_Speed1);    
    return;
  }
  else if (foxenMindState == MIND_STATE_AUTONOMOUS)
  {
    switch (GetPeopleCount())
    {
      case 0:  UserCommandExecute(fxController, ColorAuto_0); break;
      case 1:  UserCommandExecute(fxController, ColorAuto_1); break;
      case 2:  UserCommandExecute(fxController, ColorAuto_2); break;
      default: UserCommandExecute(fxController, ColorAuto_N); break;
    }
    UserCommandExecute(fxController, Cmd_SpeedPos);
    UserCommandExecute(fxController, Cmd_Speed1);  

    if (GetPeopleRectSeenFlag() == false)
    {
      int x1,y1,x2,y2;
      GetPeopleRect(x1,y1,x2,y2);
      int nudgeX = 0;
      int nudgeY = 0;

      int centerX = x1 + (x2-x1)/2;
      
      if (y1 > 88) nudgeY = -1;//prioritize looking at feet
      else if (y2 < 10) nudgeY = 1; //try to get heads in picture otherwise
  
      if (centerX < 30) nudgeX = -1; //try to keep centered horizontally
      else if (centerX > 60) nudgeX = 1;
  
      if (nudgeY>0) ServoInc(SERVO_LEFT_FRONT_WRIST);
      else if (nudgeY < 0) ServoDec(SERVO_LEFT_FRONT_WRIST);

      if (nudgeX>0) ServoInc(SERVO_LEFT_FRONT_HIP);
      else if (nudgeX < 0) ServoDec(SERVO_LEFT_FRONT_HIP);

      Serial.print(F("Rect:"));
      Serial.print(x1);
      Serial.print(F(" "));
      Serial.print(y1);
      Serial.print(F(" "));
      Serial.print(x2);
      Serial.print(F(" "));
      Serial.print(y2);
      Serial.print(F("="));
      Serial.print(nudgeX);
      Serial.print(F(","));
      Serial.print(nudgeY);
      Serial.println();

      SetPeopleRectSeenFlag(true);
    }
  }
  else
  {
    emotions.Poll(fxController);
  }

  State_Poll(fxController);
  bool needsUpdate = false;

  if (fxController.select)
  {
    FxEventProcess(fxController, fx_status_section_0 + fxController.select);
    needsUpdate = true;
  }
  else FxEventProcess(fxController, fx_strip_all);
  
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxController.strip[strip]->fxPaletteUpdateType == FxPaletteUpdateType::Once
     || fxController.strip[strip]->fxPaletteUpdateType == FxPaletteUpdateType::Always
     || fxController.IsAnimating())
      needsUpdate = true;
  }  
  if (fxController.fxState == FxState_PlayingTrack || needsUpdate)
  {
    unsigned long t =  millis();
    if (t - fxController.lastTimeLedUpdate > UPDATE_DELAY)//delay to let bluetooth get data(fastled issue)
    {
      UpdatePalette(fxController);      
      fxController.lastTimeLedUpdate = t;
      
      for (int strip=0;strip<NUM_STRIPS;strip++)
      {
        if (fxController.strip[strip]->fxPaletteUpdateType == FxPaletteUpdateType::Once)
            fxController.strip[strip]->fxPaletteUpdateType = FxPaletteUpdateType::Done;
      }
    }
  }
}
