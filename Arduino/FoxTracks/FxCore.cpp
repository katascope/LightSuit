/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#include "Config.h"
#include <Arduino.h>
#include "FxCore.h"

static TimeCode timeController;
uint32_t LEDRGB(uint8_t r, uint8_t g, uint8_t b) { return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b; }
unsigned char lerp(float mux, unsigned char a, unsigned char b) { return (unsigned char)(a * (1.0 - mux) + b * mux); }
uint32_t LerpRGB(float t, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2) { return LEDRGB(lerp(t, r1, r2),lerp(t, g1, g2),lerp(t, b1, b2)); }

uint32_t LerpRGB(float t, uint32_t rgb1, uint32_t rgb2) {
  unsigned char r1 = (rgb1 >> 16) & 0xFF;
  unsigned char g1 = (rgb1 >> 8) & 0xFF;
  unsigned char b1 = (rgb1 >> 0) & 0xFF;
  unsigned char r2 = (rgb2 >> 16) & 0xFF;
  unsigned char g2 = (rgb2 >> 8) & 0xFF;
  unsigned char b2 = (rgb2 >> 0) & 0xFF;
  return LEDRGB(lerp(t, r1, r2),lerp(t, g1, g2),lerp(t, b1, b2));
}

uint32_t ShortnameToCRGB(char shortName)
{  
  switch (shortName)
  {
    case 'd': return CRGB_DARK;
    case 'w': return CRGB_WHITE;
    case 'r': return CRGB_RED;
    case 'y': return CRGB_YELLOW;
    case 'g': return CRGB_GREEN;
    case 'c': return CRGB_CYAN;
    case 'b': return CRGB_BLUE;
    case 'm': return CRGB_MAGENTA;
    case 'o': return CRGB_ORANGE;
    case 'h': return CRGB_HALF;
    case 'l': return CRGB_LOWHALF;
  }
  return CRGB_DARK;
}


void PrintFxTrackEndAction(FxTrackEndAction fxTrackEndAction)
{  
  switch (fxTrackEndAction)
  {
    case StopAtEnd: Serial.print(F("StopAtEnd")); break;
    case LoopAtEnd: Serial.print(F("LoopAtEnd")); break;
    default: Serial.print(F("Unk"));
  }
}

void PrintFxPaletteUpdateType(FxPaletteUpdateType paletteUpdateType)
{
  switch (paletteUpdateType)
  {
    case None:    Serial.print(F("None")); break;
    case Once:    Serial.print(F("Once")); break;
    case Done:    Serial.print(F("Done")); break;
    case Always:  Serial.print(F("Alwa")); break;
    default: Serial.print(F("Unk"));
  }
}

void PrintFxStateName(FxState s)
{
  switch (s)
  {
    case FxState_Default:        Serial.print(F("Norm")); break;
    case FxState_TestPattern:    Serial.print(F("Test")); break;
    case FxState_PlayingTrack:   Serial.print(F("Play")); break;
    default: Serial.print(F("Unk"));
  }
}

