#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "FoxenDisplay.h"

void FoxenLcd::Startup()
{
  Serial.println("FoxenLCD startup");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  Serial.println("FoxenLCD ok");
}

void FoxenLcd::DrawStateName(FoxenState state)
{
  String msg = "";
  switch (state)
  {
    case FoxenState_Asleep:  msg = F("asleep"); break;
    case FoxenState_Waking:  msg = F("waking"); break;
    case FoxenState_Awake:   msg = F("awake"); break;
    case FoxenState_Focused: msg = F("focused"); break;
  }
  display.print(msg);
}

void FoxenLcd::DrawSpinner(int spin)
{
//  char[] spinner = F("-/|\\-/|\\");
  switch (spin)
  {
    case 0: display.print(F("-")); break;
    case 1: display.print(F("/")); break;
    case 2: display.print(F("|")); break;
    case 3: display.print(F("\\")); break;
    case 4: display.print(F("-")); break;
    case 5: display.print(F("/")); break;
    case 6: display.print(F("|")); break;
    case 7: display.print(F("\\")); break;
  }
}

void FoxenLcd::DrawTime()
{
  signed long secondsOld =  (signed long)millis() / 1000;
  signed long hrs  = secondsOld / 360;
  signed long mins = (secondsOld - (hrs * 360)) / 60;
  signed long secs = secondsOld % 60;
  int len = 2;
  if (mins > 9) len++;
  if (mins > 99) len++;
  if (secs > 9) len++;

  display.setCursor(126 - len * 8, 0);

  display.print(mins);
  display.print(F(":"));
  display.print(secs);
}

void FoxenLcd::DrawState(int state, int tick)
{
  switch (state)
  {
    case FoxenState_Asleep:  display.print(F("_-.-_")); break;
    case FoxenState_Waking:  display.print(F("=v.v=")); break;
    case FoxenState_Awake:   display.print(F("=^.^=")); break;
    case FoxenState_Focused: display.print(F("=O.O=")); break;
  }
}

void FoxenLcd::DrawLog()
{
  display.print(log);
}

void FoxenLcd::Draw()
{
  display.clearDisplay();

  //Line 1
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(name);
  display.print(F(" "));
  DrawStateName(foxenstate);
  DrawTime();

  //Line 2
  display.setCursor(0, 8);
//  display.print(F("udist: "));
//  display.println(ultraDistance);

  //display.setCursor(0, 16);
  if (ultraDistance < 100)
  {
   //float distScale = (float)(ultraDistance / 1000.0f)/4;
   
   int barDistance = (15-ultraDistance / 4);
   for (int i=0;i<barDistance;i++)
   {
     //DrawSpinner( ((tick) / 2) % 8);
     display.print(F("#"));
   }
  }
  display.println();

  display.print(F("A "));
  display.print(accelerationX);
  display.print(F(" "));
  display.print(accelerationY);
  display.print(F(" "));
  display.print(accelerationZ);
  display.println();
  display.print(F("G "));
  display.print(gyroX);
  display.print(F(" "));
  display.print(gyroY);
  display.print(F(" "));
  display.print(gyroZ);
  display.println();
  
  //DrawSpinner((tick / 2) % 8);
  //display.print(F(" "));  
  //DrawLog();
  display.display();
  tick++;
}
