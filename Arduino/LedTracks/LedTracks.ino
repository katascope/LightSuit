/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
// LightDrive : A time-track event system for Addressable LED
// Purpose is for a wearable dance-synchronized lightsuit.
#include "Config.h"
#include "Fx.h"
#include "Track.h"
#include "Cmd.h"
#include "State.h"
#include "Devices.h"
static FxController fxController;

#if ENABLE_LCD
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "FoxenDisplay.h"
static FoxenLcd lcd;
#endif

#if ENABLE_ULTRASOUND
#include "FoxenUltrasound.h"

static FoxenUltrasound ultrasound;
#endif

#if ENABLE_IMU
#include "IMU.h"
static FIMU fimu;
#endif

#if ENABLE_SERVOS
#include "Servos.h"
#endif 

#if ENABLE_EMOTION
#include "Emotion.h"
static EmotionalCore emotions;
#endif

static unsigned long lastTimeDisplay = 0;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print(DeviceName);
  Serial.print(F("Serial init: "));
  Serial.println(SERIAL_BAUD_RATE);
  
#if SYSTEM_NANO_33_BLE
  Serial.println(F("System: Arduino Nano 33 BLE"));
#elif SYSTEM_NANO_33_IOT
  Serial.println(F("System: Arduino Nano 33 IOT"));
#elif SYSTEM_UNO
  Serial.println(F("System: Arduino UNO"));
#elif SYSTEM_NANO
  Serial.println(F("System: Arduino Nano"));
#else
  Serial.println(F("System: UNKNOWN"));
#endif

#if ENABLE_LCD
  lcd.Startup();
  lcd.SetCursor(0,0);
  lcd.Print(DeviceName);
  lcd.SetCursor(1,0);
  lcd.Print(F("Booting up"));
#endif

#if ENABLE_TRACK_CHECK
  if (trackHasLinearTime())
    Serial.println(F("Track Linear Check = OK"));
  else {
    Serial.println(F("Track Linear Check = FAILED"));
    return;
  }
#endif

#if ENABLE_MEMORYUSAGE
  Serial.println(F("MemoryUsage"));
  MEMORY_PRINT_STACKSIZE
  MEMORY_PRINT_HEAPSIZE
#endif  

#if ENABLE_NEOPIXEL
  Serial.println(F("Delaying 3 seconds for LEDs."));
  delay( 3000 ); // power-up safety delay
  neopixelSetup();
  for (int strip=0;strip<NUM_STRIPS;strip++)
    for (int led=0;led<fxController.strip[strip]->numleds;led++)
      fxController.strip[strip]->palette[led] = 0;
  Serial.print(F("NeoPixel init: "));
  Serial.print(F(" LEDs on pin "));
  Serial.println(LED_PIN);
#else
  Serial.println(F("No NeoPixel init"));
#endif

#if ENABLE_BLE
  Serial.println(F("BLE init"));
  bleSetup();
#else
  Serial.println(F("No BLE init"));
#endif

  fxController.fxState = STARTUP_STATE;

  if (fxController.fxState == FxState_TestPattern)
  { 
    Serial.println("Setting test pattern.");
    FxEventProcess(fxController, fx_palette_drb);
  }

  if (fxController.fxState == FxState_PlayingTrack)
  {
    fxController.fxTrackEndAction = FxTrackEndAction::LoopAtEnd;
    trackStart(fxController, 0, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), fxController.fxTrackEndAction);
  }
  else Serial.println(F("Lightstrips OK"));
#if ENABLE_NEOPIXEL
//Display brightness levels
  Serial.print(F("Brightness = { "));
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    fxController.strip[strip]->brightness = BRIGHTNESS;
    neopixelSetBrightness(strip,fxController.strip[strip]->brightness);
    Serial.print(fxController.strip[strip]->brightness);
    Serial.print(F(" "));
  }
  Serial.println(F(" }"));
#endif

#if ENABLE_ULTRASOUND
  ultrasound.Startup();
#endif

#if ENABLE_IMU
  fimu.Startup();
#endif

#if ENABLE_SERVOS
  ServoStartup();
#endif

#if ENABLE_MEMORYUSAGE
  emotions.Startup();
#endif  


UserCommandExecute(fxController, Cmd_Brightness_Half); 
UserCommandExecute(fxController, Cmd_ColorDark); 

  Serial.println("Setup complete.");
}

void UpdatePalette()
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

void loop()
{
 
  while (Serial.available())    
    UserCommandInput(fxController, Serial.read());

#if ENABLE_BLE
  blePoll(fxController);
#endif

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
      UpdatePalette();
      
      fxController.lastTimeLedUpdate = t;
      
      for (int strip=0;strip<NUM_STRIPS;strip++)
      {
        if (fxController.strip[strip]->fxPaletteUpdateType == FxPaletteUpdateType::Once)
          fxController.strip[strip]->fxPaletteUpdateType = FxPaletteUpdateType::Done;
      }
    }
  }

#if ENABLE_IMU
  fimu.Poll();
#if ENABLE_LCD
  lcd.accelerationX = fimu.accelerationX;
  lcd.accelerationY = fimu.accelerationY;
  lcd.accelerationZ = fimu.accelerationZ;
  lcd.gyroX = fimu.gyroX;
  lcd.gyroY = fimu.gyroY;
  lcd.gyroZ = fimu.gyroZ;
#endif  
#endif  

#if ENABLE_ULTRASOUND
  ultrasound.Update();
  int distance = ultrasound.GetDistance();
  if (distance == 0) { }
  else if (distance < 10) { UserCommandExecute(fxController, Cmd_ColorRed);}
  else if (distance < 19) {UserCommandExecute(fxController, Cmd_ColorOrange);}
  else if (distance < 29) { UserCommandExecute(fxController, Cmd_ColorYellow);}
  else if (distance < 39) { UserCommandExecute(fxController, Cmd_ColorGreen);}
  else {UserCommandExecute(fxController, Cmd_ColorMagenta);} 
#endif  

#if ENABLE_LCD
  lcd.ultraDistance = ultrasound.GetDistance();
  int distance = ultrasound.GetDistance();
  if (distance == 0) { }
  else if (distance < 10) { lcd.log="Freeze";}
  else if (distance < 19) { lcd.log="Danger";}
  else if (distance < 29) { lcd.log="Warning"; }
  else if (distance < 39) { lcd.log="Aware";}
  else {lcd.log="Open";} 
  lcd.Draw();
#endif  

#if ENABLE_EMOTION
  emotions.Poll(fxController, ultrasound.GetDistance());
#endif

//Display status once a second
  unsigned long t =  millis();
  if (t - lastTimeDisplay > 1000)//delay to let bluetooth get data
  {      
    if (fxController.fxState != FxState_PlayingTrack)
    {
      Serial.print(DeviceName);
#if ENABLE_EMOTION
      Serial.print(F(", Emo="));
      Serial.print(emotions.GetCurrentFeelingName());
#endif
      Serial.print(F(", Ult="));
      Serial.print(ultrasound.GetDistance());
      Serial.print(F(" "));
      FxDisplayStatus(fxController);            
      Serial.println();
    }
    lastTimeDisplay = t;
  }
}