void PrintFxEventName(int event)
{
  if (event >= fx_stripmask_0 && event <= fx_stripmask_255)
  {
    Serial.print(F("stripMask"));
    Serial.print((unsigned int)event-(unsigned int)fx_stripmask_0);
  }
    
  switch(event)
  {
    case fx_speed_0: Serial.print(F("x0"));return;
    case fx_speed_1: Serial.print(F("x1"));return;
    case fx_speed_2: Serial.print(F("x2"));return;
    case fx_speed_3: Serial.print(F("x3"));return;
    case fx_speed_4: Serial.print(F("x4"));return;
    case fx_speed_5: Serial.print(F("x5"));return;
    case fx_speed_6: Serial.print(F("x6"));return;
    case fx_speed_7: Serial.print(F("x7"));return;
    case fx_speed_8: Serial.print(F("x8"));return;
    case fx_speed_9: Serial.print(F("x9"));return;
    case fx_speed_10: Serial.print(F("x10"));return;
    case fx_speed_11: Serial.print(F("x11"));return;
    case fx_speed_12: Serial.print(F("x12"));return;
    case fx_speed_13: Serial.print(F("x13"));return;
    case fx_speed_14: Serial.print(F("x14"));return;
    case fx_speed_15: Serial.print(F("x15"));return;
    case fx_speed_16: Serial.print(F("x16"));return;
    case fx_speed_17: Serial.print(F("x17"));return;
    case fx_speed_18: Serial.print(F("x18"));return;
    case fx_speed_32: Serial.print(F("x32"));return;

    case fx_speed_pos: Serial.print(F("speed pos"));return;
    case fx_speed_neg: Serial.print(F("speed neg"));return;
    case fx_speed_inc: Serial.print(F("speed inc"));return;
    case fx_speed_dec: Serial.print(F("speed dec"));return;
    case fx_speed_rst: Serial.print(F("speed rst"));return;
    
    case fx_transition_fast: Serial.print(F("t-fast"));return;
    case fx_transition_timed_fade:Serial.print(F("t-timed-fade"));return;
    case fx_transition_timed_wipe_pos:Serial.print(F("t-timed-wipe-pos"));return;
    case fx_transition_timed_wipe_neg:Serial.print(F("t-timed-wipe-neg"));return;
    case fx_transition_timed_wipe_outin:Serial.print(F("t-timed-wipe-outin"));return;
    case fx_transition_timed_wipe_inout:Serial.print(F("t-timed-wipe-inout"));return;
    case fx_transition_timed_wipe_random:Serial.print(F("t-timed-wipe-rnd"));return;
    case fx_transition_timed_fade_sin:Serial.print(F("t-timed-wipe-sine"));return;    
    case fx_transition_timed_fade_cos:Serial.print(F("t-timed-wipe-sine"));return;    
    
    case fx_palette_lead:    Serial.print(F("lead"));return;    
    case fx_palette_follow:  Serial.print(F("follow"));return;       

    case fx_palette_lava: Serial.print(F("lava"));return;
    case fx_palette_cloud: Serial.print(F("cloud"));return;
    case fx_palette_ocean: Serial.print(F("ocean"));return;
    case fx_palette_forest: Serial.print(F("forest"));return;
    case fx_palette_rainbow: Serial.print(F("rainbow"));return;
    case fx_palette_rainbowstripe: Serial.print(F("rainbowstripe"));return;
    case fx_palette_party: Serial.print(F("party"));return;
    case fx_palette_heat: Serial.print(F("heat"));return;

    case fx_palette_dark:    Serial.print(F("dark"));return;
    case fx_palette_white:   Serial.print(F("white"));return;
    case fx_palette_red:     Serial.print(F("red"));return;
    case fx_palette_yellow:  Serial.print(F("yellow"));return;
    case fx_palette_green:   Serial.print(F("green"));return;
    case fx_palette_cyan:    Serial.print(F("cyan"));return;
    case fx_palette_blue:    Serial.print(F("blue"));return;
    case fx_palette_magenta: Serial.print(F("magenta"));return;
    case fx_palette_orange:  Serial.print(F("orange"));return;
    case fx_palette_half:    Serial.print(F("half"));return;
    case fx_palette_lowhalf: Serial.print(F("lowhalf"));return;
    
    case fx_palette_pulse_dark:    Serial.print(F("pulse-dark"));return;
    case fx_palette_pulse_white:   Serial.print(F("pulse-white"));return;
    case fx_palette_pulse_red:     Serial.print(F("pulse-red"));return;
    case fx_palette_pulse_yellow:  Serial.print(F("pulse-yellow"));return;
    case fx_palette_pulse_green:   Serial.print(F("pulse-green"));return;
    case fx_palette_pulse_cyan:    Serial.print(F("pulse-cyan"));return;
    case fx_palette_pulse_blue:    Serial.print(F("pulse-blue"));return;
    case fx_palette_pulse_magenta: Serial.print(F("pulse-magenta"));return;
    case fx_palette_pulse_orange:  Serial.print(F("pulse-orange"));return;
    case fx_palette_pulse_half:  Serial.print(F("pulse-half"));return;
    case fx_palette_pulse_lowhalf:  Serial.print(F("pulse-lowhalf"));return;

    case fx_palette_pulse2_dark:    Serial.print(F("pulse2-dark"));return;
    case fx_palette_pulse2_white:   Serial.print(F("pulse2-white"));return;
    case fx_palette_pulse2_red:     Serial.print(F("pulse2-red"));return;
    case fx_palette_pulse2_yellow:  Serial.print(F("pulse2-yellow"));return;
    case fx_palette_pulse2_green:   Serial.print(F("pulse2-green"));return;
    case fx_palette_pulse2_cyan:    Serial.print(F("pulse2-cyan"));return;
    case fx_palette_pulse2_blue:    Serial.print(F("pulse2-blue"));return;
    case fx_palette_pulse2_magenta: Serial.print(F("pulse2-magenta"));return;
    case fx_palette_pulse2_orange:  Serial.print(F("pulse2-orange"));return;
    case fx_palette_pulse2_half:  Serial.print(F("pulse2-half"));return;
    case fx_palette_pulse2_lowhalf:  Serial.print(F("pulse2-lowhalf"));return;

    case fx_palette_pulse3_dark:    Serial.print(F("pulse3-dark"));return;
    case fx_palette_pulse3_white:   Serial.print(F("pulse3-white"));return;
    case fx_palette_pulse3_red:     Serial.print(F("pulse3-red"));return;
    case fx_palette_pulse3_yellow:  Serial.print(F("pulse3-yellow"));return;
    case fx_palette_pulse3_green:   Serial.print(F("pulse3-green"));return;
    case fx_palette_pulse3_cyan:    Serial.print(F("pulse3-cyan"));return;
    case fx_palette_pulse3_blue:    Serial.print(F("pulse3-blue"));return;
    case fx_palette_pulse3_magenta: Serial.print(F("pulse3-magenta"));return;
    case fx_palette_pulse3_orange:  Serial.print(F("pulse3-orange"));return;
    case fx_palette_pulse3_half:    Serial.print(F("pulse3-half"));return;
    case fx_palette_pulse3_lowhalf: Serial.print(F("pulse3-lowhalf"));return;    

    case fx_palette_pulse4_dark:    Serial.print(F("pulse4-dark"));return;
    case fx_palette_pulse4_white:   Serial.print(F("pulse4-white"));return;
    case fx_palette_pulse4_red:     Serial.print(F("pulse4-red"));return;
    case fx_palette_pulse4_yellow:  Serial.print(F("pulse4-yellow"));return;
    case fx_palette_pulse4_green:   Serial.print(F("pulse4-green"));return;
    case fx_palette_pulse4_cyan:    Serial.print(F("pulse4-cyan"));return;
    case fx_palette_pulse4_blue:    Serial.print(F("pulse4-blue"));return;
    case fx_palette_pulse4_magenta: Serial.print(F("pulse4-magenta"));return;
    case fx_palette_pulse4_orange:  Serial.print(F("pulse4-orange"));return;
    case fx_palette_pulse4_half:    Serial.print(F("pulse4-half"));return;
    case fx_palette_pulse4_lowhalf: Serial.print(F("pulse4-lowhalf"));return;   
    case fx_palette_dw: Serial.print(F("dark-white"));return;
    case fx_palette_dr: Serial.print(F("dark-red"));return;
    case fx_palette_dy: Serial.print(F("dark-yellow"));return;
    case fx_palette_dg: Serial.print(F("dark-green"));return;
    case fx_palette_dc: Serial.print(F("dark-cyan"));return;
    case fx_palette_db: Serial.print(F("dark-blue"));return;
    case fx_palette_dm: Serial.print(F("dark-magenta"));return;
    case fx_palette_wr: Serial.print(F("white-red"));return;
    case fx_palette_wy: Serial.print(F("white-yellow"));return;
    case fx_palette_wg: Serial.print(F("white-green"));return;
    case fx_palette_wc: Serial.print(F("white-cyan"));return;
    case fx_palette_wb: Serial.print(F("white-blue"));return;
    case fx_palette_wm: Serial.print(F("white-magenta"));return;
    case fx_palette_ry: Serial.print(F("red-yellow"));return;
    case fx_palette_rg: Serial.print(F("red-green"));return;
    case fx_palette_rc: Serial.print(F("red-cyan"));return;
    case fx_palette_rb: Serial.print(F("red-blue"));return;
    case fx_palette_rm: Serial.print(F("red-magenta"));return;
    case fx_palette_yg: Serial.print(F("yellow-green"));return;
    case fx_palette_yc: Serial.print(F("yellow-cyan"));return;
    case fx_palette_yb: Serial.print(F("yellow-blue"));return;
    case fx_palette_ym: Serial.print(F("yellow-magenta"));return;
    case fx_palette_gc: Serial.print(F("green-cyan"));return;
    case fx_palette_gb: Serial.print(F("green-blue"));return;
    case fx_palette_gm: Serial.print(F("green-magenta"));return;
    case fx_palette_cb: Serial.print(F("cyan-blue"));return;
    case fx_palette_cm: Serial.print(F("cyan-magenta"));return;
    case fx_palette_bm: Serial.print(F("blue-magenta"));return;

    case fx_palette_wry:Serial.print(F("wry"));return;
    case fx_palette_wrg:Serial.print(F("wrg"));return;
    case fx_palette_wrc:Serial.print(F("wrc"));return;
    case fx_palette_wrb:Serial.print(F("wrb"));return;
    case fx_palette_wrm:Serial.print(F("wrm"));return;
    case fx_palette_wyg:Serial.print(F("wyg"));return;
    case fx_palette_wyc:Serial.print(F("wyc"));return;
    case fx_palette_wyb:Serial.print(F("wyb"));return;
    case fx_palette_wym:Serial.print(F("wym"));return;
    case fx_palette_wgc:Serial.print(F("wgc"));return;
    case fx_palette_wgb:Serial.print(F("wgb"));return;
    case fx_palette_wgm:Serial.print(F("wgm"));return;
    case fx_palette_wcb:Serial.print(F("wcb"));return;
    case fx_palette_wcm:Serial.print(F("wcm"));return;
    case fx_palette_wbm:Serial.print(F("wbm"));return;

    case fx_palette_dry:Serial.print(F("dry"));return;
    case fx_palette_drg:Serial.print(F("drg"));return;
    case fx_palette_drc:Serial.print(F("drc"));return;
    case fx_palette_drb:Serial.print(F("drb"));return;
    case fx_palette_drm:Serial.print(F("drm"));return;
    case fx_palette_dyg:Serial.print(F("dyg"));return;
    case fx_palette_dyc:Serial.print(F("dyc"));return;
    case fx_palette_dyb:Serial.print(F("dyb"));return;
    case fx_palette_dym:Serial.print(F("dym"));return;
    case fx_palette_dgc:Serial.print(F("dgc"));return;
    case fx_palette_dgb:Serial.print(F("dgb"));return;
    case fx_palette_dgm:Serial.print(F("dgm"));return;
    case fx_palette_dcb:Serial.print(F("dcb"));return;
    case fx_palette_dcm:Serial.print(F("dcm"));return;
    case fx_palette_dbm:Serial.print(F("dbm"));return;

    case fx_palette_rbm:Serial.print(F("rbm"));return;
    
    case fx_strip_all:  Serial.print(F("strip-all"));return;
    case fx_strip_none: Serial.print(F("strip-none"));return;
    case fx_strip_odds: Serial.print(F("strip-odds"));return;
    case fx_strip_evens:Serial.print(F("strip-evens"));return;
    case fx_strip0:     Serial.print(F("strip0"));return;
    case fx_strip1:     Serial.print(F("strip1"));return;
    case fx_strip2:     Serial.print(F("strip2"));return;
    case fx_strip3:     Serial.print(F("strip3"));return;
    case fx_strip4:     Serial.print(F("strip4"));return;
    case fx_strip5:     Serial.print(F("strip5"));return;
    case fx_strip6:     Serial.print(F("strip6"));return;
    case fx_strip7:     Serial.print(F("strip7"));return;

    case fx_particles_off: Serial.print(F("particles_off"));return;
    case fx_particles_pos: Serial.print(F("particles_pos"));return;
    case fx_particles_neg: Serial.print(F("particles_neg"));return;
    case fx_particles_rnd: Serial.print(F("particles_rnd"));return;
    case fx_particles_length_1: Serial.print(F("particles_len1"));return;
    case fx_particles_length_2: Serial.print(F("particles_len2"));return;
    case fx_particles_length_3: Serial.print(F("particles_len3"));return;
    case fx_particles_length_4: Serial.print(F("particles_len4"));return;
    case fx_particles_color_dark:   Serial.print(F("particles_color_dark"));return;
    case fx_particles_color_white:  Serial.print(F("particles_color_white"));return;
    case fx_particles_color_red:    Serial.print(F("particles_color_wred"));return;
    case fx_particles_color_yellow: Serial.print(F("particles_color_yellow"));return;
    case fx_particles_color_green : Serial.print(F("particles_color_green"));return;
    case fx_particles_color_cyan:   Serial.print(F("particles_color_cyan"));return;
    case fx_particles_color_blue:   Serial.print(F("particles_color_blue"));return;
    case fx_particles_color_magenta:Serial.print(F("particles_color_magenta"));return;
    case fx_particles_color_orange: Serial.print(F("particles_color_orange"));return;
    case fx_particles_color_half:   Serial.print(F("particles_color_half"));return;
    case fx_particles_color_lowhalf:Serial.print(F("particles_color_lowhalf"));return;
      
    case fx_nothing:Serial.print(F("nothing"));return;
  }
}

