// TimUtil.h

#ifndef _TIMUTIL_h
#define _TIMUTIL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <WiFiUdp.h>
#include <TimeLib.h>
#include <NTPClient.h>

class TimUtilClass
{
 private:
	 String mTime = "no time";
	 String mDate = "no date";
	 WiFiUDP ntpUDP;
	 NTPClient mTimeClient;
 protected:

 public:
	void init();
	String getTime();
	String getDate();
	void update();
	TimUtilClass();
	void setTimeClient(NTPClient ntpcl);
};

extern TimUtilClass TimUtil;

#endif

