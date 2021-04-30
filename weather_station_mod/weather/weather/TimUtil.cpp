// 
// 
// 

#include "TimUtil.h"
#include "time.h"
#include "UnitStorage.h"
#include "DisplayUtil.h"
time_t now;// this is the epoch
tm timeStruct;     // the structure tm holds time information in a more convient way

extern UnitStorageClass unitStorage;
extern DisplayUtil displayUtil;


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
	localtime_r(&now, &timeStruct);           // update the structure tm with the current time
	char tbuffer[6];
	char dbuffer[11];
	strftime(tbuffer, sizeof(tbuffer), "%X", &timeStruct);
	strftime(dbuffer, sizeof(dbuffer), "%d.%m.%Y", &timeStruct);
	this->mDate = String(dbuffer);
	this->mTime = String(tbuffer);
	//Serial.print("UHR: "); Serial.println(mTime);
	//Serial.print("TAG: "); Serial.println(mDate);
}


TimUtilClass::TimUtilClass() {
	this->init();
}

int TimUtilClass::getHour()
{
	return 0;
}

void TimUtilClass::setTimeOfLastMsg()
{
	time(&now);                       // read the current time
	// update the structure tm with the current time
	localtime_r(&now, &lastMessage);
	unitStorage.firstMsgReceived = true;

}
boolean TimUtilClass::lastMsgTooLate() {
	time(&now);                       // read the current time
	localtime_r(&now, &timeStruct);   // update the structure tm with the current time
	// if current time < lastMessage we have an overflow e.g. current time 01:01  & last message 23:58
	// thus lastMessage  + MAX_WAIT_FOR_TEMP2  get too big
	// so add max units (24 hours or 60 minutes, respectively) to current time if (current time < lastMessage) in order to fix overflow
	int currentHour = timeStruct.tm_hour;
	if (currentHour < lastMessage.tm_hour) { currentHour += 24; }
#if defined(VM_DEBUG)
	Serial.print("last time value = "); Serial.println(this->lastMessage);
	Serial.print("currrent value = "); Serial.println(currentHour);
	Serial.print("firstMsgReceived  = "); Serial.println(unitStorage.firstMsgReceived);
#endif
	constexpr auto MAX_WAIT_FOR_ANY_MQTT = 2;

	int diff = (currentHour - lastMessage.tm_hour);
	String tmpMsg = "last msg came at " + String(lastMessage.tm_hour) + ":" + String(lastMessage.tm_min) + ", data_received = " + unitStorage.firstMsgReceived;
	Serial.println(tmpMsg);
	displayUtil.displayStatusMsg(tmpMsg);
	// value only relevant if at least 1 mqtt topic has been received
	boolean retVal = (diff > MAX_WAIT_FOR_ANY_MQTT) && unitStorage.firstMsgReceived;
	return retVal; // true if no msg at least MAX_WAIT_FOR_ANY_MQTT units
}

