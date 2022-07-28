/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#ifndef TRACK_DEF
#define TRACK_DEF
#include "Config.h"
#include <avr/pgmspace.h>
#include "FxCore.h"
#include "TrackMacros.h"

#if LEAD
#define COLOR_ALPHA fx_palette_red
#define COLOR_BETA  fx_palette_blue
#define COLOR_THETA  fx_palette_cyan
#define COLOR_DELTA  fx_palette_magenta
#elif FOLLOW
#define COLOR_ALPHA fx_palette_blue
#define COLOR_BETA  fx_palette_red
#define COLOR_THETA fx_palette_magenta
#define COLOR_DELTA  fx_palette_cyan
#else
#define COLOR_ALPHA fx_palette_blue
#define COLOR_BETA  fx_palette_red
#define COLOR_THETA fx_palette_magenta
#define COLOR_DELTA  fx_palette_cyan
#endif

// Main Track set to 'The Game Has Changed'
#define TRACK_START_DELAY    0  // Delay time from start until track should truly 'start'

//Multistrip
const unsigned long SongTrackTest[] PROGMEM =
{
  _FLASH_TO(1000, fx_palette_dark)
  1000, fx_speed_2,
  1000, fx_speed_pos,
  1000, fx_transition_timed_fade,
  1000, fx_particles_rnd,
  1000, fx_palette_cm,
  /*5000, fx_palette_yellow,
  10000, fx_palette_green,
  15000, fx_palette_cyan,
  20000, fx_palette_blue,
  25500, fx_palette_magenta,*/

  //40000, fx_sidefx_stars_neg_on,
  _FADE_TO(40000, fx_palette_dark)
  _TRACK_END(45000)
};

