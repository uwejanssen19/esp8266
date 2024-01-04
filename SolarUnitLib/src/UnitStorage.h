// UnitStorage.h

#ifndef _UNITSTORAGE_h
#define _UNITSTORAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class UnitStorageClass
{
 protected:


 public:
	void init();
#ifdef WEATHER_ASTRO
	String localIP = "";
	String gTemp1 = "-1";
	String gTemp2 = "-1";
	String gTemp3 = "-1";
	String gPress2 = "-1";
	String gHum2 = "-1";
	String gRainProb = "-1";
	String gMoonPhase = "-1";
	String gMoonRise = "-1";
	String gMoonSet = "-1";
	String gSunRise = "-1";
	String gSunSet = "-1";
	String gAzimut = "-1";
	String gElevation = "-1";
	String gAstroTime = "-1";
	String gSunCulm = "-1";
	String gAstroEvent = "Waiting ...";
	String gLastEventTime = "99:99";
	String gTimeTemp1 = "HH:MM";
	String gTimeTemp2 = "HH:MM";
	String gTimeTemp3 = "HH:MM";
	String gDaily = "";
#endif // ASTRO & WEATHER
#ifdef SMART_HOME
	String PV_Power="3.33";
	String  SOC = "55.5";
	String  GridPower = "2.22";
	//String  ConsumedPower = "-4.14";
	String  Mini600 = "1";
	String  Wind = "2";
#define MAX_PAYLOAD 32
	char payload[MAX_PAYLOAD];
#endif // SMART_HOME
	unsigned short itemPtr = 2; // stores which item is currently displayed
};

extern UnitStorageClass UnitStorage;

#endif

