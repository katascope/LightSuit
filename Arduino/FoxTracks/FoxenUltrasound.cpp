/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
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
