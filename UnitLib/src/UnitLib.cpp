/*
 Name:		UnitLib.cpp
 Created:	19.05.2021 13:12:29
 Author:	uwe
 Editor:	http://www.visualmicro.com
*/

#include "UnitLib.h"
// Enable MqttClient logs

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
	if (!mqtt->isConnected()) {
		// Close connection if exists
		wclient.stop();
		// Re-establish TCP connection with MQTT broker
		LOG_PRINTFLN("Connecting with %s", mqttServer);
		wclient.connect(mqttServer, 1883);
		if (!wclient.connected()) {
			LOG_PRINTFLN("Can't establish the TCP connection");
			delay(1000);
			ESP.restart();
		}
		// Start new MQTT connection
		MqttClient::ConnectResult connectResult;
		// Connect

		MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
		options.MQTTVersion = 4;
		options.clientID.cstring = (char*)clientId;
		options.cleansession = true;
		options.keepAliveInterval = 15; // 15 seconds
		MqttClient::Error::type rc = mqtt->connect(options, connectResult);
		if (rc != MqttClient::Error::SUCCESS) {
			LOG_PRINTFLN("Connection error: %i", rc);
			return false;
		}
	}
	return true;
}

void mqttPublish(const char * topic, const char *messageValue) {
	const char* buf = messageValue;
	MqttClient::Message message;
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
	WiFi.hostname("UweSolar2");
	WiFi.begin(PRIVATE_SSID, PRIVATE_WLAN_KEY);
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