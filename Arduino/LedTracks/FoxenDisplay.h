/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#ifndef FDISPLAY_DEF
#define FDISPLAY_DEF

class FoxenLcd
{
  public:
    enum FoxenState
    {
      FoxenState_Asleep  = 0,
      FoxenState_Waking  = 1,
      FoxenState_Awake   = 2,
      FoxenState_Focused = 3,
    };
    String name = "Mree";
    String log = "The quick brown fox jumps over the lazy dog. 0123456789 What does the fox say?";
    unsigned int ultraDistance = 1000;
    FoxenState foxenstate = FoxenState_Awake;
    float accelerationX, accelerationY, accelerationZ;
    float gyroX, gyroY, gyroZ;
  private:
    unsigned long int tick = 0;
  private:
    void DrawStateName(FoxenState state);
    void DrawSpinner(int spin);
    void DrawTime();
    void DrawState(int state, int tick);
    void DrawLog();
  public:
    void Startup();
    void Draw();
};

#endif
