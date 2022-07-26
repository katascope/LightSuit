/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#include "Config.h"
#include "Fx.h"
#include "Devices.h"

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//WS2811 - led dangly lights

#if ENABLE_NEOPIXEL
#include <Adafruit_NeoPixel.h>
static Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(NUM_LEDS_0, LED_PIN+0, NEO_GRB + NEO_KHZ800);
#if ENABLE_MULTISTRIP
static Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS_1, LED_PIN+1, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS_2, LED_PIN+2, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS_3, LED_PIN+3, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUM_LEDS_4, LED_PIN+4, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(NUM_LEDS_5, LED_PIN+5, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(NUM_LEDS_6, LED_PIN+6, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(NUM_LEDS_7, LED_PIN+7, NEO_GRB + NEO_KHZ800);
#endif
void neopixelSetup()
{
  strip0.begin();
  strip0.setBrightness(BRIGHTNESS);
#if ENABLE_MULTISTRIP  
  strip1.begin();
  strip1.setBrightness(BRIGHTNESS);
  strip2.begin();
  strip2.setBrightness(BRIGHTNESS);
  strip3.begin();
  strip3.setBrightness(BRIGHTNESS);
  strip4.begin();
  strip4.setBrightness(BRIGHTNESS);
  strip5.begin();
  strip5.setBrightness(BRIGHTNESS);
  strip6.begin();
  strip6.setBrightness(BRIGHTNESS);
  strip7.begin();
  strip7.setBrightness(BRIGHTNESS);
#endif  
}
void neopixelSetBrightness(int strip, unsigned char brightness)
{
  if (brightness > BRIGHTNESS_LIMIT)
    brightness = BRIGHTNESS_LIMIT;
    
  switch (strip)
  {
    case 0:
      strip0.setBrightness(brightness);
      strip0.show();
    break;
#if ENABLE_MULTISTRIP  
    case 1:
      strip1.setBrightness(brightness);
      strip1.show();
    break;
    case 2:
      strip2.setBrightness(brightness);
      strip2.show();
    break;
    case 3:
      strip3.setBrightness(brightness);
      strip3.show();
    break;
    case 4:
      strip4.setBrightness(brightness);
      strip4.show();
    break;
    case 5:
      strip5.setBrightness(brightness);
      strip5.show();
    break;
    case 6:
      strip6.setBrightness(brightness);
      strip6.show();
    break;
    case 7:
      strip7.setBrightness(brightness);
      strip7.show();
    break;
#endif  
  }
}

void neopixelSetPixel(int slot, int offset, uint32_t rgb)
{
    switch (slot)
    {
      case 0: strip0.setPixelColor(offset, rgb); break;
#if ENABLE_MULTISTRIP  
      case 1: strip1.setPixelColor(offset, rgb); break;
      case 2: strip2.setPixelColor(offset, rgb); break;
      case 3: strip3.setPixelColor(offset, rgb); break;
      case 4: strip4.setPixelColor(offset, rgb); break;
      case 5: strip5.setPixelColor(offset, rgb); break;
      case 6: strip6.setPixelColor(offset, rgb); break;
      case 7: strip7.setPixelColor(offset, rgb); break;
#endif      
    }
}

void neopixelSetPalette(int slot, int numleds, uint32_t *palette, int paletteIndex)
{  
  uint32_t offset = paletteIndex;
  unsigned char r,g,b;
  unsigned char h,s,v;
  for(uint16_t i=0; i<numleds; i++)
  {
    if (offset >= numleds)
     offset=0;    

    uint32_t rgb = palette[i];
    r = (rgb >> 16) & 0xFF;
    g = (rgb >> 8) & 0xFF;
    b = (rgb >> 0) & 0xFF;

//shimmer effect, unstable
/*    int scale = 32;
    if (r < 255-scale && r > scale && g < 255-scale
       && g > scale && b < 255-scale && b > scale) 
       {
        int s = random(-scale,scale);
        r += s;
        g += s;
        b += s;
       }
*/
//pulsar effect
/*
    if (i %NUM_LEDS==0) 
    {
      r=g=0;
      b=255;
    }*/

    //rgb=LEDRGB(r,g,b);

    if (offset < 4)
    {
    //  rgb = CRGB_WHITE;
    }
    
    neopixelSetPixel(slot,offset,rgb);
    offset++;    
  }
  
    switch (slot)
    {
      case 0: strip0.show();break;
#if ENABLE_MULTISTRIP  
      case 1: strip1.show();break;
      case 2: strip2.show();break;
      case 3: strip3.show();break;
      case 4: strip4.show();break;
      case 5: strip5.show();break;
      case 6: strip6.show();break;
      case 7: strip7.show();break;
#endif  
    }
}
#endif



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#if ENABLE_BLE
//#include "BLE.h"
#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>
#include "Fx.h"
#include "Cmd.h"
#include "Track.h"
const int BLE_LED_PIN = LED_BUILTIN;
const int RSSI_LED_PIN = 25;//LED_PWR;
BLEService lightsuitService( BLE_UUID_LIGHTSUIT_SERVICE );
BLEUnsignedLongCharacteristic authenticateCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_AUTHENTICATE, BLEWrite);
BLEUnsignedLongCharacteristic statusCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_STATUS, BLEWrite | BLERead | BLENotify );
BLECharCharacteristic commandCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COMMAND, BLERead | BLEWrite  );
BLEUnsignedLongCharacteristic playCharacteristic(BLE_UUID_LIGHTSUIT_CHARACTERISTIC_PLAY, BLERead | BLEWrite  );

