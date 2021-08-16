
#include "SoilSensor.h"
Adafruit_seesaw ss;

void SoilSensor::init() {
		if (!ss.begin(0x36)) {
			Serial.println("ERROR! seesaw not found");
			while (1);
		}
		else
		{
		  Serial.print("seesaw started! version: ");
		  Serial.println(ss.getVersion(), HEX);
	}
}
uint16_t SoilSensor::readSoilHum()
{
	uint16_t capread = ss.touchRead(0);
	Serial.print("Capacitive: "); Serial.println(capread);
	return capread;
}

float SoilSensor::readSoilTemp()
{
	float tempC = ss.getTemp();
	Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
	return tempC;
}
