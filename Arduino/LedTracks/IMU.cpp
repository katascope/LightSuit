#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>
#include "IMU.h"

/*#define LED_PIN     3 // 3, 5 for some, should be 3 
#define NUM_LEDS    310
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];*/
//////////////// FastLED Section ////////////////


void FIMU::Startup()
{
  if ( !IMU.begin() )
  {
    Serial.println( "Failed to initialize IMU!" );
    while ( 1 );
  }
  Serial.print( "Accelerometer sample rate = " );
  Serial.print( IMU.accelerationSampleRate() );
  Serial.println( " Hz" );
}

void FIMU::Poll()
{
          if ( IMU.accelerationAvailable() )
          {
            IMU.readAcceleration( accelerationX, accelerationY, accelerationZ );
          /*  Serial.print("Acc=");
            Serial.print(accelerationX);
            Serial.print('\t');
            Serial.print(accelerationY);
            Serial.print('\t');
            Serial.print(accelerationZ);*/
          }

          if ( IMU.gyroscopeAvailable() )
          {
            IMU.readGyroscope( gyroX, gyroY, gyroZ );
            /*Serial.print("Gyro=");
            Serial.print(gyroX);
            Serial.print('\t');
            Serial.print(gyroY);
            Serial.print('\t');
            Serial.print(gyroZ);*/
          }
}
