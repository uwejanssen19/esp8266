// DisplayUtil.h

#ifndef _DISPLAYUTIL_h
#define _DISPLAYUTIL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TimUtilCheck.h"
#include "UnitStorage.h"
#include <gfxfont.h>
#include <Adafruit_GFX.h>

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>

// select the display class and display driver class in the following file (new style):
#include "GxEPD2_display_selection_new_style.h"

#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

// display const 

constexpr auto UPPER_LEFT_CORNER = 10;
constexpr auto  X_LINE_1 = UPPER_LEFT_CORNER;
constexpr auto  Y_LINE_1 = 31;
constexpr auto  X_VERSION = 120;
constexpr auto  X_IP = 300;
constexpr auto  X_DATE = 660;

constexpr auto  HLINE_LEN = 780;
constexpr auto  HLINE1_LEN = HLINE_LEN;
constexpr auto  HLINE1_X = 10;
constexpr auto  HLINE1_Y = 40;

//constexpr auto  RECT1_X = 10;
//constexpr auto  RECT1_Y = 30;
//constexpr auto  RECT1_WIDTH = 360;
//constexpr auto  RECT1_HEIGHT = 125;

constexpr auto  LEFTMOST_X = 2;
constexpr auto  TEMP1_ICON_X = LEFTMOST_X;
constexpr auto  TEMP1_ICON_MARGIN_TOP = 22;
constexpr auto  TEMP1_ICON_Y = (30 + TEMP1_ICON_MARGIN_TOP);

constexpr auto  TEMP_Y = 75; // Y for temperatures
constexpr auto  TEMP1_X = 70;
constexpr auto  TEMP1_Y = TEMP_Y;

constexpr auto  TEMP2_X = TEMP1_X + 220;
constexpr auto  TEMP2_Y = TEMP1_Y;

constexpr auto  TEMP3_X = TEMP2_X + 240;
constexpr auto  TEMP3_Y = TEMP_Y;

constexpr auto  HUM_X = TEMP1_X;
constexpr auto  HUM_Y = 95;
constexpr auto  RAIN_ICON_Y = HUM_Y + 1;
constexpr auto  RAIN_Y = 126;
constexpr auto  PRESS_ICON_X = 15;
constexpr auto  PRESS_ICON_Y = 141;
constexpr auto  PRESS_X = HUM_X;
constexpr auto  PRESS_Y = 163;
constexpr auto HLINE_DAILY_BEGIN_X = 0;
constexpr auto HLINE_DAILY_BEGIN_Y = 175+20;
constexpr auto HLINE_DAILY_WIDTH = HLINE_LEN;
constexpr auto DAILY_X = 30;
constexpr auto DAILY_Y = 225;
constexpr auto HLINE_DAILY_END_X = HLINE_DAILY_BEGIN_X;
constexpr auto HLINE_DAILY_END_Y = 240;
constexpr auto RISESET_ICON_X = 10;
constexpr auto RISESET_ICON_Y = 270;
constexpr auto SUNRISE_X = 60;
constexpr auto SUNRISE_Y = 275 + 15;
constexpr auto SUNSET_X = 60;
constexpr auto SUNSET_Y = 289 + 15;
constexpr auto MOONPHASE_ICON_X = 237;
constexpr auto MOONPHASE_ICON_Y = 265 + 15;
constexpr auto MOONRISE_X = 270;
constexpr auto MOONRISE_Y = 275 + 15;
constexpr auto LAST_EVT_X = 350;
constexpr auto LAST_EVT_Y = 275 + 15;
constexpr auto MOONSET_X = 270;
constexpr auto MOONSET_Y = 304;
constexpr auto ASTRO_EV_X = 350;
constexpr auto ASTRO_EV_Y = 304;

constexpr auto HLINE_SUNSECTION_X = 0;
constexpr auto HLINE_SUNSECTION_Y = 320;
constexpr auto HLINE_SUNSECTION_WIDTH = HLINE_LEN;
constexpr auto SUN_EVT_TIME_X = 60;
constexpr auto SUN_EVT_TIME_Y = 368;
constexpr auto AZIMUT_X = 300;
constexpr auto AZIMUT_Y = 368;
constexpr auto ELEV_X = 300;
constexpr auto ELEV_Y = 388;
constexpr auto CULM_MAX_X = 60;
constexpr auto CULM_MAX_Y = 418;

constexpr auto VERSION = "v1.07";

class DisplayUtil
{
 protected:


 public:
	void init();
	void displayData(TimUtilCheck, UnitStorageClass);
	void displayStatusMsg(String msg);
	void displayMsg(String msg);
	void display_icon(int, int, String);
	void drawDashedHLine(int16_t, int16_t, int16_t, uint16_t);
	void writeDashedLine(int16_t, int16_t, int16_t, int16_t, uint16_t);
	//void dashedRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
};


#endif

