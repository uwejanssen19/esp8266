#pragma once
#ifndef _MQTTUTIL_h
#define _MQTTUTIL_h
// Include library
#include <MqttClient.h>
#include <WiFiClient.h>
#include "UnitStorage.h"
#include "TimUtil.h"


class MqttUtil : public MqttClient
{
private:
	WiFiClient wclient;
//	MqttClient* mqtt;

	MqttClient::System* mqttSystem;
	MqttClient::Logger* mqttLogger;
	MqttClient::Network* mqttNetwork;
	//// Make 128 bytes send buffer
	MqttClient::Buffer* mqttSendBuffer;
	//// Make 128 bytes receive buffer
	MqttClient::Buffer* mqttRecvBuffer;
	//// Allow up to 2 subscriptions simultaneously
	MqttClient::MessageHandlers* mqttMessageHandlers;
	//// Configure client options
	MqttClient::Options mqttOptions;

	UnitStorageClass unitStorage;
	TimUtilBase timUtil;
//	void callbackTemp1(char* x, uint16_t dummy);
public:
	//MqttClient getClient();
	MqttUtil(WiFiClient &wclient, UnitStorageClass &unitStorage, TimUtilBase &timUtil);
	//void mqttConnect(void* (displayMsg)(String msg));
	void mqttConnect();
	void mqttSubscribe(void* (function)(char* payload), char * topic);
	void unsubscribe();
//	void processMessage(MqttClient::MessageData& md);
};

// ============== Object to supply system functions ============================
class System : public MqttClient::System {
public:

	unsigned long millis() const {
		return ::millis();
	}

	void yield(void) {
		::yield();
	}
};





/* ###################################################################################################################### old code:*/
//#include <WiFiClient.h>
//
//#include <Adafruit_MQTT_FONA.h>
//#include "Adafruit_MQTT_Client.h"
//#include "Adafruit_MQTT.h"
//
//#include "UnitStorage.h"
//#include "TimUtil.h"
//
//#define CALLBACK_NAME_ONLY(NAME) callback ## NAME
//#define CALLBACK_REF_DECL(NAME)  CALLBACK_NAME_ONLY(NAME) (char* x, uint16_t dummy)
//// MQTT const
//#define AIO_SERVER "garden-control.fritz.box"
//#define AIO_SERVERPORT (int)1883
//#define MY_QOS (uint8_t)MQTT_QOS_0
//
//
//class MqttUtil
//{
//private:
//	Adafruit_MQTT_Client mqtt;
//	Adafruit_MQTT_Subscribe subscribeTemp1;
////	void CALLBACK_REF_DECL(Temp1);
//	UnitStorageClass unitStorage;
//	TimUtilBase timUtil;
////	void callbackTemp1(char* x, uint16_t dummy);
//public:
//	void mqttConnect();
//	void mqttConnect(void(*displayMsg)(String msg));
//	Adafruit_MQTT_Client getClient();
//	void processPackets(int timeout);
//	MqttUtil(WiFiClient wclient, UnitStorageClass unitStorage, TimUtilBase timUtil);
//	void mqttSubscribe();
//	void unsubscribe();
//};
//
#endif // _MQTTUTIL_h