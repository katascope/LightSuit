#include <SPI.h>
#include <Wire.h>
#include "FoxenUltrasound.h"

void FoxenUltrasound::Startup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);    
}

long FoxenUltrasound::GetDistance()
{
  return distance;
}

static unsigned long previousMicros = 0;
void FoxenUltrasound::Update()
{
  long duration;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(offTime);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(onTime);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);

#if 0 // non-blocking version, if can get to work
 unsigned long currentMicros = micros();     
  if((triggerState == LOW) && (currentMicros - previousMicros >= offTime))     
   {      
     triggerState = HIGH; // turn it on      
     previousMicros = currentMicros; // remember the time     
     digitalWrite(trigPin, triggerState); // update the actual trigger     
   }    
   else if((triggerState == HIGH) && (currentMicros - previousMicros >= onTime))    
   {           
     triggerState = LOW; // turn it off          
     previousMicros = currentMicros; // remember the time           
     digitalWrite(trigPin, triggerState); // update the actual trigger      
   }    
#endif

  duration = pulseIn(echoPin, HIGH);  
  distance = duration * 0.034 / 2;
  //Serial.print("Distance: ");
  //Serial.println(distance);
 
}
