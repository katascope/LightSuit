/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#ifndef CMD_DEF
#define CMD_DEF
#include <Arduino.h>
struct FxController;

enum CaptureTextMode
{
  CaptureNone,
  CaptureTimeCode
};

enum UserCommand
{
  Cmd_Unk,
  Cmd_Help,

  Cmd_ServoMin,
  Cmd_ServoCenter,
  Cmd_ServoMax,

  Cmd_Brightness_Max,
  Cmd_Brightness_Normal,
  Cmd_Brightness_Half,

  Cmd_State_Default,
  Cmd_State_Test,
  
  Cmd_PlayFromStart,
  Cmd_PlayFrom,
  Cmd_PlayStop,
  
  Cmd_ColorDark, 
  Cmd_ColorWhite,
  Cmd_ColorRed,
  Cmd_ColorYellow,
  Cmd_ColorGreen,
  Cmd_ColorCyan,
  Cmd_ColorBlue,
  Cmd_ColorMagenta,
  Cmd_ColorOrange,
  Cmd_ColorHalf,

  Cmd_ColorWhiteBlue,
  Cmd_ColorWhiteYellow,
  Cmd_ColorWhiteMagenta,
  Cmd_ColorRedBlue,
  Cmd_ColorCyanMagenta,

  Cmd_ColorPulseDark, 
  Cmd_ColorPulseWhite,
  Cmd_ColorPulseRed,
  Cmd_ColorPulseYellow,
  Cmd_ColorPulseGreen,
  Cmd_ColorPulseCyan,
  Cmd_ColorPulseBlue,
  Cmd_ColorPulseMagenta,
  Cmd_ColorPulseOrange,  
  Cmd_ColorPulseHalf, 
  Cmd_ColorPulse2Dark, 
  Cmd_ColorPulse2White,
  Cmd_ColorPulse2Red,
  Cmd_ColorPulse2Yellow,
  Cmd_ColorPulse2Green,
  Cmd_ColorPulse2Cyan,
  Cmd_ColorPulse2Blue,
  Cmd_ColorPulse2Magenta,
  Cmd_ColorPulse2Orange,  
  Cmd_ColorPulse2Half,  

  Cmd_ColorLava,
  Cmd_ColorCloud,
  Cmd_ColorOcean,
  Cmd_ColorForest,
  Cmd_ColorRainbow,
  Cmd_ColorRainbowstripe,
  Cmd_ColorParty,
  Cmd_ColorHeat,

  Cmd_SpeedNeg,
  Cmd_SpeedPos,
  Cmd_SpeedDec,
  Cmd_SpeedInc,
  Cmd_SpeedRst,
  Cmd_Speed1,
  Cmd_Speed2,
  Cmd_Speed3,
  Cmd_Speed4,

  Cmd_Particles_On,
  Cmd_Particles_Off,

  Cmd_StripAll,
  Cmd_StripNone,
  Cmd_StripOdds,
  Cmd_StripEvens,
  Cmd_Strip0,
  Cmd_Strip1,
  Cmd_Strip2,
  Cmd_Strip3,
  Cmd_Strip4,
  Cmd_Strip5,
  Cmd_Strip6,
  Cmd_Strip7,

  Cmd_TransitionFast
};

void UserCommandExecute(FxController &fxc, int cmd);
void UserCommandInput(FxController &fxc, int data);

void ComplexUserCommandInput(FxController &fxc, String data);

#endif