//Multistrip
const unsigned long SongTrack[] PROGMEM =
{
    _TRACK_BEGIN

    //Lead CrossStep
    _FLASH_WHITE(2500)
    _MULTI_COLOR_FROM_FEET(2500, COLOR_ALPHA)
    _MULTI_COLOR_FROM_BELLY(2900, COLOR_ALPHA)
    _MULTI_COLOR_FROM_SHOULDERS_TO_WRISTS(3300, COLOR_ALPHA)
    _MULTI_FINISH(3650)
    _FADE_TO(3650, fx_palette_dark)

    //Follow CrossStep
    _FLASH_WHITE(4800)
    _MULTI_COLOR_FROM_FEET(4800, COLOR_BETA)
    _MULTI_COLOR_FROM_BELLY(5200, COLOR_BETA)
    _MULTI_COLOR_FROM_SHOULDERS_TO_WRISTS(5600, COLOR_BETA)
    _MULTI_FINISH(5950)
    _FADE_TO(5950, fx_palette_dark)

    //Lead CrossStep
    _FLASH_WHITE(7300)
    _MULTI_COLOR_FROM_FEET(7300, fx_palette_rb)
    _MULTI_COLOR_FROM_BELLY(7700, fx_palette_rb)
    _MULTI_COLOR_FROM_SHOULDERS_TO_WRISTS(8100, fx_palette_rb)
    _MULTI_FINISH(8450)
    _FADE_TO(8450, fx_palette_dark)

    //March together
    _FLASH_WHITE(9700)
    _PLASMA(9700, fx_palette_rb)

    //Arms up & Circles around each other
    _STROBE_COLORS(10800, COLOR_ALPHA, COLOR_BETA)
#if LEAD
    _MULTI_COLOR_FROM_RIGHT_WRIST(14800, fx_palette_magenta)
    _MULTI_COLOR_FROM_RIGHT_SHOULDER_TO_CENTER(15200, fx_palette_magenta)
    _MULTI_COLOR_FROM_CENTER_TO_LEFT_SHOULDER(15600, fx_palette_magenta)
    _MULTI_COLOR_FROM_WAIST_TO_FEET(16000, fx_palette_magenta)
    _MULTI_COLOR_TO_LEFT_WRIST(16400, fx_palette_magenta)
#elif FOLLOW
    _MULTI_COLOR_FROM_RIGHT_WRIST(14800, fx_palette_magenta)
    _MULTI_COLOR_FROM_RIGHT_SHOULDER_TO_CENTER(15200, fx_palette_magenta)
    _MULTI_COLOR_FROM_CENTER_TO_LEFT_SHOULDER(15600, fx_palette_magenta)
    _MULTI_COLOR_FROM_WAIST_TO_FEET(16000, fx_palette_magenta)
    _MULTI_COLOR_TO_LEFT_WRIST(16400, fx_palette_magenta)
    /*  _MULTI_COLOR_FROM_LEFT_WRIST(14800, fx_palette_magenta`)
      _MULTI_COLOR_FROM_LEFT_SHOULDER_TO_CENTER(15200, fx_palette_magenta)
      _MULTI_COLOR_FROM_CENTER_TO_RIGHT_SHOULDER(15600, fx_palette_magenta)
      _MULTI_COLOR_FROM_WAIST(16000, fx_palette_magenta)
      _MULTI_COLOR_TO_RIGHT_WRIST(16400, fx_palette_magenta)*/
#endif

    //Build2
    _FLASH_WHITE(16800)
    _PLASMA_FAST(16800, fx_palette_cm)

    //BEATS
    _FLASH_WHITE(19600)
    _FIRE_EFFECT(19600, fx_palette_red, fx_palette_blue, fx_palette_rb, fx_palette_pulse2_blue, fx_palette_pulse2_red)

    //calm/smooth in down
    _FLASH_WHITE(24500)

    _MULTI_COLOR_FROM_FEET(24500, COLOR_ALPHA)
    _MULTI_COLOR_FROM_BELLY(25250, COLOR_ALPHA)
    _MULTI_COLOR_FROM_SHOULDERS_TO_WRISTS(25800, COLOR_ALPHA)

    _FLASH_WHITE(26500)
    //Reachout?
    _MULTI_COLOR_FROM_WRISTS(26900, fx_palette_magenta)
    _MULTI_COLOR_FROM_SHOULDERS_TO_CENTER(27400, fx_palette_magenta)
    _MULTI_COLOR_FROM_WAIST_TO_FEET(27900, fx_palette_magenta)

    //Take them to crazytown.
    _MULTI_FINISH(29000)
    _BURST_OUT_TO(29000, fx_palette_half)    
    29000, fx_particles_neg,
    //we came together, so purple again?
    29000, fx_particles_color_magenta,
    29000, fx_transition_timed_wipe_inout,
    29000, fx_palette_blue,
    29400, fx_palette_red,
    29790, fx_palette_magenta,
    30180, fx_palette_blue,
    30570, fx_palette_rm,
    30960, fx_palette_bm,
    31350, fx_palette_rb,
    31740, fx_palette_red,
    
    32130, fx_palette_magenta,
    32520, fx_palette_blue,
    32910, fx_palette_rm,
    33300, fx_palette_rb,
    33690, fx_particles_off,
    33690, fx_palette_red,
    
    34080, fx_speed_2,
    34080, fx_speed_neg,
    _MULTI_COLOR_FROM_FEET(34080, COLOR_BETA)
    _MULTI_COLOR_FROM_BELLY(34470, fx_palette_rb)
    _MULTI_COLOR_FROM_SHOULDERS_TO_WRISTS(34860, COLOR_ALPHA)
    _MULTI_COLOR_FROM_FEET(35250, fx_palette_rb)
    _MULTI_COLOR_FROM_BELLY(35640, COLOR_ALPHA)
    _MULTI_COLOR_FROM_SHOULDERS_TO_WRISTS(36030, COLOR_BETA)

    _MULTI_FINISH(36420)
    36420, fx_transition_timed_wipe_inout,
    36420, COLOR_ALPHA,
    36810, COLOR_BETA,
    37200, fx_palette_rb,
    37200, fx_particles_off,
    //_MULTI_COLOR_FROM_FEET(36420, COLOR_ALPHA)
    //_MULTI_COLOR_FROM_BELLY(36810, COLOR_BETA)
    //_MULTI_COLOR_FROM_SHOULDERS_TO_WRISTS(37200, fx_palette_rb)
    _MULTI_FINISH(37590)
    37590, fx_transition_timed_fade,
    37590, fx_palette_red,

    //Paso Spins
    _FADE_TO(38700, fx_palette_dr)
    _FADE_TO(39200, fx_palette_dr)

    _FADE_TO(41300, fx_palette_dark)
    //_WIPE_UP(43300, fx_palette_blue)
    43300, fx_speed_rst,
    43300, fx_transition_timed_wipe_inout,
#if LEAD
    43300, fx_strip + (LEDS_2),
    43300, fx_palette_red,
    43775, fx_strip + (LEDS_1),
    43775, fx_palette_red,
    44250, fx_strip + (LEDS_0),
    44250, fx_palette_red,
    44725, fx_strip + (LEDS_3),
    44725, fx_palette_red,
    45200, fx_strip + (LEDS_4),
    45200, fx_palette_red,
    45675, fx_strip + (LEDS_6),
    45675, fx_palette_red,
    46150, fx_strip + (LEDS_5),
    46150, fx_palette_red,
    46625, fx_strip + (LEDS_7),
    46625, fx_palette_red,
#elif FOLLOW
    43300, fx_strip + (LEDS_7),
    43300, fx_palette_red,
    43775, fx_strip + (LEDS_5),
    43775, fx_palette_red,
    44250, fx_strip + (LEDS_6),
    44250, fx_palette_red,
    44725, fx_strip + (LEDS_4),
    44725, fx_palette_red,
    45200, fx_strip + (LEDS_3),
    45200, fx_palette_red,
    45675, fx_strip + (LEDS_0),
    45675, fx_palette_red,
    46150, fx_strip + (LEDS_1),
    46150, fx_palette_red,
    46625, fx_strip + (LEDS_2),
    46625, fx_palette_red,
#endif    
    47100, fx_strip_all,
    47100, fx_particles_off,
    47100, fx_speed_2,
    47100, fx_speed_neg,
    
    47100, fx_particles_pos,
    47100, fx_particles_color_red,
    
    _FADE_TO(47100, fx_palette_pulse2_red)
    _FADE_TO(48100, fx_palette_pulse2_red)
    //primetime
    50400, fx_particles_off,
    _FLASH_WHITE(50400)

    //blue fire
    _FIRE_EFFECT(50600, fx_palette_pulse2_blue, fx_palette_pulse2_cyan, fx_palette_pulse2_white, fx_palette_blue, fx_palette_cyan)
    _FIRE_EFFECT(55000, fx_palette_pulse2_blue, fx_palette_pulse2_magenta, fx_palette_db, fx_palette_dm, fx_palette_dbm)

    //creates the 'eva effect'
    //57200, fx_speed_rst,
    57200, fx_speed_3,
    57200, fx_speed_neg,
    57200, fx_transition_fast,
    //57200, fx_palette_dbm,
    _FADE_TO(57200, fx_palette_blue)
    _FADE_TO(59600, fx_palette_pulse2_dark)

    _PLASMA_OPPOSING(60000, fx_palette_dc, fx_palette_dm)
    _PLASMA_OPPOSING(66000, fx_palette_pulse2_cyan, fx_palette_pulse2_magenta)

    //CHAPTER 2
    72000, fx_speed_0,
    72000, fx_speed_pos,
    _FADE_TO(72000, fx_palette_magenta)

    //Side-Kicks
    _SIDE_KICK_EVENS(73000, COLOR_THETA)
    _SIDE_KICK_ODDS(73500, COLOR_THETA)
    _SIDE_KICK_EVENS(74000, COLOR_DELTA)
    _SIDE_KICK_ODDS(74500, COLOR_DELTA)
    _SIDE_KICK_EVENS(75000, COLOR_THETA)
    _SIDE_KICK_ODDS(75500, COLOR_THETA)
    _SIDE_KICK_EVENS(76000, COLOR_DELTA)
    _SIDE_KICK_ODDS(76500, COLOR_DELTA)
    _SIDE_KICK_EVENS(77000, COLOR_THETA)
    _SIDE_KICK_ODDS(77500, COLOR_THETA)
    _SIDE_KICK_EVENS(78000, COLOR_DELTA)
    _SIDE_KICK_ODDS(78500, COLOR_DELTA)
    _SIDE_KICK_EVENS(79000, COLOR_THETA)
    _SIDE_KICK_ODDS(79500, COLOR_THETA)
    _SIDE_KICK_EVENS(80000, COLOR_DELTA)
    _SIDE_KICK_ODDS(80500, COLOR_DELTA)

    81000, fx_strip_all,
    81000, fx_particles_off,

    ///bwaaah, into the sss...qqs's
    81500, fx_speed_2,
    81500, fx_speed_neg,
    _FADE_TO(81500, fx_palette_pulse2_red)
    _FADE_TO(82800, fx_palette_pulse2_red)
    //end of bwaah

    _FADE_TO(88000, fx_palette_rb)
    _FLASH_TO(94000, fx_palette_blue)
    _FLASH_TO(95000, fx_palette_red)

#if LEAD
    _FLASH_TO(96000, fx_palette_pulse2_magenta)
    96000, fx_speed_2,
    96000, fx_speed_neg,
    96000, fx_transition_timed_wipe_random,
    96000, fx_palette_dark,
    100000, fx_palette_dark,
    //pickup from spinning
    _MULTI_COLOR_FROM_WRISTS(101000, fx_palette_magenta)
    _MULTI_COLOR_FROM_NECK(102000, fx_palette_magenta)
    _MULTI_COLOR_FROM_WAIST_TO_FEET(103000, fx_palette_magenta)
#elif FOLLOW
    _FLASH_TO(96000, fx_palette_pulse2_magenta)
    96000, fx_speed_2,
    96000, fx_speed_neg,
    _FADE_TO(97000, fx_palette_magenta)
    101000, fx_palette_magenta,
#endif
    104000, fx_strip_all,
    104000, fx_speed_2,
    104000, fx_speed_neg,
    _FADE_TO(104000, fx_palette_pulse2_magenta)

    //CHAPTER 3
    //big march around
    108000, fx_speed_0,
    108000, fx_particles_rnd,
    _FLASH_TO(108000, COLOR_ALPHA)
    //_BURST_OUT_TO(109000, fx_palette_half)
    //_BURST_OUT_TO(109500, COLOR_BETA)
    _BURST_OUT_TO(110000, fx_palette_half)
    _BURST_OUT_TO(110500, COLOR_ALPHA)
    _BURST_OUT_TO(111000, fx_palette_half)
    _BURST_OUT_TO(111500, COLOR_BETA)
    _BURST_OUT_TO(112000, fx_palette_half)
    _BURST_OUT_TO(112500, COLOR_ALPHA)
    _BURST_OUT_TO(113000, fx_palette_half)
    _BURST_OUT_TO(113500, COLOR_BETA)
    _BURST_OUT_TO(114000, fx_palette_half)
    _BURST_OUT_TO(114500, COLOR_ALPHA)
    _BURST_OUT_TO(115000, fx_palette_half)
    _BURST_OUT_TO(115500, COLOR_BETA)
    _BURST_OUT_TO(116000, fx_palette_half)
    _BURST_OUT_TO(116500, COLOR_ALPHA)
    _BURST_OUT_TO(117000, fx_palette_half)

    //_FADE_TO(111000, fx_palette_red)
    _FADE_TO(118000, fx_palette_blue)
    _FADE_TO(119000, fx_palette_red)
    _FADE_TO(119500, fx_palette_blue)
    _FADE_TO(120000, fx_palette_red)
    _FADE_TO(120500, fx_palette_magenta)

    121000, fx_speed_neg,
    121000, fx_speed_4,
    _FADE_TO(121000, fx_palette_pulse2_white)
    _FADE_TO(121500, fx_palette_pulse2_white)

    122100, fx_speed_8,
    122100, fx_transition_fast,
    122100, fx_palette_pulse_red,
    122200, fx_palette_pulse_yellow,
    122300, fx_palette_pulse_green,
    122400, fx_palette_pulse_cyan,
    122500, fx_palette_pulse_blue,
    122600, fx_palette_pulse_magenta,
    122700, fx_palette_pulse_white,
    122800, fx_palette_pulse2_red,
    122900, fx_palette_pulse2_yellow,
    123000, fx_palette_pulse2_green,
    123100, fx_palette_pulse2_cyan,
    123200, fx_palette_pulse2_blue,
    123300, fx_palette_pulse2_magenta,
    123400, fx_palette_pulse2_white,
    123500, fx_particles_pos,
    123500, fx_particles_color_white,
    123500, fx_speed_16,
    123500, fx_transition_fast,
    123500, fx_palette_pulse3_red,
    123600, fx_palette_pulse3_yellow,
    123700, fx_palette_pulse3_green,
    123800, fx_palette_pulse3_cyan,
    124900, fx_palette_pulse3_blue,
    124000, fx_palette_pulse3_magenta,
    124100, fx_palette_pulse3_white,
    124200, fx_palette_pulse4_red,
    124300, fx_palette_pulse4_yellow,
    124400, fx_palette_pulse4_green,
    124500, fx_palette_pulse4_cyan,
    124600, fx_palette_pulse4_blue,
    124700, fx_palette_pulse4_magenta,
    124800, fx_palette_pulse4_white,
    124800, fx_particles_off,

    _FADE_TO(125000, fx_palette_magenta)
    _FADE_TO(126500, fx_palette_dark)

    //the end
    _TRACK_END(127000)
};

const PROGMEM int numSongTracks = sizeof(SongTrack) / (sizeof(unsigned long) * 2);

unsigned long SongTrack_timecode(int i);
unsigned long SongTrack_event(int i);

unsigned long GetFinalTimeCodeEntry();
int GetNextTimeCodeMatch(int currentMatch);
int GetCurrentTimeCodeMatch(unsigned long timecode);
int GetPreviousTimeCodeMatch(unsigned long timecode);

void trackStart(FxController &fxc, unsigned long tc, unsigned long tcOffset, FxTrackEndAction tae);
void trackStop(FxController &fxc);
bool trackHasLinearTime();
void FxTrackSay(unsigned long timecode, unsigned long matchedTimecode, unsigned long nextMatchedTimecode);

#endif
