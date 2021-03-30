// 
// 
// 

#include "TimUtil.h"
time_t now;                         // this is the epoch
tm tm;                              // the structure tm holds time information in a more convient way

void TimUtilClass::init() {
//	Serial.println("TimUtilClass::init()");
	configTime(MY_TZ, "de.ntp.pool.org");
}
String TimUtilClass::getTime() {
	return mTime;
}
String TimUtilClass::getDate() {
	return mDate;
}

//void showTime() {
//time(&now);                       // read the current time
//localtime_r(&now, &tm);           // update the structure tm with the current time
//Serial.print("year:");
//Serial.print(tm.tm_year + 1900);  // years since 1900
//Serial.print("\tmonth:");
//Serial.print(tm.tm_mon + 1);      // January = 0 (!)
//Serial.print("\tday:");
//Serial.print(tm.tm_mday);         // day of month
//Serial.print("\thour:");
//Serial.print(tm.tm_hour);         // hours since midnight  0-23
//Serial.print("\tmin:");
//Serial.print(tm.tm_min);          // minutes after the hour  0-59
//Serial.print("\tsec:");
//Serial.print(tm.tm_sec);          // seconds after the minute  0-61*
//Serial.print("\twday");
//Serial.print(tm.tm_wday);         // days since Sunday 0-6
//if (tm.tm_isdst == 1)             // Daylight Saving Time flag
//Serial.print("\tDST");
//else
//Serial.print("\tstandard");
//Serial.println();
//}

void TimUtilClass::update() {
	time(&now);                       // read the current time
	localtime_r(&now, &tm);           // update the structure tm with the current time
	mTime = String(tm.tm_hour) + ":" + String(tm.tm_min);
	mDate = String(tm.tm_mday) + "." + String(tm.tm_mon+1) + "." +String(tm.tm_year+1900);
	//Serial.print("UHR: "); Serial.println(mTime);
	//Serial.print("TAG: "); Serial.println(mDate);
}


TimUtilClass::TimUtilClass() {
//		Serial.println("IN CTOR TimUtilClass::TimUtilClass()");
	this->init();
}

