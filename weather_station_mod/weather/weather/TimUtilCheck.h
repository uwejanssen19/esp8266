#pragma once
#ifndef _TIMEUTILCHECK_h
#define _TIMEUTILCHECK_h
#include "TimUtil.h"
class TimUtilCheck :
    public TimUtilBase
{
 private:
    tm lastMessage;
    boolean firstMsgReceived = false;
public:
    void setTimeOfLastMsg();
    void setFirstMessageReceived(boolean);
    boolean getFirstMessageReceived();
    boolean lastMsgTooLate(String &msg);
    TimUtilCheck();
};

#endif