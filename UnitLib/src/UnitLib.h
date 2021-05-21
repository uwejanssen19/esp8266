/*
 Name:		UnitLib.h
 Created:	19.05.2021 13:12:29
 Author:	uwe
 Editor:	http://www.visualmicro.com
*/

#ifndef _UnitLib_h
#define _UnitLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <MqttClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

#define LOG_PRINTFLN(fmt, ...)	logfln(fmt, ##__VA_ARGS__)
#define LOG_SIZE_MAX 128


void mqttSetup(/*MqttClient * &/*, WiFiClient &*/);
bool mqttConnect(/*MqttClient * mqttClient, */const char* mqttServer, const char * clientId/* , WiFiClient wclient*/);
void mqttPublish(/*MqttClient * mqttClient, */const char * topic, const char * value);
//MqttClient* getMqtt();
void wifiSetup();
void logfln(const char* fmt, ...);
void mqttYield(long ms);
void mqttSubscribe(const char* topic, void (*cbk)(MqttClient::MessageData& md));

#endif

