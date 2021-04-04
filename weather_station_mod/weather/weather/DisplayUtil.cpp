// 
// 
// force definition of display object inside "GxEPD2_display_selection_new_style.h"
#define NEED_DISPLAY_DEF
#include "DisplayUtil.h"


// Define each of the *icons for display

const unsigned char moon_0_8[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xff,0xf8,0x3f,0xff,0xfc,0x3f,0xff,0xfc,0x7f,0xff,0xfe
,0x7f,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xff,0xfe
,0x7f,0xff,0xfe,0x3f,0xff,0xfc,0x3f,0xff,0xfc,0x1f,0xff,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_1[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xe1,0xf8,0x3f,0xf0,0x7c,0x3f,0xfc,0x3c,0x7f,0xfc,0x1e
,0x7f,0xfe,0x1e,0xff,0xfe,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xfe,0x0f,0x7f,0xfe,0x1e
,0x7f,0xfc,0x1e,0x3f,0xfc,0x3c,0x3f,0xf0,0x7c,0x1f,0xe1,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_2[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xe1,0xf8,0x3f,0xf0,0x7c,0x3f,0xfc,0x3c,0x7f,0xfc,0x1e
,0x7f,0xfe,0x1e,0xff,0xfe,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xfe,0x0f,0x7f,0xfe,0x1e
,0x7f,0xfc,0x1e,0x3f,0xfc,0x3c,0x3f,0xf0,0x7c,0x1f,0xe1,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_3[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xf1,0xf8,0x3f,0xf0,0x7c,0x3f,0xf0,0x3c,0x7f,0xf0,0x1e
,0x7f,0xf0,0x1e,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0x7f,0xf0,0x1e
,0x7f,0xf0,0x1e,0x3f,0xf0,0x3c,0x3f,0xf0,0x7c,0x1f,0xf1,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_4[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xc1,0xf8,0x3f,0xc0,0x7c,0x3f,0x80,0x3c,0x7f,0x00,0x1e
,0x7f,0x00,0x1e,0xff,0x00,0x0f,0xff,0x00,0x0f,0xff,0x00,0x0f,0xff,0x00,0x0f,0xff,0x00,0x0f,0xff,0x00,0x0f,0x7f,0x00,0x1e
,0x7f,0x00,0x1e,0x3f,0x80,0x3c,0x3f,0xc0,0x7c,0x1f,0xc1,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_5[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0x81,0xf8,0x3e,0x00,0x7c,0x3c,0x00,0x3c,0x78,0x00,0x1e
,0x78,0x00,0x1e,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0x78,0x00,0x1e
,0x78,0x00,0x1e,0x3c,0x00,0x3c,0x3e,0x00,0x7c,0x1f,0x81,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_6[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0x8f,0xf8,0x3e,0x0f,0xfc,0x3c,0x0f,0xfc,0x78,0x0f,0xfe
,0x78,0x0f,0xfe,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0x78,0x0f,0xfe
,0x78,0x0f,0xfe,0x3c,0x0f,0xfc,0x3e,0x0f,0xfc,0x1f,0x8f,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_7[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0x87,0xf8,0x3e,0x0f,0xfc,0x3c,0x3f,0xfc,0x78,0x3f,0xfe
,0x78,0x7f,0xfe,0xf0,0x7f,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0x7f,0xff,0x78,0x7f,0xfe
,0x78,0x3f,0xfe,0x3c,0x3f,0xfc,0x3e,0x0f,0xfc,0x1f,0x87,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_8[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0x87,0xf8,0x3e,0x0f,0xfc,0x3c,0x3f,0xfc,0x78,0x3f,0xfe
,0x78,0x7f,0xfe,0xf0,0x7f,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0x7f,0xff,0x78,0x7f,0xfe
,0x78,0x3f,0xfe,0x3c,0x3f,0xfc,0x3e,0x0f,0xfc,0x1f,0x87,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char pressure[] PROGMEM = {
0x00, 0x00, 0x84, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x84, 0x44, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc4, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x4c, 0x88, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x88, 0x88, 0x80, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x40, 0x00, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0x11, 0x08, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x01, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xc0, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x30, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x01, 0x80, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x04, 0x18, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x01, 0x00
, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x18, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x80, 0x00, 0x01, 0x80
, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x80, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x61, 0x80, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x80, 0x00, 0x03, 0xc0
, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x03, 0x80
, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00
, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00
, 0x00, 0x08, 0x00, 0x00, 0x03, 0x80, 0x3f, 0x80, 0x00, 0x00, 0x10, 0x00, 0x00, 0x03, 0x80, 0x3f, 0xe0, 0x00
, 0x00, 0x20, 0x00, 0x00, 0x03, 0x80, 0x30, 0xe0, 0x00, 0x3c, 0xc0, 0x00, 0x00, 0x03, 0xfc, 0x30, 0xe7, 0xf0
, 0xff, 0x80, 0x00, 0x00, 0x03, 0xfc, 0x30, 0xe3, 0xf0, 0xe3, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x3b, 0xe0, 0x38
, 0x01, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x3f, 0xc1, 0xf8, 0x01, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x3f, 0x07, 0xf8
, 0x01, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x30, 0x0e, 0x38, 0x01, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x30, 0x0e, 0x38
, 0x03, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x30, 0x07, 0xf8, 0x01, 0x00, 0x00, 0x00, 0x01, 0x8e, 0x30, 0x03, 0xf0
};

const unsigned char sunrise_sunset[] PROGMEM = {
0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00
,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x01,0xc0,0x01,0x80,0x03,0x80
,0x01,0xe0,0x00,0x00,0x07,0x80,0x01,0xf0,0x00,0x00,0x0f,0x80,0x00,0xf8,0x00,0x00,0x1f,0x00,0x00,0x78,0x00,0x00,0x1e,0x00
,0x00,0x38,0x03,0xc0,0x1c,0x00,0x00,0x00,0x1f,0xf8,0x00,0x00,0x00,0x00,0x7f,0xfe,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00
,0x00,0x01,0xf8,0x1f,0x80,0x00,0x00,0x03,0xe0,0x07,0xc0,0x00,0x00,0x03,0xc0,0x03,0xc0,0x00,0x00,0x07,0x80,0x01,0xe0,0x00
,0x00,0x07,0x80,0x01,0xe0,0x00,0x00,0x0f,0x00,0x00,0xf0,0x00,0x7e,0x0f,0x00,0x00,0xf0,0x7e,0xff,0x0f,0x00,0x00,0xf0,0xff
,0xff,0x0f,0x00,0x00,0xf0,0xff,0x7e,0x0f,0x00,0x00,0xf0,0x7e,0x00,0x07,0x00,0x00,0xe0,0x00,0x00,0x07,0x80,0x01,0xe0,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x07,0xff,0xff,0xe0,0x00,0x00,0x0f,0xff,0xff,0xf0,0x00,0x00,0x0f,0xff,0xff,0xf0,0x00,0x00,0x07,0xff,0xff,0xe0,0x00
};

const unsigned char clear_day[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x38, 0x00, 0x30, 0x00, 0x70, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0xf0, 0x00
, 0x00, 0x3e, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x03, 0xe0, 0x00
, 0x00, 0x0f, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0x00, 0x78, 0x03, 0x80, 0x00
, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00
, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x03, 0xf0, 0x00, 0x00
, 0x00, 0x00, 0x7c, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x78, 0x00, 0x00
, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00
, 0x00, 0x01, 0xe0, 0x00, 0x1e, 0x00, 0x00, 0x0f, 0xc1, 0xe0, 0x00, 0x1e, 0x0f, 0xc0
, 0x1f, 0xe1, 0xe0, 0x00, 0x1e, 0x1f, 0xe0, 0x1f, 0xe1, 0xe0, 0x00, 0x1e, 0x1f, 0xe0
, 0x0f, 0xc1, 0xe0, 0x00, 0x1e, 0x0f, 0xc0, 0x00, 0x01, 0xe0, 0x00, 0x1e, 0x00, 0x00
, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00
, 0x00, 0x00, 0x78, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0xf8, 0x00, 0x00
, 0x00, 0x00, 0x3f, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00
, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00
, 0x00, 0x07, 0x00, 0x78, 0x03, 0x80, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x03, 0xc0, 0x00
, 0x00, 0x1f, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0xf0, 0x00
, 0x00, 0x3c, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x38, 0x00, 0x30, 0x00, 0x70, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char temperature[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xcf, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xb7, 0xc0, 0x00, 0x00
, 0x00, 0x00, 0x0f, 0x33, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x79, 0xe0, 0x00, 0x00
, 0x00, 0x00, 0x1e, 0xfd, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1e, 0xfd, 0xe0, 0x00, 0x00
, 0x00, 0x00, 0x1e, 0x79, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x33, 0xc0, 0x00, 0x00
, 0x00, 0x00, 0x0f, 0x87, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char prob_rain[] PROGMEM = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xc0,0x00,0x00
,0x00,0x00,0x3f,0xff,0xf0,0x00,0x00,0x00,0x00,0x7f,0xff,0xfc,0x00,0x00,0x00,0x01,0xff,0xff,0xfe,0x00,0x00,0x00,0x03,0xff,0xff,0xff,0x00,0x00
,0x00,0x07,0xff,0xff,0xff,0x80,0x00,0x00,0x07,0xff,0xff,0xff,0xc0,0x00,0x00,0x0f,0xff,0xff,0xff,0xe0,0x00,0x00,0x0f,0xff,0xff,0xff,0xe0,0x00
,0x00,0x00,0x30,0x30,0x18,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00
,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00
,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x40,0x00,0x00,0x00,0x00,0x00,0x38,0xe0,0x00,0x00,0x00,0x00,0x00,0x38,0xe0,0x00,0x00
,0x00,0x00,0x00,0x1f,0xc0,0x00,0x00,0x00,0x00,0x00,0x1f,0x80,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const unsigned char barometer[] PROGMEM = {
0x00,0x1f,0xe0,0x00,0x00,0x7f,0xf8,0x00,0x01,0xff,0xfe,0x00,0x03,0xf0,0x3f,0x00,0x0f,0x80,0x07,0xc0,0x0f,0x00,0x03,0xc0,0x1e,0x00,0x01,0xe0,0x3c,0x00,0x00,0xf0
,0x38,0x00,0x3c,0x70,0x70,0x00,0x3c,0x38,0x70,0x00,0x7c,0x38,0xf0,0x00,0xfc,0x3c,0xe0,0x07,0xf0,0x1c,0xe0,0x0f,0xe0,0x1c,0xe0,0x0f,0xc0,0x1c,0xe0,0x0f,0xc0,0x1c
,0xe0,0x1f,0x80,0x1c,0xe0,0x3f,0x80,0x1c,0xf3,0xfc,0x00,0x3c,0x71,0xf8,0x00,0x38,0x70,0xf0,0x00,0x38,0x38,0x70,0x00,0x70,0x3c,0x30,0x00,0xf0,0x1e,0x10,0x01,0xe0
,0x0f,0x00,0x03,0xc0,0x0f,0x80,0x07,0xc0,0x03,0xf0,0x3f,0x00,0x01,0xff,0xfe,0x00,0x00,0x7f,0xf8,0x00,0x00,0x1f,0xe0,0x00
};

const unsigned char wind_speed[] PROGMEM = {
0x00,0x00,0x00,0x00,0x01,0xfc,0x00,0x00,0x03,0x3f,0xf0,0x00,0x85,0x3e,0x1f,0x80,0xd9,0x3e,0x1f,0x38,0xf1,0x3e,0x0f,0x0c,0xc1,0x3e,0x0f,0x0c,0xc1,0x3e,0x0f,0x0c
,0xf1,0x3e,0x0f,0x0c,0xd9,0x3e,0x0f,0x18,0xc5,0x3e,0x1f,0xc0,0xc3,0x3f,0xf0,0x00,0xc1,0xfe,0x00,0x00,0xc0,0x80,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00
,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00
,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

//const unsigned char rain[] PROGMEM = {
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x00
//,0x00,0x01,0xff,0xe0,0x00,0x00,0x00,0x00,0x07,0xff,0xf8,0x00,0x00,0x00,0x00,0x0f,0xff,0xfc,0x00,0x00,0x00,0x00,0x3f,0x80,0x7f,0x00,0x00,0x00
//,0x00,0x7e,0x00,0x1f,0x80,0x00,0x00,0x00,0x78,0x00,0x07,0x80,0x00,0x00,0x00,0xf0,0x00,0x03,0xc0,0x00,0x00,0x01,0xe0,0x00,0x01,0xec,0x00,0x00
//,0x01,0xe0,0x00,0x01,0xff,0xc0,0x00,0x03,0xc0,0x00,0x00,0xff,0xf0,0x00,0x03,0xc0,0x00,0x00,0xff,0xf8,0x00,0x03,0x80,0x00,0x00,0x40,0x7c,0x00
//,0x03,0x80,0x00,0x00,0x00,0x3e,0x00,0x07,0x80,0x00,0x00,0x00,0x1e,0x00,0x07,0x80,0x00,0x00,0x00,0x0f,0x00,0x07,0x80,0x00,0x00,0x00,0x07,0x00
//,0x07,0x80,0x00,0x00,0x00,0x07,0x00,0x03,0x80,0x00,0x00,0x00,0x07,0x80,0x03,0x80,0x00,0x00,0x00,0x07,0x80,0x03,0xc0,0x00,0x00,0x00,0x07,0x80
//,0x03,0xc0,0x78,0x00,0x78,0x07,0x80,0x01,0xe0,0x78,0x00,0x78,0x07,0x00,0x01,0xe0,0x78,0x00,0x78,0x0f,0x00,0x00,0xf0,0x78,0x00,0x78,0x0f,0x00
//,0x00,0x78,0x78,0x78,0x78,0x1e,0x00,0x00,0x78,0x78,0x78,0x78,0x3e,0x00,0x00,0x38,0x30,0x78,0x30,0x7c,0x00,0x00,0x08,0x00,0x78,0x00,0x78,0x00
//,0x00,0x00,0x00,0x78,0x00,0x70,0x00,0x00,0x00,0x00,0x78,0x00,0x40,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00
//,0x00,0x00,0x78,0x78,0x78,0x00,0x00,0x00,0x00,0x78,0x78,0x78,0x00,0x00,0x00,0x00,0x30,0x78,0x30,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00
//,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//};

const unsigned char partly_cloudy_day[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x06, 0x00, 0x0e, 0x00
, 0x00, 0x07, 0x80, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x3e, 0x00
, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x78, 0x00
, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00
, 0x00, 0x00, 0x01, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x00, 0x00
, 0x00, 0x07, 0xe7, 0xe0, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x80, 0x1f, 0x00, 0x00
, 0x00, 0xff, 0xff, 0x00, 0x0f, 0x00, 0x00, 0x03, 0xff, 0xff, 0x80, 0x07, 0x80, 0x00
, 0x07, 0xf0, 0x0f, 0xe0, 0x07, 0x80, 0x00, 0x0f, 0xc0, 0x03, 0xf0, 0x03, 0xc0, 0x00
, 0x1f, 0x00, 0x00, 0xf8, 0x03, 0xc1, 0xf8, 0x1e, 0x00, 0x00, 0x78, 0x03, 0xc3, 0xfc
, 0x3c, 0x00, 0x00, 0x3f, 0xc3, 0xc3, 0xfc, 0x3c, 0x00, 0x00, 0x3f, 0xfb, 0xc1, 0xf8
, 0x78, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x78, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00
, 0x70, 0x00, 0x00, 0x08, 0x1f, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00
, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00
, 0xf0, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00
, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00
, 0x78, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00
, 0x3c, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00
, 0x1e, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00
, 0x0f, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x1f, 0x80, 0x00
, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00
, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00
};



void DisplayUtil::init()
{
   display.init(115200);
}
void DisplayUtil::displayData(TimUtilClass timUtil, UnitStorageClass unitStorage)
{

        //  String currentIcon = "weather.darksky.home.currently.icon";
        String dailySummary = F(" Lokal veraenderliches Wetter, vereinzelt Schauer oder Sonnenschein");
        //  double windSpeed = 25.09;
        display.setRotation(2);
        display.setFont(&FreeMonoBold18pt7b);
        display.setTextColor(GxEPD_BLACK);
        display.setFullWindow();
        display.firstPage();


        do
        {
            display.fillScreen(GxEPD_WHITE);
            display.setFont(&FreeMonoBold9pt7b);

            display.setCursor(X_LINE_1, Y_LINE_1); display.println(timUtil.getTime());
            display.setCursor(X_VERSION, Y_LINE_1); display.print(VERSION);
            display.setCursor(X_IP, Y_LINE_1); display.print(unitStorage.localIP);
            display.setCursor(X_DATE, Y_LINE_1); display.println(timUtil.getDate());
            drawDashedHLine(X_LINE_1, 30, HLINE1_LEN, GxEPD_BLACK);

            display.setFont(&FreeMonoBold12pt7b);
            //dashedRect(RECT1_X, RECT1_Y, RECT1_WIDTH, RECT1_HEIGHT, GxEPD_BLACK);
            display_icon(LEFTMOST_X, TEMP1_ICON_Y, F("temperature"));
            display.setCursor(TEMP1_X, TEMP1_Y); display.println(String(unitStorage.gTemp1) + F(" C (") + String(unitStorage.gTimeTemp1) + F(")"));
            display.setCursor(TEMP2_X, TEMP1_Y); display.println(String(unitStorage.gTemp2) + F(" C (") + String(unitStorage.gTimeTemp2) + F(")"));
            display.setCursor(TEMP3_X, TEMP1_Y); display.println(String(unitStorage.gTemp3) + F(" C (") + String(unitStorage.gTimeTemp3) + F(")"));


            display.setCursor(HUM_X, HUM_Y); display.print(unitStorage.gHum2); display.println("%");
            display_icon(LEFTMOST_X, HUM_Y + 4, F("prob_rain"));
            display.setCursor(TEMP1_X, RAIN_Y); display.print(unitStorage.gRainProb); display.println(F(" Liter/qm"));
            display_icon(PRESS_ICON_X, PRESS_ICON_Y, F("barometer"));
            display.setCursor(PRESS_X, PRESS_Y); display.print(unitStorage.gPress2); display.println("hPa");

            display.setFont(&FreeMonoBold9pt7b);
            drawDashedHLine(HLINE_DAILY_BEGIN_X, HLINE_DAILY_BEGIN_Y, HLINE_DAILY_WIDTH, GxEPD_BLACK);
            display.setCursor(DAILY_X, DAILY_Y); display.println(dailySummary);
            drawDashedHLine(HLINE_DAILY_END_X, HLINE_DAILY_END_Y, HLINE_DAILY_WIDTH, GxEPD_BLACK);
            display.setFont(&FreeMonoBold9pt7b);
            display_icon(RISESET_ICON_X, RISESET_ICON_Y, "sunrise_sunset");
            display.setCursor(SUNRISE_X, SUNRISE_Y); display.println(unitStorage.gSunRise);
            display.setCursor(SUNSET_X, SUNSET_Y); display.println(unitStorage.gSunSet);
            display.setFont(&FreeMonoBold18pt7b);
            display_icon(MOONPHASE_ICON_X, MOONPHASE_ICON_Y, "moon_" + String(unitStorage.gMoonPhase));
            display.setFont(&FreeMonoBold9pt7b);
            display.setCursor(MOONRISE_X, MOONRISE_Y); display.println(unitStorage.gMoonRise);
            display.setCursor(LAST_EVT_X, LAST_EVT_Y); display.println("Letzter Eintrag");
            display.setCursor(MOONSET_X, MOONSET_Y); display.println(unitStorage.gMoonSet);
            display.setCursor(ASTRO_EV_X, ASTRO_EV_Y); display.println(unitStorage.gLastEventTime + ": " + unitStorage.gAstroEvent);

            drawDashedHLine(HLINE_SUNSECTION_X, HLINE_SUNSECTION_Y, HLINE_SUNSECTION_WIDTH, GxEPD_BLACK);
            display.setCursor(SUN_EVT_TIME_X, SUN_EVT_TIME_Y); display.println("Sonnenstand um: " + String(unitStorage.gAstroTime));
            display.setCursor(AZIMUT_X, AZIMUT_Y); display.println("Azimut: " + String(unitStorage.gAzimut));
            display.setCursor(ELEV_X, ELEV_Y); display.println("Hoehe: " + String(unitStorage.gElevation));
            display.setCursor(CULM_MAX_X, CULM_MAX_Y); display.println("Hoechststand bisher: " + String(unitStorage.gSunCulm));
        } while (display.nextPage());

}
void DisplayUtil::drawDashedHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    display.startWrite();
    writeDashedLine(x, y, x + w - 1, y, color);
    display.endWrite();
}
#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

void DisplayUtil::writeDashedLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    bool hole = false; //make it dash by using a hole every second pixel
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    }
    else {
        ystep = -1;
    }

    for (; x0 <= x1; x0++) {
        if (steep) {
            if (!hole) display.writePixel(y0, x0, color);
            hole = !hole;
        }
        else {
            if (!hole) display.writePixel(x0, y0, color);
            hole = !hole;
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

//void DisplayUtil::dashedRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
//    display.startWrite();
//    writeDashedLine(x, y, x + w - 1, y, color);
//    writeDashedLine(x, y, x, y + h - 1, color);
//    writeDashedLine(x + w - 1, y, x + w - 1, y + h - 1, color);
//    writeDashedLine(x, y + h - 1, x + w - 1, y + h - 1, color);
//    display.endWrite();
//}

void DisplayUtil::display_icon(int x, int y, String icon_name) {
    int scale = 10; // Adjust size as necessary
    if (icon_name == F("partly-cloudy-day"))
        display.drawBitmap(x, y, partly_cloudy_day, 54, 50, GxEPD_BLACK);
    else if (icon_name == F("clear-day"))
        display.drawBitmap(x, y, clear_day, 54, 50, GxEPD_BLACK);
    //else if (icon_name == "rain")
    //  display.drawBitmap(x, y, rain, 54, 50, GxEPD_BLACK);
    else if (icon_name == F("sunrise_sunset"))
        display.drawBitmap(x, y, sunrise_sunset, 48, 36, GxEPD_BLACK);
    else if (icon_name == F("prob_rain"))
        display.drawBitmap(x, y, prob_rain, 54, 50, GxEPD_BLACK);
    else if (icon_name == F("temperature"))
        display.drawBitmap(x, y, temperature, 54, 50, GxEPD_BLACK);
    else if (icon_name == F("pressure"))
        display.drawBitmap(x, y, pressure, 69, 64, GxEPD_BLACK);
    else if (icon_name == "moon_0")
        display.drawBitmap(x, y, moon_0_8, 24, 24, GxEPD_BLACK);
    else if (icon_name == "moon_1")
        display.drawBitmap(x, y, moon_2, 24, 24, GxEPD_BLACK);
    else if (icon_name == "moon_2")
        display.drawBitmap(x, y, moon_3, 24, 24, GxEPD_BLACK);
    else if (icon_name == "moon_3")
        display.drawBitmap(x, y, moon_4, 24, 24, GxEPD_BLACK);
    else if (icon_name == "moon_4")
        display.drawBitmap(x, y, moon_5, 24, 24, GxEPD_BLACK);
    else if (icon_name == "moon_5")
        display.drawBitmap(x, y, moon_6, 24, 24, GxEPD_BLACK);
    else if (icon_name == "moon_6")
        display.drawBitmap(x, y, moon_6, 24, 24, GxEPD_BLACK);
    else if (icon_name == "moon_7")
        display.drawBitmap(x, y, moon_8, 24, 24, GxEPD_BLACK);
    else if (icon_name == "moon_8")
        display.drawBitmap(x, y, moon_0_8, 24, 24, GxEPD_BLACK);
    else if (icon_name == "barometer")
        display.drawBitmap(x, y, barometer, 30, 30, GxEPD_BLACK);
    else if (icon_name == "wind_speed")
        display.drawBitmap(x, y, wind_speed, 30, 30, GxEPD_BLACK);
}
