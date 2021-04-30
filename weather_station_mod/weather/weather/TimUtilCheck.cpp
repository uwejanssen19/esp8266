#include "TimUtilCheck.h"
#include <time.h>
void TimUtilCheck::setTimeOfLastMsg()
{
	time(&now);                       // read the current time
	// update the structure tm with the current time
	localtime_r(&now, &lastMessage);
	this->firstMsgReceived = true;

}
void TimUtilCheck::setFirstMessageReceived(boolean val) {
	this->firstMsgReceived = val;
}

boolean TimUtilCheck::getFirstMessageReceived()
{
	return firstMsgReceived;
}


boolean TimUtilCheck::lastMsgTooLate(String &msg) {
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
	String tmpMsg = "last msg came at " + String(lastMessage.tm_hour) + ":" + String(lastMessage.tm_min) + ", data_received = " + firstMsgReceived;
	Serial.println(tmpMsg);
	//displayUtil.displayStatusMsg(tmpMsg);
	msg = tmpMsg;
	// value only relevant if at least 1 mqtt topic has been received
	boolean retVal = (diff > MAX_WAIT_FOR_ANY_MQTT) && firstMsgReceived;
	return retVal; // true if no msg at least MAX_WAIT_FOR_ANY_MQTT units
}

TimUtilCheck::TimUtilCheck() : TimUtilBase() {}