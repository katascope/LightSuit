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

void PrintMindState()
{
  Serial.print(DeviceName);  
  switch(foxenMindState)
  {
    case MIND_STATE_ASLEEP:     Serial.print(F("=asleep"));break;
    case MIND_STATE_PRIMAL:     Serial.print(F("=primal"));break;
    case MIND_STATE_DIRECT:     Serial.print(F("=direct"));break;
    case MIND_STATE_TRACK:      Serial.print(F("=track"));break;
    case MIND_STATE_AUTONOMOUS: Serial.print(F("=auto"));break;
  }
  emotions.Print();
  Serial.print(F(","));  
  ServosPrint();
}

void PollMindState(struct FxController &fxController)
{
  if (fxController.fxState == FxState_PlayingTrack)
  {
    //do normal things
  }  
  else if (foxenMindState == MIND_STATE_ASLEEP)
  {
    UserCommandExecute(fxController, Cmd_ColorPulseMagenta);
    UserCommandExecute(fxController, Cmd_SpeedNeg);
    UserCommandExecute(fxController, Cmd_Speed1);
    
    return;
  }
  else
  {
    emotions.Poll(fxController);
  }

  State_Poll(fxController);
  
  bool needsUpdate = false;
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
