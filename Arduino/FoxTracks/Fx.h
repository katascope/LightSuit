/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#ifndef FX_DEF
#define FX_DEF
#include <Arduino.h>
#include "Config.h"
#include "FxCore.h"

#define NUM_PARTICLES 4

enum FxParticleMode
{
  FX_PARTICLEMODE_STAR,
  FX_PARTICLEMODE_RND,
};

class FxParticle
{
public:  
  float on = false;
  FxParticleMode mode = FX_PARTICLEMODE_STAR;
  float loc = 0;
  float vel = 0;
  unsigned int len = 2;
  uint32_t rgb = 0xFFFFFFFF;
  FxParticle()
  {
      loc = 0;
      vel = 0.5f + (float)(rand()%40) / 40.0f;
  }
};

class FxStripController
{
public:  
  int numleds = 0;
  unsigned char brightness = BRIGHTNESS;
  FxTransitionType transitionType = Transition_Instant;  
  FxPaletteUpdateType fxPaletteUpdateType = FxPaletteUpdateType::None;
  uint32_t *palette;
  uint32_t *nextPalette;
  uint32_t *initialPalette;
  unsigned int *sequence;
  int paletteSpeed = 0;
  int paletteDirection = 1;
  int paletteIndex = 0;

  FxParticle particles[NUM_PARTICLES];
public:
  FxStripController(int nl)
  { 
    numleds = nl;
    palette = (uint32_t *)malloc(sizeof(uint32_t) * numleds);
    nextPalette = (uint32_t *)malloc(sizeof(uint32_t) * numleds);
    initialPalette = (uint32_t *)malloc(sizeof(uint32_t) * numleds);
    sequence = (unsigned int *)malloc(sizeof(sequence) * numleds);
    for (int i=0;i<numleds;i++)
    {
      palette[i] = LEDRGB(0,0,0);
      nextPalette[i] = LEDRGB(0,0,0);
      initialPalette[i] = LEDRGB(0,0,0);
      sequence[i] = i;
    }
  } 
  bool HasRunning()
  {
    for (int i=0;i<NUM_PARTICLES;i++)
      if (particles[i].on) 
        return true;
    return false;
  }
  void SetParticlesRunning(bool state)
  {
    for (int i=0;i<NUM_PARTICLES;i++)
      particles[i].on = state;
  }
  void SetParticlesLength(int len)
  {
    for (int i=0;i<NUM_PARTICLES;i++)
      particles[i].len = len;
  }
  void SetParticlesColor(uint32_t rgb)
  {
    for (int i=0;i<NUM_PARTICLES;i++)
      particles[i].rgb = rgb;
  }
  void SetParticlesDirection(int dir)//-1 or 1
  {
    RandomizeParticles();
    for (int i=0;i<NUM_PARTICLES;i++)
      particles[i].loc = dir * particles[i].loc;
  }
  void SetParticleMode(FxParticleMode mode)
  {
    for (int i=0;i<NUM_PARTICLES;i++)
    {
      particles[i].mode = mode;
    }
    RandomizeParticles();
  }
  void RandomizeParticles()
  {
    for (int i=0;i<NUM_PARTICLES;i++)
    {
      particles[i].loc = rand() % (numleds-1);
      if (particles[i].mode == FX_PARTICLEMODE_RND)
         particles[i].loc = rand() % 10;
    }
  }
};

struct FxController
{
public:  
  float transitionMux = 0;
  FxState fxState = FxState_Default;
  FxTrackEndAction fxTrackEndAction;
  unsigned long lastTimeLedUpdate = 0;  
  unsigned char stripMask = 255;
  FxStripController *strip[NUM_STRIPS];
  int select = 0;
  public:
  bool IsAnimating()
  {
    for (int i=0;i<NUM_STRIPS;i++)
        if (strip[i]->paletteSpeed > 0)
          return true;
    if (HasRunning())
      return true;
    
    return false;
  }
  FxController()
  {
    for (int i=0;i<NUM_STRIPS;i++)
    {
      strip[i] = NULL;
      switch (i)
      {
        case 0: strip[i] = new FxStripController(NUM_LEDS_0); break;
        case 1: strip[i] = new FxStripController(NUM_LEDS_1); break;
        case 2: strip[i] = new FxStripController(NUM_LEDS_2); break;
        case 3: strip[i] = new FxStripController(NUM_LEDS_3); break;
        case 4: strip[i] = new FxStripController(NUM_LEDS_4); break;
        case 5: strip[i] = new FxStripController(NUM_LEDS_5); break;
        case 6: strip[i] = new FxStripController(NUM_LEDS_6); break;
        case 7: strip[i] = new FxStripController(NUM_LEDS_7); break;
      }
    }
  }
  bool HasRunning()
  {
    for (int s=0;s<NUM_STRIPS;s++)
      if (stripMask & (1<<s))   
        if (strip[s]->HasRunning())
          return true;
    return false;
  }
  void SetParticlesRunning(bool isRunning)
  {
    for (int s=0;s<NUM_STRIPS;s++)
      if (stripMask & (1<<s))   
        strip[s]->SetParticlesRunning(isRunning);
  }  
  void SetParticlesColor(uint32_t rgb)
  {
    for (int s=0;s<NUM_STRIPS;s++)
      if (stripMask & (1<<s))   
        strip[s]->SetParticlesColor(rgb);
  }  
  void SetParticlesDirection(int dir)
  {
    for (int s=0;s<NUM_STRIPS;s++)
      if (stripMask & (1<<s))   
        strip[s]->SetParticlesDirection(dir);
  }  
  void SetParticlesLength(int len)
  {
    for (int s=0;s<NUM_STRIPS;s++)
      if (stripMask & (1<<s))   
        strip[s]->SetParticlesLength(len);
  }
  void SetParticleMode(FxParticleMode mode)
  {
    for (int s=0;s<NUM_STRIPS;s++)
      if (stripMask & (1<<s))   
        strip[s]->SetParticleMode(mode);
  }
  
};

void FxProcessSideFX(FxController &fxc);
void FxEventProcess(FxController &fxc,int event);
void FxDisplayStatus(FxController &fxc);
void CreateSinglePulseBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b) ;

#endif
