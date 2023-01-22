/*Copyright 6/14/2022 github/katascope
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#ifndef FX_TYPES_DEF
#define FX_TYPES_DEF
#include <Arduino.h>

#if ENABLE_SAFETY
#define DARK    0x00,0x00,0x00
#define WHITE   0x5F,0x5F,0x5F
#define RED     0xFF,0x00,0x00
#define YELLOW  0x9F,0x9F,0x00
#define GREEN   0x00,0xFF,0x00
#define CYAN    0x00,0x9F,0x9F
#define BLUE    0x00,0x00,0xFF
#define MAGENTA 0x9F,0x00,0x9F
#define ORANGE  0xFF,0x7F,0x00
#define HALF    0x3F,0x3F,0x3F
#define LOWHALF 0x1F,0x1F,0x1F
#else
#define DARK    0x00,0x00,0x00
#define WHITE   0x7F,0x7F,0x7F
#define RED     0xFF,0x00,0x00
#define YELLOW  0xFF,0xFF,0x00
#define GREEN   0x00,0xFF,0x00
#define CYAN    0x00,0xFF,0xFF
#define BLUE    0x00,0x00,0xFF
#define MAGENTA 0x7F,0x00,0xFF
#define ORANGE  0xFF,0x7F,0x00
#define HALF    0x7F,0x7F,0x7F
#define LOWHALF 0x4F,0x4F,0x4F
#endif

#define CRGB_DARK    LEDRGB(DARK)
#define CRGB_WHITE   LEDRGB(WHITE)
#define CRGB_RED     LEDRGB(RED)
#define CRGB_YELLOW  LEDRGB(YELLOW)
#define CRGB_GREEN   LEDRGB(GREEN)
#define CRGB_CYAN    LEDRGB(CYAN)
#define CRGB_BLUE    LEDRGB(BLUE)
#define CRGB_MAGENTA LEDRGB(MAGENTA)
#define CRGB_ORANGE  LEDRGB(ORANGE)
#define CRGB_HALF    LEDRGB(HALF)
#define CRGB_LOWHALF LEDRGB(LOWHALF)

enum FxPaletteUpdateType
{
  None,
  Once,
  Done,
  Always
};

enum FxState
{
  FxState_Default        = 0,
  FxState_TestPattern    = 1,
  FxState_PlayingTrack   = 2
};

enum FxStripMask
{
  LEDS_0 = 1,   RIGHT_CHEST_A = LEDS_0,
  LEDS_1 = 2,   LEFT_CHEST_A = LEDS_1,
  LEDS_2 = 4,   RIGHT_CHEST_B = LEDS_2,
  LEDS_3 = 8,   LEFT_CHEST_B = LEDS_3,
  LEDS_4 = 16,  RIGHT_ARM = LEDS_4,
  LEDS_5 = 32,  LEFT_ARM = LEDS_5,
  LEDS_6 = 64,  RIGHT_LEG = LEDS_6,
  LEDS_7 = 128, LEFT_LEG = LEDS_7
};

//List of possible Fx events
enum FxEvent
{
  fx_speed_0  = 0,
  fx_speed_1  = 1,
  fx_speed_2  = 2,
  fx_speed_3  = 3,
  fx_speed_4  = 4,
  fx_speed_5  = 5,
  fx_speed_6  = 6,
  fx_speed_7  = 7,
  fx_speed_8  = 8,
  fx_speed_9  = 9,
  fx_speed_10 = 10,
  fx_speed_11 = 11,
  fx_speed_12 = 12,
  fx_speed_13 = 13,
  fx_speed_14 = 14,
  fx_speed_15 = 15,
  fx_speed_16 = 16,
  fx_speed_17 = 17,
  fx_speed_18 = 18,
  fx_speed_32 = 19,

  fx_speed_pos = 20,
  fx_speed_neg = 21,
  fx_speed_inc = 22,
  fx_speed_dec = 23,
  fx_speed_rst = 24,

  fx_servo_min,
  fx_servo_zero,
  fx_servo_max,
  fx_servo_front_left_hip,
  fx_servo_front_left_elbow,
  fx_servo_front_left_foot,
  fx_servo_front_right_hip,
  fx_servo_front_right_elbow,
  fx_servo_front_right_foot,
  fx_servo_back_left_hip,
  fx_servo_back_left_elbow,
  fx_servo_back_left_foot,
  fx_servo_back_right_hip,
  fx_servo_back_right_elbow,
  fx_servo_back_right_foot,
  
  fx_transition_fast,
  fx_transition_timed_fade,
  fx_transition_timed_wipe_pos,
  fx_transition_timed_wipe_neg,
  fx_transition_timed_wipe_outin,
  fx_transition_timed_wipe_inout,
  fx_transition_timed_wipe_random,

  fx_transition_timed_fade_sin,
  fx_transition_timed_fade_cos,

  fx_palette_lead,
  fx_palette_follow,

  fx_track_begin,
  fx_track_stop,

  fx_palette_lava,
  fx_palette_cloud,
  fx_palette_ocean,
  fx_palette_forest,
  fx_palette_rainbow,
  fx_palette_rainbowstripe,
  fx_palette_party,
  fx_palette_heat,

  fx_palette_dark,
  fx_palette_white,
  fx_palette_red,
  fx_palette_yellow,
  fx_palette_green,
  fx_palette_cyan,
  fx_palette_blue,
  fx_palette_magenta,
  fx_palette_orange,
  fx_palette_half,
  fx_palette_lowhalf,

  fx_palette_pulse_dark,
  fx_palette_pulse_white,
  fx_palette_pulse_red,
  fx_palette_pulse_yellow,
  fx_palette_pulse_green,
  fx_palette_pulse_cyan,
  fx_palette_pulse_blue,
  fx_palette_pulse_magenta,
  fx_palette_pulse_orange,
  fx_palette_pulse_half,
  fx_palette_pulse_lowhalf,

  fx_palette_pulse2_dark,
  fx_palette_pulse2_white,
  fx_palette_pulse2_red,
  fx_palette_pulse2_yellow,
  fx_palette_pulse2_green,
  fx_palette_pulse2_cyan,
  fx_palette_pulse2_blue,
  fx_palette_pulse2_magenta,
  fx_palette_pulse2_orange,
  fx_palette_pulse2_half,
  fx_palette_pulse2_lowhalf,  

  fx_palette_pulse3_dark,
  fx_palette_pulse3_white,
  fx_palette_pulse3_red,
  fx_palette_pulse3_yellow,
  fx_palette_pulse3_green,
  fx_palette_pulse3_cyan,
  fx_palette_pulse3_blue,
  fx_palette_pulse3_magenta,
  fx_palette_pulse3_orange,
  fx_palette_pulse3_half,
  fx_palette_pulse3_lowhalf,  

  fx_palette_pulse4_dark,
  fx_palette_pulse4_white,
  fx_palette_pulse4_red,
  fx_palette_pulse4_yellow,
  fx_palette_pulse4_green,
  fx_palette_pulse4_cyan,
  fx_palette_pulse4_blue,
  fx_palette_pulse4_magenta,
  fx_palette_pulse4_orange,
  fx_palette_pulse4_half,
  fx_palette_pulse4_lowhalf,    
  
  fx_palette_dw,
  fx_palette_dr,
  fx_palette_dy,
  fx_palette_dg,
  fx_palette_dc,
  fx_palette_db,
  fx_palette_dm,
  fx_palette_wr,
  fx_palette_wy,
  fx_palette_wg,
  fx_palette_wc,
  fx_palette_wb,
  fx_palette_wm,
  fx_palette_ry,
  fx_palette_rg,
  fx_palette_rc,
  fx_palette_rb,
  fx_palette_rm,
  fx_palette_yg,
  fx_palette_yc,
  fx_palette_yb,
  fx_palette_ym,
  fx_palette_gc,
  fx_palette_gb,
  fx_palette_gm,
  fx_palette_cb,
  fx_palette_cm,
  fx_palette_bm,

  fx_palette_wry,
  fx_palette_wrg,
  fx_palette_wrc,
  fx_palette_wrb,
  fx_palette_wrm,
  fx_palette_wyg,
  fx_palette_wyc,
  fx_palette_wyb,
  fx_palette_wym,
  fx_palette_wgc,
  fx_palette_wgb,
  fx_palette_wgm,
  fx_palette_wcb,
  fx_palette_wcm,
  fx_palette_wbm,

  fx_palette_dry,
  fx_palette_drg,
  fx_palette_drc,
  fx_palette_drb,
  fx_palette_drm,
  fx_palette_dyg,
  fx_palette_dyc,
  fx_palette_dyb,
  fx_palette_dym,
  fx_palette_dgc,
  fx_palette_dgb,
  fx_palette_dgm,
  fx_palette_dcb,
  fx_palette_dcm,
  fx_palette_dbm,

  fx_palette_rbm,

  fx_particles_off,
  fx_particles_pos,
  fx_particles_neg,
  fx_particles_rnd,
  fx_particles_length_1,
  fx_particles_length_2,
  fx_particles_length_3,
  fx_particles_length_4,

  fx_particles_color_dark,
  fx_particles_color_white,
  fx_particles_color_red,
  fx_particles_color_yellow,
  fx_particles_color_green,
  fx_particles_color_cyan,
  fx_particles_color_blue,
  fx_particles_color_magenta,
  fx_particles_color_orange,
  fx_particles_color_half,
  fx_particles_color_lowhalf,    

  fx_status_section_0,
  fx_status_section_1,
  fx_status_section_2,
  fx_status_section_3,
  fx_status_section_4,
  fx_status_section_5,
  fx_status_section_6,
  fx_status_section_7,
  fx_status_section_8,
  fx_status_section_9,
  fx_status_section_10,
  fx_status_section_11,
  fx_status_section_12,
  fx_status_section_13,
  fx_status_section_14,
  fx_status_section_15,
  
  fx_strip_all,  //Target all strips
  fx_strip_none, //Target no strips, why?
  fx_strip_evens, //Target even strips
  fx_strip_odds, //Target odd strips
  
  fx_stripmask_0, fx_strip = fx_stripmask_0,//make a syntactic sugar for it
  fx_stripmask_1,fx_stripmask_2,fx_stripmask_3,fx_stripmask_4,fx_stripmask_5,fx_stripmask_6,fx_stripmask_7,fx_stripmask_8,  
  fx_stripmask_9,fx_stripmask_10,fx_stripmask_11,fx_stripmask_12,fx_stripmask_13,fx_stripmask_14,fx_stripmask_15,fx_stripmask_16,
  fx_stripmask_17,fx_stripmask_18,fx_stripmask_19,fx_stripmask_20,fx_stripmask_21,fx_stripmask_22,fx_stripmask_23,fx_stripmask_24,
  fx_stripmask_25,fx_stripmask_26,fx_stripmask_27,fx_stripmask_28,fx_stripmask_29,fx_stripmask_30,fx_stripmask_31,fx_stripmask_32,
  fx_stripmask_33,fx_stripmask_34,fx_stripmask_35,fx_stripmask_36,fx_stripmask_37,fx_stripmask_38,fx_stripmask_39,fx_stripmask_40,
  fx_stripmask_41,fx_stripmask_42,fx_stripmask_43,fx_stripmask_44,fx_stripmask_45,fx_stripmask_46,fx_stripmask_47,fx_stripmask_48,
  fx_stripmask_49,fx_stripmask_50,fx_stripmask_51,fx_stripmask_52,fx_stripmask_53,fx_stripmask_54,fx_stripmask_55,fx_stripmask_56,
  fx_stripmask_57,fx_stripmask_58,fx_stripmask_59,fx_stripmask_60,fx_stripmask_61,fx_stripmask_62,fx_stripmask_63,fx_stripmask_64,
  fx_stripmask_65,fx_stripmask_66,fx_stripmask_67,fx_stripmask_68,fx_stripmask_69,fx_stripmask_70,fx_stripmask_71,fx_stripmask_72,
  fx_stripmask_73,fx_stripmask_74,fx_stripmask_75,fx_stripmask_76,fx_stripmask_77,fx_stripmask_78,fx_stripmask_79,fx_stripmask_80,
  fx_stripmask_81,fx_stripmask_82,fx_stripmask_83,fx_stripmask_84,fx_stripmask_85,fx_stripmask_86,fx_stripmask_87,fx_stripmask_88,
  fx_stripmask_89,fx_stripmask_90,fx_stripmask_91,fx_stripmask_92,fx_stripmask_93,fx_stripmask_94,fx_stripmask_95,fx_stripmask_96,
  fx_stripmask_97,fx_stripmask_98,fx_stripmask_99,fx_stripmask_100,fx_stripmask_101,fx_stripmask_102,fx_stripmask_103,fx_stripmask_104,
  fx_stripmask_105,fx_stripmask_106,fx_stripmask_107,fx_stripmask_108,fx_stripmask_109,fx_stripmask_110,fx_stripmask_111,fx_stripmask_112,
  fx_stripmask_113,fx_stripmask_114,fx_stripmask_115,fx_stripmask_116,fx_stripmask_117,fx_stripmask_118,fx_stripmask_119,fx_stripmask_120,
  fx_stripmask_121,fx_stripmask_122,fx_stripmask_123,fx_stripmask_124,fx_stripmask_125,fx_stripmask_126,fx_stripmask_127,fx_stripmask_128,
  fx_stripmask_129,fx_stripmask_130,fx_stripmask_131,fx_stripmask_132,fx_stripmask_133,fx_stripmask_134,fx_stripmask_135,fx_stripmask_136,
  fx_stripmask_137,fx_stripmask_138,fx_stripmask_139,fx_stripmask_140,fx_stripmask_141,fx_stripmask_142,fx_stripmask_143,fx_stripmask_144,
  fx_stripmask_145,fx_stripmask_146,fx_stripmask_147,fx_stripmask_148,fx_stripmask_149,fx_stripmask_150,fx_stripmask_151,fx_stripmask_152,
  fx_stripmask_153,fx_stripmask_154,fx_stripmask_155,fx_stripmask_156,fx_stripmask_157,fx_stripmask_158,fx_stripmask_159,fx_stripmask_160,
  fx_stripmask_161,fx_stripmask_162,fx_stripmask_163,fx_stripmask_164,fx_stripmask_165,fx_stripmask_166,fx_stripmask_167,fx_stripmask_168,
  fx_stripmask_169,fx_stripmask_170,fx_stripmask_171,fx_stripmask_172,fx_stripmask_173,fx_stripmask_174,fx_stripmask_175,fx_stripmask_176,
  fx_stripmask_177,fx_stripmask_178,fx_stripmask_179,fx_stripmask_180,fx_stripmask_181,fx_stripmask_182,fx_stripmask_183,fx_stripmask_184,
  fx_stripmask_185,fx_stripmask_186,fx_stripmask_187,fx_stripmask_188,fx_stripmask_189,fx_stripmask_190,fx_stripmask_191,fx_stripmask_192,
  fx_stripmask_193,fx_stripmask_194,fx_stripmask_195,fx_stripmask_196,fx_stripmask_197,fx_stripmask_198,fx_stripmask_199,fx_stripmask_200,
  fx_stripmask_201,fx_stripmask_202,fx_stripmask_203,fx_stripmask_204,fx_stripmask_205,fx_stripmask_206,fx_stripmask_207,fx_stripmask_208,
  fx_stripmask_209,fx_stripmask_210,fx_stripmask_211,fx_stripmask_212,fx_stripmask_213,fx_stripmask_214,fx_stripmask_215,fx_stripmask_216,
  fx_stripmask_217,fx_stripmask_218,fx_stripmask_219,fx_stripmask_220,fx_stripmask_221,fx_stripmask_222,fx_stripmask_223,fx_stripmask_224,
  fx_stripmask_225,fx_stripmask_226,fx_stripmask_227,fx_stripmask_228,fx_stripmask_229,fx_stripmask_230,fx_stripmask_231,fx_stripmask_232,
  fx_stripmask_233,fx_stripmask_234,fx_stripmask_235,fx_stripmask_236,fx_stripmask_237,fx_stripmask_238,fx_stripmask_239,fx_stripmask_240,
  fx_stripmask_241,fx_stripmask_242,fx_stripmask_243,fx_stripmask_244,fx_stripmask_245,fx_stripmask_246,fx_stripmask_247,fx_stripmask_248,
  fx_stripmask_249,fx_stripmask_250,fx_stripmask_251,fx_stripmask_252,fx_stripmask_253,fx_stripmask_254,fx_stripmask_255,//Same as fx_MULTI_FINISH

  fx_strip0 = fx_stripmask_1,    
  fx_strip1 = fx_stripmask_2,    
  fx_strip2 = fx_stripmask_4,    
  fx_strip3 = fx_stripmask_8,    
  fx_strip4 = fx_stripmask_16,    
  fx_strip5 = fx_stripmask_32,    
  fx_strip6 = fx_stripmask_64,    
  fx_strip7 = fx_stripmask_128,   
  
  fx_nothing = 0xFFFF
};

struct Fx {
  unsigned long timecode;
  unsigned long event;
};

enum FxTransitionType
{
  Transition_Instant         = 0,
  Transition_TimedFade       = 1,
  Transition_TimedWipePos    = 2,
  Transition_TimedWipeNeg    = 3,
  Transition_TimedWipeOutIn  = 4,
  Transition_TimedWipeInOut  = 5,
  Transition_TimedWipeRandom = 6,
  Transition_TimedFadeSin    = 7,
  Transition_TimedFadeCos    = 8,
};

enum FxTrackEndAction
{
  StopAtEnd = 0,
  LoopAtEnd = 1
};

enum    WEBRGB {
  AliceBlue = 0xF0F8FF, Amethyst = 0x9966CC, AntiqueWhite = 0xFAEBD7, Aqua = 0x00FFFF,
  Aquamarine = 0x7FFFD4, Azure = 0xF0FFFF, Beige = 0xF5F5DC, Bisque = 0xFFE4C4,
  Black = 0x000000, BlanchedAlmond = 0xFFEBCD, Blue = 0x0000FF, BlueViolet = 0x8A2BE2,
  Brown = 0xA52A2A, BurlyWood = 0xDEB887, CadetBlue = 0x5F9EA0, Chartreuse = 0x7FFF00,
  Chocolate = 0xD2691E, Coral = 0xFF7F50, CornflowerBlue = 0x6495ED, Cornsilk = 0xFFF8DC,
  Crimson = 0xDC143C, Cyan = 0x00FFFF, DarkBlue = 0x00008B, DarkCyan = 0x008B8B,
  DarkGoldenrod = 0xB8860B, DarkGray = 0xA9A9A9, DarkGrey = 0xA9A9A9, DarkGreen = 0x006400,
  DarkKhaki = 0xBDB76B, DarkMagenta = 0x8B008B, DarkOliveGreen = 0x556B2F, DarkOrange = 0xFF8C00,
  DarkOrchid = 0x9932CC, DarkRed = 0x8B0000, DarkSalmon = 0xE9967A, DarkSeaGreen = 0x8FBC8F,
  DarkSlateBlue = 0x483D8B, DarkSlateGray = 0x2F4F4F, DarkSlateGrey = 0x2F4F4F, DarkTurquoise = 0x00CED1,
  DarkViolet = 0x9400D3, DeepPink = 0xFF1493, DeepSkyBlue = 0x00BFFF, DimGray = 0x696969,
  DimGrey = 0x696969, DodgerBlue = 0x1E90FF, FireBrick = 0xB22222, FloralWhite = 0xFFFAF0,
  ForestGreen = 0x228B22, Fuchsia = 0xFF00FF, Gainsboro = 0xDCDCDC, GhostWhite = 0xF8F8FF,
  Gold = 0xFFD700, Goldenrod = 0xDAA520, Gray = 0x808080, Grey = 0x808080,
  Green = 0x008000, GreenYellow = 0xADFF2F, Honeydew = 0xF0FFF0, HotPink = 0xFF69B4,
  IndianRed = 0xCD5C5C, Indigo = 0x4B0082, Ivory = 0xFFFFF0, Khaki = 0xF0E68C,
  Lavender = 0xE6E6FA, LavenderBlush = 0xFFF0F5, LawnGreen = 0x7CFC00, LemonChiffon = 0xFFFACD,
  LightBlue = 0xADD8E6, LightCoral = 0xF08080, LightCyan = 0xE0FFFF, LightGoldenrodYellow = 0xFAFAD2,
  LightGreen = 0x90EE90, LightGrey = 0xD3D3D3, LightPink = 0xFFB6C1, LightSalmon = 0xFFA07A,
  LightSeaGreen = 0x20B2AA, LightSkyBlue = 0x87CEFA, LightSlateGray = 0x778899, LightSlateGrey = 0x778899,
  LightSteelBlue = 0xB0C4DE, LightYellow = 0xFFFFE0, Lime = 0x00FF00, LimeGreen = 0x32CD32,
  Linen = 0xFAF0E6, Magenta = 0xFF00FF, Maroon = 0x800000, MediumAquamarine = 0x66CDAA,
  MediumBlue = 0x0000CD, MediumOrchid = 0xBA55D3, MediumPurple = 0x9370DB, MediumSeaGreen = 0x3CB371,
  MediumSlateBlue = 0x7B68EE, MediumSpringGreen = 0x00FA9A, MediumTurquoise = 0x48D1CC, MediumVioletRed = 0xC71585,
  MidnightBlue = 0x191970, MintCream = 0xF5FFFA, MistyRose = 0xFFE4E1, Moccasin = 0xFFE4B5,
  NavajoWhite = 0xFFDEAD, Navy = 0x000080, OldLace = 0xFDF5E6, Olive = 0x808000,
  OliveDrab = 0x6B8E23, Orange = 0xFFA500, OrangeRed = 0xFF4500, Orchid = 0xDA70D6,
  PaleGoldenrod = 0xEEE8AA, PaleGreen = 0x98FB98, PaleTurquoise = 0xAFEEEE, PaleVioletRed = 0xDB7093,
  PapayaWhip = 0xFFEFD5, PeachPuff = 0xFFDAB9, Peru = 0xCD853F, Pink = 0xFFC0CB,
  Plaid = 0xCC5533, Plum = 0xDDA0DD, PowderBlue = 0xB0E0E6, Purple = 0x800080,
  Red = 0xFF0000, RosyBrown = 0xBC8F8F, RoyalBlue = 0x4169E1, SaddleBrown = 0x8B4513,
  Salmon = 0xFA8072, SandyBrown = 0xF4A460, SeaGreen = 0x2E8B57, Seashell = 0xFFF5EE,
  Sienna = 0xA0522D, Silver = 0xC0C0C0, SkyBlue = 0x87CEEB, SlateBlue = 0x6A5ACD,
  SlateGray = 0x708090, SlateGrey = 0x708090, Snow = 0xFFFAFA, SpringGreen = 0x00FF7F,
  SteelBlue = 0x4682B4, Tan = 0xD2B48C, Teal = 0x008080, Thistle = 0xD8BFD8,
  Tomato = 0xFF6347, Turquoise = 0x40E0D0, Violet = 0xEE82EE, Wheat = 0xF5DEB3,
  White = 0xFFFFFF, WhiteSmoke = 0xF5F5F5, Yellow = 0xFFFF00, YellowGreen = 0x9ACD32,
  FairyLight = 0xFFE42D, FairyLightNCC = 0xFF9D2A
};

uint32_t LEDRGB(uint8_t r, uint8_t g, uint8_t b);
unsigned char lerp(float mux, unsigned char a, unsigned char b);
uint32_t LerpRGB(float t, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2);
uint32_t LerpRGB(float t, uint32_t rgb1, uint32_t rgb2);
void LerpPaletteFromMicroPalette(uint32_t *palette, unsigned int paletteSize, uint32_t* microPalette, unsigned int microPaletteSize);
void CopyPalette(int numleds, uint32_t *dst, uint32_t *src);

uint32_t ShortnameToCRGB(char shortName);

void PrintFxTrackEndAction(FxTrackEndAction fxTrackEndAction);
void PrintFxPaletteUpdateType(FxPaletteUpdateType paletteUpdateType);
void PrintFxStateName(FxState s);
void PrintFxEventName(int event);
void PrintFxTransitionName(FxTransitionType t);

//////// Time code section ////////
struct TimeCode
{
  signed long timeOffset = 0;
  signed long songOffset = 0;
  unsigned long lastMatchedTimecode = 0;
};
signed long getTimecodeTimeOffset();
signed long getTimecodeSongOffset();
signed long setTimecodeTimeOffset(signed long tc);
signed long setTimecodeSongOffset(signed long tc);
void setTimecodeLastMatched(unsigned long match);
unsigned long getTimecodeLastMatched();
unsigned long GetTime();
//////// Time code section ////////



#endif