//BLEDevice * central = NULL;
void blePeripheralConnectHandler(BLEDevice c) {
  //central = &c;
#if DEBUG_BLE  
  // central connected event handler
  Serial.print(F("Connected event, central: "));
  Serial.println(c.address());
#endif 
}
void blePeripheralDisconnectHandler(BLEDevice c) {
  //central = NULL;
#if DEBUG_BLE  
  // central disconnected event handler
  Serial.print(F("Disconnected event, central: "));
  Serial.println(c.address());
#endif  
}
bool bleSetup()
{
  pinMode( BLE_LED_PIN, OUTPUT );
  pinMode( RSSI_LED_PIN, OUTPUT );
  
  if ( !BLE.begin() )
  {
    return false;
  }

  // set advertised local name and service UUID:
  BLE.setDeviceName( DeviceName );
  BLE.setLocalName( DeviceName );
  BLE.setAdvertisedService( lightsuitService );

  // BLE add characteristics
  lightsuitService.addCharacteristic( authenticateCharacteristic );
  lightsuitService.addCharacteristic( commandCharacteristic );
  lightsuitService.addCharacteristic( playCharacteristic );
 
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  
  // add service
  BLE.addService( lightsuitService );

  // set the initial value for the characeristics:
  commandCharacteristic.writeValue( 0 );
  playCharacteristic.writeValue(0);
  statusCharacteristic.writeValue(0);
  // start advertising
  BLE.advertise();

  digitalWrite( BLE_LED_PIN, HIGH );    
  return true;
}

void blePoll(FxController &fxc)
{
  static unsigned long counter = 0;
  static long previousMillis = 0;

  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

#if DEBUG_BLE  
//  Serial.println(F("Waiting for connection."));
#endif  

  if ( central )
  {
#if DEBUG_BLE  
//    Serial.print( F("Connected to central: " ));
    //Serial.print( central.address() );
#endif
    if ( central.connected() )
    {
      //if( authenticateCharacteristic.value() == 3838) //authenticated
      {
        if (commandCharacteristic.written() )
        {   
          Serial.print( F("BLE cmd: " ));
          int v = commandCharacteristic.value();
          Serial.print( (char)v);
          UserCommandInput(fxc, v);
          Serial.println();
        }
        if (playCharacteristic.written() )
        {
          //Get all our timing setup.
          unsigned long tc = playCharacteristic.value();
          int prevmatch = GetPreviousTimeCodeMatch(tc);    
          setTimecodeLastMatched(SongTrack_timecode(prevmatch));
          setTimecodeSongOffset(tc);  
          setTimecodeTimeOffset(millis());
          
          //Finally start the track
          trackStart(fxc,tc, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), FxTrackEndAction::StopAtEnd);
        }
      }

    } // while connected

#if DEBUG_BLE  
    //Serial.print( F( "Disconnected from central: " ) );
//    Serial.println( central->address() );
#endif    
  } // if central
} // loop
#endif
