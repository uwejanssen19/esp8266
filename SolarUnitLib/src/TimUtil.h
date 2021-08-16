
#ifndef _TIMUTIL_h
#define _TIMUTIL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
constexpr auto MY_TZ = "CET-1CEST,M3.5.0/02,M10.5.0/03" ;

class TimUtilBase
{
 private:
	 String mTime = "no time";
	 String mDate = "no date";
 protected:
	 time_t now;// this is the epoch
	 tm timeStruct;     // the structure tm holds time information in a more convient way
 public:
	void init();
	String getTime();
	String getDate();
	void update();
	TimUtilBase();
	int getHour();
	void setTimeOfLastMsg();
};

extern TimUtilBase TimUtil;

#endif

