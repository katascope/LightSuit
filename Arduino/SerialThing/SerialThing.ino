/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#define SERIAL_BAUD_RATE 115200

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print(F("Serial init: "));
  Serial.println(SERIAL_BAUD_RATE);
  Serial.println("Setup complete.");
}
int tick =0;
void loop()
{
  while (Serial.available())  
  {
    int serial = Serial.read();
    Serial.print(F("Rcv="));
    Serial.println(serial);
  }

  Serial.print(F("Tick="));
  Serial.println(tick);
  tick++;
  delay(250);
}
