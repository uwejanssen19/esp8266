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
#define MQTT_LOG_ENABLED 0
#define LOG_PRINTFLN(fmt, ...)	logfln(fmt, ##__VA_ARGS__)
#define LOG_SIZE_MAX 128


#include <cred.h>
#include <WiFiUdp.h>
//#include <WiFiServerSecureBearSSL.h>
//#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecure.h>
#include <WiFiServer.h>
//#include <WiFiClientSecureBearSSL.h>
//#include <WiFiClientSecureAxTLS.h>
//#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
//#include <CertStoreBearSSL.h>
//#include <BearSSLHelpers.h>
#include <MqttClient.h>
#include <ArduinoOTA.h>

#ifndef _PROTOTYPE  // no sensor implementation for lab edition ( = _PROTOTYPE ) 
#include <Adafruit_BMP085.h>
//#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#endif


void mqttSetup(/*MqttClient * &/*, WiFiClient &*/);
bool mqttConnect(/*MqttClient * mqttClient, */const char* mqttServer, const char * clientId/* , WiFiClient wclient*/);
void mqttPublish(/*MqttClient * mqttClient, */const char * topic, const char * value);
//MqttClient* getMqtt();
void wifiSetup();
void logfln(const char* fmt, ...);
void mqttYield(long ms);
void mqttSubscribe(const char* topic, void (*cbk)(MqttClient::MessageData& md));
void printValues();
#ifndef _PROTOTYPE // no sensor implementation for lab edition
extern Adafruit_BMP085 bme;
//extern Adafruit_BME280 bme;
#endif

#endif
