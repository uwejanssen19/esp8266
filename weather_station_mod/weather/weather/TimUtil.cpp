// 
// 
// 

#include "TimUtil.h"

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
//// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
void TimUtilClass::init() {
	Serial.println("TimUtilClass::init()");
    mTimeClient.begin();
}
String TimUtilClass::getTime() {
	return mTime;
}
String TimUtilClass::getDate() {
	return mDate;
}
void TimUtilClass::setTimeClient(NTPClient cl) {
	this->mTimeClient = cl;
}
void TimUtilClass::update() {
	mTimeClient.update();
	time_t utc = mTimeClient.getEpochTime();
	setTime(utc);
	mDate = String(day()) + String(". ") + String(monthShortStr(month())) + String(" ") + String(year());
	mTime = mTimeClient.getFormattedTime();
	Serial.println(mDate);
}

TimUtilClass::TimUtilClass() : ntpUDP(),mTimeClient(ntpUDP) {
	Serial.println("IN CTOR TimUtilClass::TimUtilClass()");
	this->init();
}

