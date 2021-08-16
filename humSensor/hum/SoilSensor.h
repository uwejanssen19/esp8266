

#ifndef _SoilSensor_h
#define _SoilSensor_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif

#include <Adafruit_seesaw.h>
class SoilSensor 
{
private:

public:
    uint16_t readSoilHum();
    float readSoilTemp();   
    void init();
};