void PrintFxTransitionName(FxTransitionType t)
{
  switch (t)
  {
    case Transition_Instant:        Serial.print(F("Fast")); return;
    case Transition_TimedFade:      Serial.print(F("Fade")); return;
    case Transition_TimedWipePos:   Serial.print(F("Wip+")); return;
    case Transition_TimedWipeNeg:   Serial.print(F("Wip-")); return;
    case Transition_TimedWipeOutIn: Serial.print(F("WipOI")); return;
    case Transition_TimedWipeInOut: Serial.print(F("WipIO")); return;
    case Transition_TimedWipeRandom: Serial.print(F("WipRnd")); return;
    case Transition_TimedFadeSin:   Serial.print(F("FadeSin")); return;
    case Transition_TimedFadeCos:   Serial.print(F("FadeCos")); return;
    default: Serial.print(F("Unknown"));
  }
}

void LerpPaletteFromMicroPalette(uint32_t *palette, unsigned int paletteSize, uint32_t* microPalette, unsigned int microPaletteSize)
{
    if (microPaletteSize == 0) //Nothing TO do..
        return;

    float stepSize = (float)paletteSize / (float)microPaletteSize;
    for (unsigned int phase = 0; phase < microPaletteSize; phase++)
    {
        unsigned int offset = (unsigned int)((float)(phase) * (float)stepSize);
        unsigned int offsetNext = (unsigned int)((float)(phase+1) * (float)stepSize) ;

        unsigned long to = 0;
        if (phase == microPaletteSize-1) //last phase, so loop back to 0 
            to = microPalette[0]; 
        else
            to = microPalette[phase + 1];

        unsigned int len = offsetNext - offset;
        for (unsigned int i = 0; i < len; i++)
        {
            float mux = (float)i / (float)(len-1);
            unsigned int palIndex = offset + i;
            unsigned long val = LerpRGB(mux, microPalette[phase], to);
            palette[palIndex] = val;
        }
    }
}

void CopyPalette(int numleds, uint32_t *dst, uint32_t *src)
{
  for (int i=0;i<numleds;i++)
    dst[i] = src[i];
}



unsigned long GetTime() { return (unsigned long)((signed long)millis() - (signed long)getTimecodeTimeOffset() + getTimecodeSongOffset()); }

void setTimecodeLastMatched(unsigned long match)
{
//  Serial.print(F("Set match="));
//  Serial.println(match);
  timeController.lastMatchedTimecode = match;
}

unsigned long getTimecodeLastMatched()
{
  return timeController.lastMatchedTimecode;
}

signed long getTimecodeTimeOffset()
{
  return timeController.timeOffset;
}

signed long getTimecodeSongOffset()
{
  return timeController.songOffset;
}

signed long setTimecodeTimeOffset(signed long tc)
{
  timeController.timeOffset = tc;  
}

signed long setTimecodeSongOffset(signed long tc)
{
  timeController.songOffset = tc;  
}


  
