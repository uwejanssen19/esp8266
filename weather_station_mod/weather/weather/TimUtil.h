
#ifndef _TIMUTIL_h
#define _TIMUTIL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Time.h>
// https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
constexpr auto MY_TZ = "CET-1CEST,M3.5.0/02,M10.5.0/03" ;

class TimUtilClass
{
 private:
	 String mTime = "no time";
	 String mDate = "no date";
 protected:

 public:
	void init();
	String getTime();
	String getDate();
	void update();
	TimUtilClass();
};

extern TimUtilClass TimUtil;

#endif

