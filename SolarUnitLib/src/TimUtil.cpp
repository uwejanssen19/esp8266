// 
// 
// 

#include "TimUtil.h"
#include "time.h"

void TimUtilBase::init() {
//	Serial.println("TimUtilBase::init() begin ");
	//configTime(MY_TZ, "de.ntp.pool.org");
	configTime(MY_TZ, "fritz.box");
	//	Serial.println("TimUtilBase::init() end");
}
String TimUtilBase::getTime() {
	return mTime;
}
String TimUtilBase::getDate() {
	return mDate;
}

//void TimUtilBase::showTime() {
//time(&now);                       // read the current time
//localtime_r(&now, &timeStruct);           // update the structure tm with the current time
//Serial.print("year:");
//Serial.print(timeStruct.tm_year + 1900);  // years since 1900
//Serial.print("\tmonth:");
//Serial.print(timeStruct.tm_mon + 1);      // January = 0 (!)
//Serial.print("\tday:");
//Serial.print(timeStruct.tm_mday);         // day of month
//Serial.print("\thour:");
//Serial.print(timeStruct.tm_hour);         // hours since midnight  0-23
//Serial.print("\tmin:");
//Serial.print(timeStruct.tm_min);          // minutes after the hour  0-59
//Serial.print("\tsec:");
//Serial.print(timeStruct.tm_sec);          // seconds after the minute  0-61*
//Serial.print("\twday");
//Serial.print(timeStruct.tm_wday);         // days since Sunday 0-6
//if (timeStruct.tm_isdst == 1)             // Daylight Saving Time flag
//  Serial.print("\tDST");
//else
//  Serial.print("\tstandard");
//  Serial.println();
//}

void TimUtilBase::update() {
	time(&now);                       // read the current time
	localtime_r(&now, &timeStruct);           // update the structure tm with the current time
	char tbuffer[6];
	char dbuffer[11];
	strftime(tbuffer, sizeof(tbuffer), "%X", &timeStruct);
	strftime(dbuffer, sizeof(dbuffer), "%d.%m.%Y", &timeStruct);
	this->mDate = String(dbuffer);
	this->mTime = String(tbuffer);
	Serial.print("UHR: "); Serial.println(mTime);
	//Serial.print("TAG: "); Serial.println(mDate);
}


TimUtilBase::TimUtilBase() {
	this->init();
}

int TimUtilBase::getHour()
{
	return 0;
}

void TimUtilBase::setTimeOfLastMsg()
{
}

