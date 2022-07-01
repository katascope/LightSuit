/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#define _TRACK_BEGIN \
  1, fx_strip_all, \
  1, fx_palette_dark, \
  1, fx_speed_rst, \
  1, fx_speed_0, \
  1, fx_speed_pos, \

#define _TRACK_END(I) \
  I, fx_strip_all, \
  I, fx_transition_timed_fade, \
  I, fx_palette_dark, \
  I, fx_particles_off, \
  I + 1000, fx_transition_fast,\
  I + 1000, fx_palette_dark, 

#define _RANDOM_TO(I, FXRGB) \
  I, fx_transition_timed_wipe_random, \
  I, FXRGB,

#define _FADE_TO(I, FXRGB) \
  I, fx_transition_timed_fade, \
  I, FXRGB,

#define _MULTI_FINISH(I) \
  I, fx_strip_all,

#define _BURST_OUT_TO(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_transition_timed_wipe_inout, \
  I, FXRGB,

#define _BURST_IN_TO(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_transition_timed_wipe_out, \
  I, FXRGB,

#define _BURST_WHITE(I) \
  I, fx_strip_all, \
  I, fx_transition_timed_wipe_inout, \
  I, fx_palette_half, \
  I, fx_speed_rst,

#define _FLASH_WHITE(I) \
  I, fx_strip_all, \
  I, fx_transition_fast, \
  I, fx_palette_half, \
  I, fx_speed_rst,

#define _FLASH_TO(I, FXRGB) \
  I, fx_strip_all, \
  I, fx_transition_fast, \
  I, FXRGB, \
  I, fx_speed_rst,

#define _WIPE_UP(I,FXRGB) \
  I, fx_speed_rst, \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB,

#define _WIPE_DN(I,FXRGB) \
  I, fx_speed_rst, \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB,

#define _PLASMA(I, FXRGB) \
  I, fx_speed_2, \
  I, fx_speed_neg, \
  I, fx_transition_timed_fade, \
  I, FXRGB,

#define _PLASMA_FAST(I, FXRGB) \
  I, fx_speed_3, \
  I, fx_speed_neg, \
  I, fx_transition_timed_fade, \
  I, FXRGB,

#define _PLASMA_OPPOSING(I, FXRGB1, FXRGB2) \
  I, fx_strip_evens, \
  I, fx_speed_2, \
  I, fx_speed_pos, \
  I, fx_transition_timed_fade, \
  I, FXRGB1, \
  I, fx_strip_odds, \
  I, fx_speed_2, \
  I, fx_speed_neg, \
  I, fx_transition_timed_fade, \
  I, FXRGB2, \
  I, fx_strip_all,

#define _STROBE_COLORS(I, FXRGB1, FXRGB2) \
  I, fx_transition_timed_fade, \
  I, fx_palette_blue, \
  I+400, fx_palette_red, \
  I+800, fx_palette_blue, \
  I+1200, fx_palette_red, \
  I+1600, fx_palette_blue, \
  I+2000, fx_palette_red, \
  I+2400, fx_palette_blue, \
  I+2800, fx_palette_red, \
  I+3200, fx_palette_blue, \
  I+3600, fx_palette_red, \
  I+3600, fx_speed_0, \

#define _FIRE_EFFECT(I, FXRGB1, FXRGB2, FXRGB3, FXRGB4, FXRGB5) \
  I, fx_speed_rst, \
  I, fx_speed_3, \
  I, fx_speed_neg, \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB1, \
  I+600, FXRGB2, \
  I+1200, FXRGB3, \
  I+1800, FXRGB4, \
  I+2400, FXRGB5, \
  I+3000, FXRGB3, \
  I+3600, FXRGB4, \
  I+4200, FXRGB5,

  

  //break up into legs in chest in arms in segments

#define _MULTI_COLOR_FROM_FEET(I, FXRGB) \
  I, fx_strip + (LEFT_LEG|RIGHT_LEG), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB,

#define _MULTI_COLOR_FROM_NECK(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_CHEST_A|LEFT_CHEST_B|RIGHT_CHEST_A|RIGHT_CHEST_B), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_SHOULDERS_TO_CENTER(I, FXRGB) \
  I, fx_strip + (LEFT_CHEST_A|LEFT_CHEST_B|RIGHT_CHEST_A|RIGHT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_BELLY(I, FXRGB) \
  I, fx_strip + (LEFT_CHEST_A|LEFT_CHEST_B|RIGHT_CHEST_A|RIGHT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_SHOULDERS_TO_WRISTS(I, FXRGB) \
  I, fx_strip + (LEFT_ARM|RIGHT_ARM), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_WAIST_TO_FEET(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_LEG|RIGHT_LEG), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB,

#define _MULTI_BURST_FROM_CENTER(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_CHEST_A|RIGHT_CHEST_A|LEFT_CHEST_B|RIGHT_CHEST_B), \
  I, fx_transition_timed_wipe_inout, \
  I, FXRGB,

#define _MULTI_COLOR_FROM_WRISTS(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_ARM|LEFT_ARM), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_RIGHT_WRIST(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_ARM), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_LEFT_WRIST(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_ARM), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define _MULTI_COLOR_TO_RIGHT_WRIST(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_ARM), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, \

#define _MULTI_COLOR_TO_LEFT_WRIST(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_ARM), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_RIGHT_SHOULDER_TO_CENTER(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_CHEST_A|RIGHT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_LEFT_SHOULDER_TO_CENTER(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_CHEST_A|LEFT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_CENTER_TO_LEFT_SHOULDER(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_CHEST_A|LEFT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define _MULTI_COLOR_FROM_CENTER_TO_RIGHT_SHOULDER(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_CHEST_A|RIGHT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define _SIDE_KICK_EVENS(I, FXRGB) \
  I, fx_strip + (LEDS_0|LEDS_2|LEDS_4|LEDS_6), \
  I, fx_speed_rst, \
  I, fx_transition_timed_wipe_outin, \
  I, FXRGB, \

#define _SIDE_KICK_ODDS(I, FXRGB) \
  I, fx_strip + (LEDS_1|LEDS_3|LEDS_5|LEDS_7), \
  I, fx_speed_rst, \
  I, fx_transition_timed_wipe_inout, \
  I, FXRGB, \

#define _TWO_STEP_MULTI_BURST_FULLBODY(I1, I2, FXRGB) \
  _MULTI_BURST_FROM_CENTER(I1, FXRGB) \
  _MULTI_COLOR_FROM_WAIST_TO_FEET(I2, FXRGB) \
  _MULTI_COLOR_FROM_SHOULDERS_TO_WRISTS(I2, FXRGB)
