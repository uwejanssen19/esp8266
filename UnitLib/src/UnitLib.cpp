/*
 Name:		UnitLib.cpp
 Created:	19.05.2021 13:12:29
 Author:	uwe
 Editor:	http://www.visualmicro.com
*/

#include "UnitLib.h"

void logfln(const char* fmt, ...) {
	char buf[LOG_SIZE_MAX];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, LOG_SIZE_MAX, fmt, ap);
	va_end(ap);
	Serial.println(buf);
}

static WiFiClient wclient;
static MqttClient* mqtt = NULL;
#ifndef _PROTOTYPE
Adafruit_BMP085 bme;
#endif

void mqttYield(long ms) {
	mqtt->yield(ms);
}
// ============== Object to supply system functions ============================
class SystemImpl : public MqttClient::System {
public:

	unsigned long millis() const {
		return ::millis();
	}

	void yield(void) {
		::yield();
	}
};

void mqttSetup() {
	// Setup MqttClient
	logfln("in mqttSetup");
	MqttClient::System* mqttSystem = new SystemImpl;
	MqttClient::Logger* mqttLogger = new MqttClient::LoggerImpl<HardwareSerial>(Serial);
	MqttClient::Network* mqttNetwork = new MqttClient::NetworkClientImpl<WiFiClient>(wclient, *mqttSystem);
	//// Make 128 bytes send buffer
	MqttClient::Buffer* mqttSendBuffer = new MqttClient::ArrayBuffer<128>();
	//// Make 128 bytes receive buffer
	MqttClient::Buffer* mqttRecvBuffer = new MqttClient::ArrayBuffer<128>();
	//// Allow up to 2 subscriptions simultaneously
	MqttClient::MessageHandlers* mqttMessageHandlers = new MqttClient::MessageHandlersImpl<2>();
	//// Configure client options
	MqttClient::Options mqttOptions;
	////// Set command timeout to 10 seconds
	mqttOptions.commandTimeoutMs = 10000;
	//// Make client object
	mqtt = new MqttClient(
		mqttOptions, *mqttLogger, *mqttSystem, *mqttNetwork, *mqttSendBuffer,
		*mqttRecvBuffer, *mqttMessageHandlers
	);
}

bool mqttConnect(const char* mqttServer, const char* clientId)
{
	String statusMsg = "Connecting to MQTT... ";
	uint8_t retries = 5;
	if (!mqtt->isConnected()) {
		// Close connection if exists
		wclient.stop();
		// Re-establish TCP connection with MQTT broker
		LOG_PRINTFLN("Connecting with %s", mqttServer);
		int wstatus = wclient.connect(mqttServer, 1883);
		LOG_PRINTFLN("returned %d", wstatus);
		//if (!wclient.connected()) {
		//	LOG_PRINTFLN("Can't establish the TCP connection");
		//	delay(5000);
		//	ESP.reset();
		//}
		// Start new MQTT connection
		MqttClient::ConnectResult connectResult;
		// Connect

		MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
		options.MQTTVersion = 4;
		options.clientID.cstring = (char*)clientId;
		options.cleansession = true;
		options.keepAliveInterval = 15; // 15 seconds
		MqttClient::Error::type rc;
		
		LOG_PRINTFLN("error code  = %d", rc);
		while ((rc = mqtt->connect(options, connectResult)) != MqttClient::Error::SUCCESS) {
			retries--;
			LOG_PRINTFLN("error code = %d", rc);
			if (retries == 0) { // give up
				statusMsg = "MQTT connect FAILED -> restart ESP";
				Serial.println(statusMsg);
				LOG_PRINTFLN("Connection error: %i, resetting board", rc);
				ESP.reset();
			}
			delay(10000); // 10s
		}
		statusMsg = "MQTT Connected!";
		Serial.println(statusMsg);
	}
	return true;
}

void mqttPublish(const char * topic, const char *messageValue) {
	const char* buf = messageValue;
	MqttClient::Message message;
	//logfln("%s%s","in ",__FUNCTION__);
	message.qos = MqttClient::QOS0;
	message.retained = false;
	message.dup = false;
	message.payload = (void*)buf;
	message.payloadLen = strlen(buf);
	mqtt->publish(topic, message);
}
//MqttClient* getMqtt() {
//	return mqtt;
//}

void wifiSetup() {
	// Setup WiFi network
	WiFi.mode(WIFI_STA);
	WiFi.hostname(HOSTNAME);
	logfln("%s", __FUNCTION__);
	WiFi.begin(USED_SSID, PRIVATE_WLAN_KEY);
	LOG_PRINTFLN("\n");
	LOG_PRINTFLN("Connecting to WiFi");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		LOG_PRINTFLN(".");
	}
	LOG_PRINTFLN("Connected to WiFi");
	LOG_PRINTFLN("IP: %s", WiFi.localIP().toString().c_str());
}
void mqttSubscribe(const char * topic, void (*cbk)(MqttClient::MessageData& md)) {
	// Add subscribe here if required
	MqttClient::Error::type rc = mqtt->subscribe(
		topic, MqttClient::QOS0, cbk
	);
	if (rc != MqttClient::Error::SUCCESS) {
		LOG_PRINTFLN("Subscribe error: %i", rc);
		LOG_PRINTFLN("Drop connection");
		mqtt->disconnect();
		return;
	}

}
void setupOTA() {
	ArduinoOTA.onStart([]() {
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH) {
			type = "sketch";
		}
		else { // U_FS
			type = "filesystem";
		}

		// NOTE: if updating FS this would be the place to unmount FS using FS.end()
		Serial.println("Start updating " + type);
		});
	ArduinoOTA.onEnd([]() {
		Serial.println("\nEnd");
		});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
		});
	ArduinoOTA.onError([](ota_error_t error) {
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) {
			Serial.println("Auth Failed");
		}
		else if (error == OTA_BEGIN_ERROR) {
			Serial.println("Begin Failed");
		}
		else if (error == OTA_CONNECT_ERROR) {
			Serial.println("Connect Failed");
		}
		else if (error == OTA_RECEIVE_ERROR) {
			Serial.println("Receive Failed");
		}
		else if (error == OTA_END_ERROR) {
			Serial.println("End Failed");
		}
		});
	ArduinoOTA.begin();
	//TelnetStream.begin();
	Serial.println("Ready");

}

//template <class BmeType>
void printValues() {
	Serial.print("Temperature = ");
	Serial.print(bme.readTemperature());
	Serial.println(" *C");

	// only BME280
//	bme.seaLevelForAltitude(423.0, SEALEVELPRESSURE_HPA);

	Serial.print("Pressure = ");

	Serial.print(bme.readPressure()/100.0F);
	Serial.println(" hPa");

	Serial.println("BmeType");

	Serial.print("Approx. Altitude = ");
	Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
	Serial.println(" m");

	//if (typeid(Adafruit_BME280) == typeid(BmeType)) {
	//bme.seaLevelForAltitude(423.0,SEALEVELPRESSURE_HPA);
		//Serial.print("Humidity = ");
		//Serial.print(bme.readHumidity());
		//Serial.println(" %");
	//}

	Serial.println();
}
