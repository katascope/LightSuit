/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#include "Config.h"
#include "Cmd.h"
#include "Fx.h"
#include "Track.h"
#include "Devices.h"
#include "Servos.h"
#include "FoxenMind.h"

void UpdatePalette(FxController &fxc);
unsigned long GetTime();
void ComplexUserCommandInput(FxController &fxc, String data);

//static CaptureTextMode captureMode = CaptureNone;
//static char captureBuffer[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0};
//static int captureCount = 0;

void InstantEvent(FxController &fxc, int event, FxPaletteUpdateType paletteUpdateType)
{
  fxc.fxState = FxState_Default;

  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxc.stripMask & (1<<strip)) 
    {
      fxc.strip[strip]->fxPaletteUpdateType = paletteUpdateType;
      fxc.strip[strip]->transitionType = Transition_Instant;
    }    
  }

  //if (event != fx_nothing) PrintFxEventName(event);
  FxEventProcess(fxc, event);
  UpdatePalette(fxc);
}

void UserCommandExecute(FxController &fxc, int cmd)
{
  switch (cmd)
  {
    case Cmd_Help:
      Serial.println(F("? : Help Menu"));
      Serial.println(F("+ - : Rotate Pos/Neg"));
      Serial.println(F("( * ) : Track Start/StartFrom/Stop"));
      Serial.println(F("{ \\ } : Servo Min/Center/Max"));
      Serial.println(F("@code : Time code"));
      Serial.println(F("[ b | n | v] : Brightness Full | Normal | Half"));
      Serial.println(F("z:default mode x:test"));
      Serial.println(F("0:dark 1:white 2:red 3:yellow 4:green 5:cyan 6:blue 7:magenta 8:orange 9:half"));
      Serial.println(F("q:strip0 w:strip1 e:strip2 r:strip3 t:strip4 y:strip5 u:strip6 i:strip7 p:All"));
      Serial.println(F("Q:lava W:cloud E:cm R:rb T:rainbow Y:rainbowstripe U:party I:heat"));        
      break;
    case Cmd_State_Default: fxc.fxState = FxState_Default;break;
    case Cmd_State_Test:    fxc.fxState = FxState_TestPattern;break;

    case Cmd_ServoMin:  ServoPose(POSE_ZERO); Serial.println(F("ServoMin")); break;
    case Cmd_ServoCenter: ServoPose(POSE_CENTER); Serial.println(F("ServoCenter")); break;
    case Cmd_ServoMax:  ServoPose(POSE_MAX); Serial.println(F("ServoMax")); break;
      
    case Cmd_PlayFromStart: trackStart(fxc, 0, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), FxTrackEndAction::StopAtEnd); break;
    case Cmd_PlayFrom:      fxc.fxState = FxState_PlayingTrack;break;
    case Cmd_PlayStop:      trackStop(fxc); break;

    case Cmd_SpeedNeg:      InstantEvent(fxc, fx_speed_neg, FxPaletteUpdateType::Once); break;
    case Cmd_SpeedPos:      InstantEvent(fxc, fx_speed_pos, FxPaletteUpdateType::Once); break;
    case Cmd_SpeedDec:      InstantEvent(fxc, fx_speed_dec, FxPaletteUpdateType::Once); break;
    case Cmd_SpeedInc:      InstantEvent(fxc, fx_speed_inc, FxPaletteUpdateType::Once); break;
    case Cmd_SpeedRst:      InstantEvent(fxc, fx_speed_0,   FxPaletteUpdateType::Once); break;

    case Cmd_Speed1:        InstantEvent(fxc, fx_speed_1,   FxPaletteUpdateType::Once); break;
    case Cmd_Speed2:        InstantEvent(fxc, fx_speed_2,   FxPaletteUpdateType::Once); break;
    case Cmd_Speed3:        InstantEvent(fxc, fx_speed_3,   FxPaletteUpdateType::Once); break;
    case Cmd_Speed4:        InstantEvent(fxc, fx_speed_4,   FxPaletteUpdateType::Once); break;
    
    case Cmd_ColorDark:     InstantEvent(fxc, fx_palette_dark,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorWhite:    InstantEvent(fxc, fx_palette_white,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorRed:      InstantEvent(fxc, fx_palette_red,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorYellow:   InstantEvent(fxc, fx_palette_yellow,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorGreen:    InstantEvent(fxc, fx_palette_green,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorCyan:     InstantEvent(fxc, fx_palette_cyan,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorBlue:     InstantEvent(fxc, fx_palette_blue,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorMagenta:  InstantEvent(fxc, fx_palette_magenta,  FxPaletteUpdateType::Once); break;
    case Cmd_ColorOrange:   InstantEvent(fxc, fx_palette_orange,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorHalf:     InstantEvent(fxc, fx_palette_half,     FxPaletteUpdateType::Once); break;

    case Cmd_ColorWhiteMagenta: InstantEvent(fxc, fx_palette_wm,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorWhiteCyan:    InstantEvent(fxc, fx_palette_wc,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorWhiteYellow:  InstantEvent(fxc, fx_palette_wy,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorWhiteBlue:    InstantEvent(fxc, fx_palette_wb,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorRedBlue:      InstantEvent(fxc, fx_palette_rb,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorCyanMagenta:  InstantEvent(fxc, fx_palette_cm,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorCyanBlue:     InstantEvent(fxc, fx_palette_cb,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorBlueMagenta:  InstantEvent(fxc, fx_palette_bm,      FxPaletteUpdateType::Once); break;

    case Cmd_ColorPulseDark:     InstantEvent(fxc, fx_palette_pulse_dark,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseWhite:    InstantEvent(fxc, fx_palette_pulse_white,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseRed:      InstantEvent(fxc, fx_palette_pulse_red,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseYellow:   InstantEvent(fxc, fx_palette_pulse_yellow,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseGreen:    InstantEvent(fxc, fx_palette_pulse_green,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseCyan:     InstantEvent(fxc, fx_palette_pulse_cyan,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseBlue:     InstantEvent(fxc, fx_palette_pulse_blue,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseMagenta:  InstantEvent(fxc, fx_palette_pulse_magenta,  FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseOrange:   InstantEvent(fxc, fx_palette_pulse_orange,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseHalf:     InstantEvent(fxc, fx_palette_pulse_half,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Dark:     InstantEvent(fxc, fx_palette_pulse2_dark,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2White:    InstantEvent(fxc, fx_palette_pulse2_white,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Red:      InstantEvent(fxc, fx_palette_pulse2_red,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Yellow:   InstantEvent(fxc, fx_palette_pulse2_yellow,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Green:    InstantEvent(fxc, fx_palette_pulse2_green,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Cyan:     InstantEvent(fxc, fx_palette_pulse2_cyan,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Blue:     InstantEvent(fxc, fx_palette_pulse2_blue,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Magenta:  InstantEvent(fxc, fx_palette_pulse2_magenta,  FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Orange:   InstantEvent(fxc, fx_palette_pulse2_orange,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Half:     InstantEvent(fxc, fx_palette_pulse2_half,   FxPaletteUpdateType::Once); break;
       
    case Cmd_ColorLava:           InstantEvent(fxc, fx_palette_lava,          FxPaletteUpdateType::Once); break;
    case Cmd_ColorCloud:          InstantEvent(fxc, fx_palette_cloud,         FxPaletteUpdateType::Once); break;
    case Cmd_ColorOcean:          InstantEvent(fxc, fx_palette_ocean,         FxPaletteUpdateType::Once); break;
    case Cmd_ColorForest:         InstantEvent(fxc, fx_palette_forest,        FxPaletteUpdateType::Once); break;
    case Cmd_ColorRainbow:        InstantEvent(fxc, fx_palette_rainbow,       FxPaletteUpdateType::Once); break;
    case Cmd_ColorRainbowstripe:  InstantEvent(fxc, fx_palette_rainbowstripe, FxPaletteUpdateType::Once); break;
    case Cmd_ColorParty:          InstantEvent(fxc, fx_palette_party,         FxPaletteUpdateType::Once); break;
    case Cmd_ColorHeat:           InstantEvent(fxc, fx_palette_heat,          FxPaletteUpdateType::Once); break;

    case Cmd_StripAll:            InstantEvent(fxc, fx_strip_all,     FxPaletteUpdateType::Once); break;
    case Cmd_StripNone:           InstantEvent(fxc, fx_strip_none,    FxPaletteUpdateType::Once); break;
    case Cmd_StripOdds:           InstantEvent(fxc, fx_strip_odds,    FxPaletteUpdateType::Once); break;
    case Cmd_StripEvens:          InstantEvent(fxc, fx_strip_evens,   FxPaletteUpdateType::Once); break;
    case Cmd_Strip0: fxc.stripMask = LEDS_0; break;
    case Cmd_Strip1: fxc.stripMask = LEDS_1; break;
    case Cmd_Strip2: fxc.stripMask = LEDS_2; break;
    case Cmd_Strip3: fxc.stripMask = LEDS_3; break;
    case Cmd_Strip4: fxc.stripMask = LEDS_4; break;
    case Cmd_Strip5: fxc.stripMask = LEDS_5; break;
    case Cmd_Strip6: fxc.stripMask = LEDS_6; break;
    case Cmd_Strip7: fxc.stripMask = LEDS_7; break;

    case Cmd_Particles_On:  fxc.SetParticlesRunning(true);break;
    case Cmd_Particles_Off: fxc.SetParticlesRunning(false);break;

    case Cmd_TransitionFast: InstantEvent(fxc, fx_transition_fast,   FxPaletteUpdateType::Once); break;
#if ENABLE_NEOPIXEL

    case Cmd_Brightness_Max: 
    {
      for (int strip=0;strip<NUM_STRIPS;strip++)
        neopixelSetBrightness(strip,BRIGHTNESS_LIMIT);
      break;
    }
    case Cmd_Brightness_Normal:
    {
      for (int strip=0;strip<NUM_STRIPS;strip++)
        neopixelSetBrightness(strip,BRIGHTNESS);
      break;
    }
    case Cmd_Brightness_Half:
    {
      for (int strip=0;strip<NUM_STRIPS;strip++)
        neopixelSetBrightness(strip,BRIGHTNESS/2);
      break;
    }
    
#endif  

    default: break;
  }
}
/*
void processCapturedText(FxController &fxc)
{
  if (captureMode == CaptureTimeCode)
  { 
    captureMode = CaptureNone;
    Serial.print(F("TimeCodeBuf( "));
    for (int i = 0; i < captureCount; i++)
    {
      Serial.print((char)captureBuffer[i]);    
      Serial.print(F(" "));
    }
    Serial.print(F(")"));
    captureBuffer[captureCount] = 0;
    Serial.print(F("=\""));
    Serial.print(captureBuffer);
    Serial.print(F("\""));
    unsigned long tc = atol(captureBuffer);
    Serial.print(F("TC:"));
    Serial.print(tc);
    int prevmatch = GetPreviousTimeCodeMatch(tc);    
    setTimecodeLastMatched(SongTrack_timecode(prevmatch));
    setTimecodeSongOffset(tc);  
    Serial.print(F(" vs t="));
    Serial.print(GetTime());
    Serial.print(F(", to="));
    Serial.print(getTimecodeTimeOffset());
    setTimecodeTimeOffset(millis());
    Serial.print(F(", "));
    Serial.print(getTimecodeLastMatched());
    Serial.print(F("="));
    Serial.print(getTimecodeSongOffset());
    Serial.print(F(",P:"));
    Serial.print(prevmatch);
    Serial.println(F(""));

    trackStart(fxc,tc, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), FxTrackEndAction::StopAtEnd);
  }
}
*/
void UserCommandInputDirect(FxController &fxc, int data)
{
  /*if (captureMode == CaptureTimeCode && data != 10 && data != 13)
  {
    if (captureCount < 15)
    {
      Serial.print(F("CC="));
      Serial.print(data);
      captureBuffer[captureCount] = (char)data;
      captureBuffer[captureCount+1] = 0;
      captureCount++;
    }
    return;
  }*/

  switch (data)
  {
   /* case '@':
      Serial.print(F("Capturing TimeCode"));
      captureCount = 0;
      //capturedTimeCode = "";
      captureMode = CaptureTimeCode;
      break;*/
    case '?': UserCommandExecute(fxc, Cmd_Help); break;

    case 'z': UserCommandExecute(fxc, Cmd_State_Default);break;
    case 'x': UserCommandExecute(fxc, Cmd_State_Test);break;
    
    case 'v': UserCommandExecute(fxc, Cmd_Brightness_Half);break;
    case 'b': UserCommandExecute(fxc, Cmd_Brightness_Max);break;
    case 'n': UserCommandExecute(fxc, Cmd_Brightness_Normal);break;

    case '{': UserCommandExecute(fxc, Cmd_ServoMin); break;
    case '\\':UserCommandExecute(fxc, Cmd_ServoCenter); break;
    case '}': UserCommandExecute(fxc, Cmd_ServoMax); break;
        
    case ')': UserCommandExecute(fxc, Cmd_PlayFromStart); break;
    case '`': UserCommandExecute(fxc, Cmd_PlayFrom); break;
    case '(': UserCommandExecute(fxc, Cmd_PlayStop); break;
    
    case '0': UserCommandExecute(fxc, Cmd_ColorDark); break;
    case '1': UserCommandExecute(fxc, Cmd_ColorWhite); break;
    case '2': UserCommandExecute(fxc, Cmd_ColorRed); break;
    case '3': UserCommandExecute(fxc, Cmd_ColorYellow); break;
    case '4': UserCommandExecute(fxc, Cmd_ColorGreen); break;
    case '5': UserCommandExecute(fxc, Cmd_ColorCyan); break;
    case '6': UserCommandExecute(fxc, Cmd_ColorBlue); break;
    case '7': UserCommandExecute(fxc, Cmd_ColorMagenta); break;
    case '8': UserCommandExecute(fxc, Cmd_ColorOrange); break;
    case '9': UserCommandExecute(fxc, Cmd_ColorHalf); break;

    case 'A': ComplexUserCommandInput(fxc, "wave"); break;
    case 'B': ComplexUserCommandInput(fxc, "dn"); break;
    case 'C': ComplexUserCommandInput(fxc, "up"); break;
    case 'D': ComplexUserCommandInput(fxc, "butt"); break;
    case 'E': ComplexUserCommandInput(fxc, "grr"); break;
    case 'F': ComplexUserCommandInput(fxc, "center"); break;
    case 'G': ComplexUserCommandInput(fxc, "p1"); break;
    case 'H': ComplexUserCommandInput(fxc, "pu"); break;
    case 'I': ComplexUserCommandInput(fxc, "pd"); break;
    case 'J': ComplexUserCommandInput(fxc, "ub"); break;
    case 'K': ComplexUserCommandInput(fxc, "uf"); break;
    case 'L': ComplexUserCommandInput(fxc, "go"); break;
    case 'M': ComplexUserCommandInput(fxc, "*hu");break;
    case 'N': ComplexUserCommandInput(fxc, "*hd"); break;
    case 'O': ComplexUserCommandInput(fxc, "*eu"); break;
    case 'P': ComplexUserCommandInput(fxc, "*ed"); break;
    case 'Q': if (fxc.select) ComplexUserCommandInput(fxc, "*wu"); else ComplexUserCommandInput(fxc, "ff"); break;
    case 'R': if (fxc.select) ComplexUserCommandInput(fxc, "*wd"); else ComplexUserCommandInput(fxc, "fg"); break;
    case 'S': ComplexUserCommandInput(fxc, "auto"); break;
    case 'T': ComplexUserCommandInput(fxc, "primal"); break;
    case 'U': ComplexUserCommandInput(fxc, "waking"); break;    
    case 'V': ComplexUserCommandInput(fxc, "ready"); break;
    case 'W': ComplexUserCommandInput(fxc, "sleep"); break;
    case 'X': ComplexUserCommandInput(fxc, "hop"); break;
    case 'Y': ComplexUserCommandInput(fxc, "gg"); break;
    case 'Z': ComplexUserCommandInput(fxc, "select"); break;
     
    case '!': ComplexUserCommandInput(fxc, "sa1"); break;
    case '%': ComplexUserCommandInput(fxc, "da1"); break;
    case '@': ComplexUserCommandInput(fxc, "sa2"); break;
    case '^': ComplexUserCommandInput(fxc, "da2"); break;
    case '#': ComplexUserCommandInput(fxc, "sa3"); break;
    case '&': ComplexUserCommandInput(fxc, "da3"); break;
    case '$': ComplexUserCommandInput(fxc, "sa4"); break;
    case '*': ComplexUserCommandInput(fxc, "da4"); break;

    
    //case 'q': UserCommandExecute(fxc, Cmd_ColorRedBlue);break;
//    case 'w': UserCommandExecute(fxc, Cmd_ColorCyanMagenta);break;
    case 'q': UserCommandExecute(fxc, Cmd_Strip0);break;
    case 'w': UserCommandExecute(fxc, Cmd_Strip1);break;
    case 'e': UserCommandExecute(fxc, Cmd_Strip2);break;
    case 'r': UserCommandExecute(fxc, Cmd_Strip3);break;
    case 't': UserCommandExecute(fxc, Cmd_Strip4);break;
    case 'y': UserCommandExecute(fxc, Cmd_Strip5);break;
    case 'u': UserCommandExecute(fxc, Cmd_Strip6);break;
    case 'i': UserCommandExecute(fxc, Cmd_Strip7);break;
    case 'o': UserCommandExecute(fxc, Cmd_StripNone);break;
    case 'p': UserCommandExecute(fxc, Cmd_StripAll);break;

    case 'a': UserCommandExecute(fxc, Cmd_ColorLava);break;
    case 's': UserCommandExecute(fxc, Cmd_ColorCloud);break;
    case 'd': UserCommandExecute(fxc, Cmd_ColorCyanMagenta);break;
    case 'f': UserCommandExecute(fxc, Cmd_ColorRedBlue);break;
    case 'g': UserCommandExecute(fxc, Cmd_ColorRainbow);break;
    case 'h': UserCommandExecute(fxc, Cmd_ColorRainbowstripe);break;
    case 'j': UserCommandExecute(fxc, Cmd_ColorParty);break;
    case 'k': UserCommandExecute(fxc, Cmd_ColorHeat);break;

    case '_': UserCommandExecute(fxc, Cmd_SpeedNeg);break;
    case '+': UserCommandExecute(fxc, Cmd_SpeedPos);break;
    case '-': UserCommandExecute(fxc, Cmd_SpeedDec);break;
    case '=': UserCommandExecute(fxc, Cmd_SpeedInc);break;
    case '~': UserCommandExecute(fxc, Cmd_SpeedRst);break;

    case '<': UserCommandExecute(fxc, Cmd_Particles_Off);break;
    case '>': UserCommandExecute(fxc, Cmd_Particles_On);break;


    case ',': break;
    case '.': break;
    case '/': break;
   

    case 10:
    case 13:
      break;
    case 0:
    case 225: break;
    default:
      Serial.print(F("unk:"));
      Serial.println(data);
      break;
  }
}

void UserCommandInput(FxController &fxc, int data)
{
  UserCommandInputDirect(fxc,data);
}

bool StringsEqual(String a, String b)
{
  if (a.length() != b.length())
  {
    Serial.println("Different length");
    return false;
  }
  for (int i=0;i<a.length();i++)
  {
    if (a[i] != b[i]) return false;
  }
  return true;
}

void ComplexUserCommandInput(FxController &fxc, String data)
{
  //Remove carriage returns; 
  if (data[data.length()-1]=='\n') data.remove(data.length()-1,1);
  if (data[data.length()-1]=='\r') data.remove(data.length()-1,1);

  if (data[0] == '!')
  {
    int x1 = ((int)data[1] - '0');
    int y1 = ((int)data[2] - '0');
    int x2 = ((int)data[3] - '0');
    int y2 = ((int)data[4] - '0');
    Serial.print(F("PplRect:"));
    Serial.print(x1);
    Serial.print(F(" "));
    Serial.print(y1);
    Serial.print(F(" "));
    Serial.print(x2);
    Serial.print(F(" "));
    Serial.print(y2);
    Serial.println();
    SetPeopleRect(x1*10,y1*10,x2*10,y2*10);
    SetPeopleRectSeenFlag(false);
  }
  else if (data.equals(F("POSES")))
  {
    for (int p=0;p<NUM_DB_POSES;p++)
    {
      Serial.print(F("POSE"));
      Serial.print(p);
      Serial.print(F(" "));
      for (int s=0;s<SERVO_NUM;s++)
      {    
        Serial.print(POSE_DB[p][s]);
        Serial.print(F(" "));
      }
      Serial.println();
    }
  }
  else if (data.equals(F("waking")))
  {  
    SetMindState(MIND_STATE_WAKING);
  }
  else if (data.equals(F("ff")))
  {
    int SPEED = 100;   
    const int POSE_CYCLE1[SERVO_NUM] { 89,44,109,-1,  89,49,79,-1,  89,44,109,-1,  89,49,79,-1 };
    const int POSE_CYCLE2[SERVO_NUM] { 89,49,99,-1,   89,54,80,-1,  89,54,80,-1,   89,49,79,-1 };
    const int POSE_CYCLE3[SERVO_NUM] { 89,54,80,-1,   89,65,103,-1, 89,65,103,-1,  89,54,80,-1 };
    const int POSE_CYCLE4[SERVO_NUM] { 89,65,103,-1,  89,49,79,-1,  89,44,109,-1,  89,65,103,-1 };
    const int POSE_CYCLE5[SERVO_NUM] { 89,44,109,-1,  89,49,79,-1,  89,44,109,-1,  89,49,79,-1 };
    ServoPose(POSE_CYCLE1); delay(SPEED);   
    ServoPose(POSE_CYCLE2); delay(SPEED);
    ServoPose(POSE_CYCLE3); delay(SPEED);      
    ServoPose(POSE_CYCLE4); delay(SPEED);      
    ServoPose(POSE_CYCLE5); delay(SPEED);      
  }
  else if (data.equals(F("fg")))
  {
    int SPEED = 100;   
    const int POSE_CYCLE1[SERVO_NUM] { 89,44,109,-1,  89,49,79,-1,  89,44,109,-1,  89,49,79,-1 };
    const int POSE_CYCLE2[SERVO_NUM] { 89,49,99,-1,   89,54,80,-1,  89,54,80,-1,   89,49,79,-1 };
    const int POSE_CYCLE3[SERVO_NUM] { 89,54,80,-1,   89,65,103,-1, 89,65,103,-1,  89,54,80,-1 };
    const int POSE_CYCLE4[SERVO_NUM] { 89,65,103,-1,  89,49,79,-1,  89,44,109,-1,  89,65,103,-1 };
    const int POSE_CYCLE5[SERVO_NUM] { 89,44,109,-1,  89,49,79,-1,  89,44,109,-1,  89,49,79,-1 };
    ServoPose(POSE_CYCLE1); delay(SPEED);      
    ServoPose(POSE_CYCLE4); delay(SPEED);      
    ServoPose(POSE_CYCLE3); delay(SPEED);
    ServoPose(POSE_CYCLE2); delay(SPEED);   
    ServoPose(POSE_CYCLE5); delay(SPEED);      
  }
  else if (data.equals(F("gg")))
  {
    int SPEED = 250;
#define GGPOSE1 89,49,84    
    const int POSE_CYCLE0[SERVO_NUM] { 89,50,87,-1,  89,49,74,-1,  89,50,87,-1,  89,49,74,-1 };
    const int POSE_CYCLE1[SERVO_NUM] { GGPOSE1 ,-1,  89,49,74, -1,  89,50,87,-1,  89,49,74,-1 };
    const int POSE_CYCLE2[SERVO_NUM] { GGPOSE1,-1,  GGPOSE1 ,-1,  89,50,87,-1,  89,49,74,-1 };
    const int POSE_CYCLE3[SERVO_NUM] { GGPOSE1,-1,  89,49,74,-1,  GGPOSE1 ,-1,  89,64,65,-1 };
    const int POSE_CYCLE4[SERVO_NUM] { 89,50,87,-1,  89,49,74,-1,  89,50,87,-1,  GGPOSE1 ,-1 };
    const int POSE_CYCLE5[SERVO_NUM] { 89,50,87,-1,  89,49,74,-1,  89,50,87,-1,  89,49,74,-1 };
    ServoPose(POSE_CYCLE0); delay(SPEED);
    ServoPose(POSE_CYCLE1); delay(SPEED);      
    ServoPose(POSE_CYCLE2); delay(SPEED);      
    ServoPose(POSE_CYCLE3); delay(SPEED);
    ServoPose(POSE_CYCLE4); delay(SPEED);   
    ServoPose(POSE_CYCLE5); delay(SPEED);      
  }
  else if (data.equals(F("hop")))
  {
    int SPEED = 250;
#define GGCROUCHF 89,36,46,-1
#define GGCROUCHB 89,36,61,-1
    const int POSE_CYCLE1[SERVO_NUM] { GGCROUCHB, GGCROUCHF, GGCROUCHB, GGCROUCHF };
    const int POSE_CYCLE2[SERVO_NUM] { -1,65,126,-1, -1,61,111,-1, -1,65,126,-1, -1,61,111,-1 };
    const int POSE_CYCLE3[SERVO_NUM] { GGCROUCHB, GGCROUCHF, GGCROUCHB, GGCROUCHF };
    ServoPose(POSE_CYCLE1); delay(1000);      
    ServoPose(POSE_CYCLE2); delay(1000);
    ServoPose(POSE_CYCLE3); delay(SPEED);   
  }
  else if (data.equals(F("ready")))
  {  
    Serial.println(F("POSES"));//Time to call and get our poses
    SetMindState(MIND_STATE_READY);
    delay(250);
    Serial.println("SNature");
  }
  else if (data.equals(F("center")))
  {
    ServoPose(POSE_CENTER);
    delay(250);
    Serial.println("SNerv");
  }
  else if (data.equals(F("go")))
  {
    Serial.println(F("Primal.."));
    ServoPose(POSE_CENTER);
    ServoPoseLerpTo(POSE_PAWSUP, 1); 
    ServoPoseLerpTo(POSE_HIPS_ORIGIN, 1); 
    ServoPoseLerpTo(POSE_ELBOW_MIN, 1);
    SetMindState(MIND_STATE_READY);
  }
  else if (data.equals(F("sleep")))
  {
    ComplexUserCommandInput(fxc,"dn");
    SetMindState(MIND_STATE_ASLEEP);
    delay(250);
    Serial.println("SPurr");
  }
  else if (data.equals(F("auto")))
  {
    const int POSE_AUTO_BACK[SERVO_NUM]  {-1,-1,-1,-1, 98,78,119,-1, -1,-1,-1,-1, 88,50,79,-1};
    const int POSE_AUTO_FRONT[SERVO_NUM] {98,35,93,-1, 98,78,119,-1, 98,35,93,-1, 88,50,79,-1};
    ServoPoseLerpTo(POSE_AUTO_BACK, 4);  
    ServoPoseLerpTo(POSE_AUTO_FRONT, 4); 
    SetMindState(MIND_STATE_AUTONOMOUS);
  }
  else if (data.indexOf("l0") != -1) { SetPeopleCount(0); }
  else if (data.indexOf("l1") != -1) { SetPeopleCount(1); }
  else if (data.indexOf("l2") != -1) { SetPeopleCount(2); }
  else if (data.indexOf("l3") != -1) { SetPeopleCount(3); }
  else if (data.indexOf("l4") != -1) { SetPeopleCount(4); }
  else if (data.indexOf("l5") != -1) { SetPeopleCount(5); }
  else if (data.indexOf("l6") != -1) { SetPeopleCount(6); }
  else if (data.indexOf("l7") != -1) { SetPeopleCount(7); }
  else if (data.equals(F("??")))
  {
    Serial.println(F("Add u/d"));
    Serial.println(F(" sleep/waking/ready/go/auto"));
    Serial.println(F(" dn/up/butt/grr"));
    Serial.println(F("--------------------------"));
    Serial.println(F("Combo:"));
    Serial.println(F(" (*+h/e/w) all hips/elbows/wrists"));
    Serial.println(F("Combo:"));
    Serial.println(F(" (l+h/e/w) left hips/elbows/wrists"));
    Serial.println(F(" (r+h/e/w) right hips/elbows/wrists"));
    Serial.println(F(" (f+h/e/w) front hips/elbows/wrists"));
    Serial.println(F(" (b+h/e/w) back hips/elbows/wrists"));
    Serial.println(F("Specific:"));
    Serial.println(F(" (fl+h/e/w) front left hip/elbow/wrist"));
    Serial.println(F(" (fr+h/e/w) front right hip/elbow/wirst"));
    Serial.println(F(" (bl+h/e/w) back left hip/elbow/wrist"));
    Serial.println(F(" (br+h/e/w) back right hip/elbow/wrist"));
  }
  else if (data.equals(F("dn"))) { 
    ServoPoseLerpTo(POSE_PAWSUP, 4); 
    ServoPoseLerpTo(POSE_HIPS_ORIGIN, 3); 
    ServoPoseLerpTo(POSE_ELBOW_MIN, 1);
    Serial.println("SPurr");//Time to call and get our poses
    delay(250);
  } 
  else if (data.equals(F("up"))) { 
    ServoPoseLerpTo(POSE_UP_BACK, 1); 
    delay(250);
    ServoPoseLerpTo(POSE_UP, 1); 
    Serial.println("SThunder");
    delay(250);
  }
  else if (data.equals(F("butt"))) { 
    ServoPoseLerpTo(POSE_UP_FRONT,4); 
    delay(250);
    ServoPoseLerpTo(POSE_UP_BACK,4); 
    delay(250);
    ServoPoseLerpTo(POSE_FRONT_PAWSDN,2);
    Serial.println("SHowl");
  }
  else if (data.equals(F("wave"))) { 
    ServoPoseLerpTo(POSE_UP_FRONT,4); 
    delay(250);
    ServoPoseLerpTo(POSE_UP_BACK,4); 
    delay(250);
    ServoPoseLerpTo(POSE_FRONT_PAWSDN,2);
    Serial.println("SMeow");
    delay(250);
    ServoPoseLerpTo(POSE_FRONT_RIGHT_PAWUP,2);
    delay(250);
    ServoPoseLerpTo(POSE_FRONT_RIGHT_PAWDN,2);
    delay(250);
    ServoPoseLerpTo(POSE_FRONT_RIGHT_PAWUP,2);
    delay(250);
    ServoPoseLerpTo(POSE_FRONT_RIGHT_PAWDN,2);
    delay(250);
    ServoPoseLerpTo(POSE_UP_FRONT,1); 
    delay(250);
    ServoPoseLerpTo(POSE_FRONT_PAWSDN,2);
  }  
  else if (data.equals(F("grr"))) { 
    ServoPoseLerpTo(POSE_UP_BACK, 1); 
    Serial.println("SHiss");
    delay(250);
    ServoPoseLerpTo(POSE_AGGRESSIVE, 1); 
    }
  else if (data.equals(F("ub"))) { ServoPoseLerpTo(POSE_UP_BACK, 1); }
  else if (data.equals(F("uf"))) { ServoPoseLerpTo(POSE_UP_FRONT, 1); }
  else if (data.equals(F("p1"))) { ServoPose(POSE_CENTER); }
  else if (data.equals(F("pu"))) { ServoPose(POSE_PAWSUP); }
  else if (data.equals(F("pd"))) { ServoPose(POSE_PAWSDN); }
  else if (data.equals(F("p0"))) { ServoPose(POSE_ZERO); }
  else if (data.equals(F("p9"))) { ServoPose(POSE_MAX); }

 else if (data.equals(F("sa1"))) { fxc.select |= 1; }
 else if (data.equals(F("da1"))) { fxc.select &= ~1; }
 else if (data.equals(F("sa2"))) { fxc.select |= 2; }
 else if (data.equals(F("da2"))) { fxc.select &= ~2; }
 else if (data.equals(F("sa3"))) { fxc.select |= 4; }
 else if (data.equals(F("da3"))) { fxc.select &= ~4; }
 else if (data.equals(F("sa4"))) { fxc.select |= 8; }
 else if (data.equals(F("da4"))) { fxc.select &= ~8; }
 
  else if (data.equals(F("select")))
  {
    FoxenMindState mindState = GetMindState();
    mindState = (FoxenMindState)((int)mindState + 1);

    if (mindState == MIND_STATE_WAKING)
      mindState = MIND_STATE_READY;
    if (mindState == MIND_STATE_TRACK)
      mindState = MIND_STATE_AUTONOMOUS;
    if (mindState == MIND_STATE_LAST)
      mindState = MIND_STATE_ASLEEP;

    if (mindState == MIND_STATE_AUTONOMOUS)
    {
      ComplexUserCommandInput(fxc,F("auto"));
      mindState = MIND_STATE_AUTONOMOUS;
    }
      
    SetMindState(mindState);
    PrintMindState();
  }  
  else if (data.equals(F("*hu"))) { 
    int bits = fxc.select;
    if (bits&SERVOS_LEFT_BACK) ServoInc(SERVO_LEFT_BACK_HIP); 
    if (bits&SERVOS_LEFT_FRONT) ServoInc(SERVO_LEFT_FRONT_HIP); 
    if (bits&SERVOS_RIGHT_BACK) ServoInc(SERVO_RIGHT_BACK_HIP); 
    if (bits&SERVOS_RIGHT_FRONT) ServoInc(SERVO_RIGHT_FRONT_HIP); 
    delay(250); Serial.println("S*Hu"); 
    }
  else if (data.equals(F("*hd"))) { 
    int bits = fxc.select;
    if (bits&SERVOS_LEFT_BACK) ServoDec(SERVO_LEFT_BACK_HIP); 
    if (bits&SERVOS_LEFT_FRONT) ServoDec(SERVO_LEFT_FRONT_HIP); 
    if (bits&SERVOS_RIGHT_BACK) ServoDec(SERVO_RIGHT_BACK_HIP); 
    if (bits&SERVOS_RIGHT_FRONT) ServoDec(SERVO_RIGHT_FRONT_HIP); 
    delay(250); Serial.println("S*Hd"); 
  }
  else if (data.equals(F("*eu"))) { 
    int bits = fxc.select;
    if (bits&SERVOS_LEFT_BACK) ServoInc(SERVO_LEFT_BACK_ELBOW); 
    if (bits&SERVOS_LEFT_FRONT) ServoInc(SERVO_LEFT_FRONT_ELBOW); 
    if (bits&SERVOS_RIGHT_BACK) ServoInc(SERVO_RIGHT_BACK_ELBOW); 
    if (bits&SERVOS_RIGHT_FRONT) ServoInc(SERVO_RIGHT_FRONT_ELBOW); 
    delay(250); Serial.println("S*Eu"); 
    }
  else if (data.equals(F("*ed"))) { 
    int bits = fxc.select;
    if (bits&SERVOS_LEFT_BACK) ServoDec(SERVO_LEFT_BACK_ELBOW); 
    if (bits&SERVOS_LEFT_FRONT) ServoDec(SERVO_LEFT_FRONT_ELBOW); 
    if (bits&SERVOS_RIGHT_BACK) ServoDec(SERVO_RIGHT_BACK_ELBOW); 
    if (bits&SERVOS_RIGHT_FRONT) ServoDec(SERVO_RIGHT_FRONT_ELBOW); 
    delay(250); Serial.println("S*Ed"); 
    }
  else if (data.equals(F("*wu"))) { 
    int bits = fxc.select;
    if (bits&SERVOS_LEFT_BACK) ServoInc(SERVO_LEFT_BACK_WRIST); 
    if (bits&SERVOS_LEFT_FRONT) ServoInc(SERVO_LEFT_FRONT_WRIST); 
    if (bits&SERVOS_RIGHT_BACK) ServoInc(SERVO_RIGHT_BACK_WRIST); 
    if (bits&SERVOS_RIGHT_FRONT) ServoInc(SERVO_RIGHT_FRONT_WRIST); 
    delay(250); Serial.println("S*Wu"); 
    }
  else if (data.equals(F("*wd"))) {
    int bits = fxc.select;
    if (bits&SERVOS_LEFT_BACK) ServoDec(SERVO_LEFT_BACK_WRIST); 
    if (bits&SERVOS_LEFT_FRONT) ServoDec(SERVO_LEFT_FRONT_WRIST); 
    if (bits&SERVOS_RIGHT_BACK) ServoDec(SERVO_RIGHT_BACK_WRIST); 
    if (bits&SERVOS_RIGHT_FRONT) ServoDec(SERVO_RIGHT_FRONT_WRIST); 
    delay(250); Serial.println("S*Wd"); 
    }
  
  else if (data.equals(F("lhu"))) { ServoInc(SERVO_LEFT_BACK_HIP); ServoInc(SERVO_LEFT_FRONT_HIP); }
  else if (data.equals(F("lhd"))) { ServoDec(SERVO_LEFT_BACK_HIP); ServoDec(SERVO_LEFT_FRONT_HIP); }
  else if (data.equals(F("rhu"))) { ServoInc(SERVO_RIGHT_BACK_HIP); ServoInc(SERVO_RIGHT_FRONT_HIP); }
  else if (data.equals(F("rhd"))) { ServoDec(SERVO_RIGHT_BACK_HIP); ServoDec(SERVO_RIGHT_FRONT_HIP); }
  else if (data.equals(F("leu"))) { ServoInc(SERVO_LEFT_BACK_ELBOW); ServoInc(SERVO_LEFT_FRONT_ELBOW); }
  else if (data.equals(F("led"))) { ServoDec(SERVO_LEFT_BACK_ELBOW); ServoDec(SERVO_LEFT_FRONT_ELBOW); }
  else if (data.equals(F("reu"))) { ServoInc(SERVO_RIGHT_BACK_ELBOW); ServoInc(SERVO_RIGHT_FRONT_ELBOW); }
  else if (data.equals(F("red"))) { ServoDec(SERVO_RIGHT_BACK_ELBOW); ServoDec(SERVO_RIGHT_FRONT_ELBOW); }
  else if (data.equals(F("lwu"))) { ServoInc(SERVO_LEFT_BACK_WRIST); ServoInc(SERVO_LEFT_FRONT_WRIST); }
  else if (data.equals(F("lwd"))) { ServoDec(SERVO_LEFT_BACK_WRIST); ServoDec(SERVO_LEFT_FRONT_WRIST); }
  else if (data.equals(F("rwu"))) { ServoInc(SERVO_RIGHT_BACK_WRIST); ServoInc(SERVO_RIGHT_FRONT_WRIST); }
  else if (data.equals(F("rwd"))) { ServoDec(SERVO_RIGHT_BACK_WRIST); ServoDec(SERVO_RIGHT_FRONT_WRIST); }

  else if (data.equals(F("fhu"))) { ServoInc(SERVO_LEFT_FRONT_HIP);   ServoInc(SERVO_RIGHT_FRONT_HIP); }
  else if (data.equals(F("fhd"))) { ServoDec(SERVO_LEFT_FRONT_HIP);   ServoDec(SERVO_RIGHT_FRONT_HIP); }
  else if (data.equals(F("bhu"))) { ServoInc(SERVO_LEFT_BACK_HIP);    ServoInc(SERVO_RIGHT_BACK_HIP); }
  else if (data.equals(F("bhd"))) { ServoDec(SERVO_LEFT_BACK_HIP);    ServoDec(SERVO_RIGHT_BACK_HIP); }
  else if (data.equals(F("feu"))) { ServoInc(SERVO_LEFT_FRONT_ELBOW); ServoInc(SERVO_RIGHT_FRONT_ELBOW); }
  else if (data.equals(F("fed"))) { ServoDec(SERVO_LEFT_FRONT_ELBOW); ServoDec(SERVO_RIGHT_FRONT_ELBOW); }
  else if (data.equals(F("beu"))) { ServoInc(SERVO_LEFT_BACK_ELBOW);  ServoInc(SERVO_RIGHT_BACK_ELBOW); }
  else if (data.equals(F("bed"))) { ServoDec(SERVO_LEFT_BACK_ELBOW);  ServoDec(SERVO_RIGHT_BACK_ELBOW); }
  else if (data.equals(F("fwu"))) { ServoInc(SERVO_LEFT_FRONT_WRIST); ServoInc(SERVO_RIGHT_FRONT_WRIST); }
  else if (data.equals(F("fwd"))) { ServoDec(SERVO_LEFT_FRONT_WRIST); ServoDec(SERVO_RIGHT_FRONT_WRIST); }
  else if (data.equals(F("bwu"))) { ServoInc(SERVO_LEFT_BACK_WRIST);  ServoInc(SERVO_RIGHT_BACK_WRIST); }
  else if (data.equals(F("bwd"))) { ServoDec(SERVO_LEFT_BACK_WRIST);  ServoDec(SERVO_RIGHT_BACK_WRIST); }

  else if (data.equals(F("flhu")) || data.equals(F("lfhu"))) { ServoInc(SERVO_LEFT_FRONT_HIP);  }
  else if (data.equals(F("flhd")) || data.equals(F("flhd"))) { ServoDec(SERVO_LEFT_FRONT_HIP);  }
  else if (data.equals(F("fleu")) || data.equals(F("fleu"))) { ServoInc(SERVO_LEFT_FRONT_ELBOW);  }
  else if (data.equals(F("fled")) || data.equals(F("fled"))) { ServoDec(SERVO_LEFT_FRONT_ELBOW);  }
  else if (data.equals(F("flwu")) || data.equals(F("flwu"))) { ServoInc(SERVO_LEFT_FRONT_WRIST);  }
  else if (data.equals(F("flwd")) || data.equals(F("flwd"))) { ServoDec(SERVO_LEFT_FRONT_WRIST);  }
  else if (data.equals(F("frhu")) || data.equals(F("frhu"))) { ServoInc(SERVO_RIGHT_FRONT_HIP);  }
  else if (data.equals(F("frhd")) || data.equals(F("frhd"))) { ServoDec(SERVO_RIGHT_FRONT_HIP);  }
  else if (data.equals(F("freu")) || data.equals(F("freu"))) { ServoInc(SERVO_RIGHT_FRONT_ELBOW);  }
  else if (data.equals(F("fred")) || data.equals(F("fred"))) { ServoDec(SERVO_RIGHT_FRONT_ELBOW);  }
  else if (data.equals(F("frwu")) || data.equals(F("frwu"))) { ServoInc(SERVO_RIGHT_FRONT_WRIST);  }
  else if (data.equals(F("frwd")) || data.equals(F("frwd"))) { ServoDec(SERVO_RIGHT_FRONT_WRIST);  }

  else if (data.equals(F("blhu")) || data.equals(F("lbhu"))) { ServoInc(SERVO_LEFT_BACK_HIP);  }
  else if (data.equals(F("blhd")) || data.equals(F("lbhd"))) { ServoDec(SERVO_LEFT_BACK_HIP);  }
  else if (data.equals(F("bleu")) || data.equals(F("lbeu"))) { ServoInc(SERVO_LEFT_BACK_ELBOW);  }
  else if (data.equals(F("bled")) || data.equals(F("lbed"))) { ServoDec(SERVO_LEFT_BACK_ELBOW);  }
  else if (data.equals(F("blwu")) || data.equals(F("lbwu"))) { ServoInc(SERVO_LEFT_BACK_WRIST);  }
  else if (data.equals(F("blwd")) || data.equals(F("lbwd"))) { ServoDec(SERVO_LEFT_BACK_WRIST);  }
  else if (data.equals(F("brhu")) || data.equals(F("rbhu"))) { ServoInc(SERVO_RIGHT_BACK_HIP);  }
  else if (data.equals(F("brhd")) || data.equals(F("rbhd"))) { ServoDec(SERVO_RIGHT_BACK_HIP);  }
  else if (data.equals(F("breu")) || data.equals(F("rbeu"))) { ServoInc(SERVO_RIGHT_BACK_ELBOW);  }
  else if (data.equals(F("bred")) || data.equals(F("rbed"))) { ServoDec(SERVO_RIGHT_BACK_ELBOW);  }
  else if (data.equals(F("brwu")) || data.equals(F("rbwu"))) { ServoInc(SERVO_RIGHT_BACK_WRIST);  }
  else if (data.equals(F("brwd")) || data.equals(F("rbwd"))) { ServoDec(SERVO_RIGHT_BACK_WRIST);  }

}
