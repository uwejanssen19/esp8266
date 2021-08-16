#include "MqttUtil.h"

// Enable MqttClient logs
#define MQTT_LOG_ENABLED 0


#define LOG_PRINTFLN(fmt, ...)	logfln(fmt, ##__VA_ARGS__)
#define LOG_SIZE_MAX 128
void logfln(const char* fmt, ...) {
	char buf[LOG_SIZE_MAX];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, LOG_SIZE_MAX, fmt, ap);
	va_end(ap);
	Serial.println(buf);
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


//MqttClient MqttUtil::getClient()
//{
//	return *mqtt;
//}
MqttUtil::MqttUtil(WiFiClient& wclient, UnitStorageClass& unitStorage, TimUtilBase& timUtil)
	: MqttClient(mqttOptions, *mqttLogger, *mqttSystem, *mqttNetwork, *mqttSendBuffer, *mqttRecvBuffer, *mqttMessageHandlers, mqttOptions.commandTimeoutMs),
	wclient(wclient),
	mqttSystem(new SystemImpl),
	mqttLogger(new MqttClient::LoggerImpl<HardwareSerial>(Serial)),
	mqttNetwork(new MqttClient::NetworkClientImpl<WiFiClient>(wclient, *mqttSystem)),
	mqttSendBuffer(new MqttClient::ArrayBuffer<128>()),
	mqttRecvBuffer(new MqttClient::ArrayBuffer<128>()),
	mqttMessageHandlers(new MqttClient::MessageHandlersImpl<2>()),
//	mqttOptions,
	/*mqtt(new MqttClient(
		mqttOptions, *mqttLogger, *mqttSystem, *mqttNetwork, *mqttSendBuffer,
		*mqttRecvBuffer, *mqttMessageHandlers)),*/
	unitStorage(unitStorage),
	timUtil(timUtil)

	//MqttClient(const Options& options, Logger& logger, System& system, Network& network,
	//	Buffer& sendBuffer, Buffer& recvBuffer, MessageHandlers& messageHandlers,
	//	unsigned long netMinTmMs = 10)
{



	//mqttOptions.commandTimeoutMs = 10000;

	//{
	//	// Setup MqttClient
	//	/* MqttClient::System* */ mqttSystem = new System;
	//	/* MqttClient::Logger* */ mqttLogger = new MqttClient::LoggerImpl<HardwareSerial>(Serial);
	//	/* MqttClient::Network* */ mqttNetwork = new MqttClient::NetworkClientImpl<WiFiClient>(wclient, *mqttSystem);
	//	//// Make 128 bytes send buffer
	//	/* MqttClient::Buffer* */ mqttSendBuffer = new MqttClient::ArrayBuffer<128>();
	//	//// Make 128 bytes receive buffer
	//	/* MqttClient::Buffer* */ mqttRecvBuffer = new MqttClient::ArrayBuffer<128>();
	//	//// Allow up to 2 subscriptions simultaneously
	//	/* MqttClient::MessageHandlers* */ mqttMessageHandlers = new MqttClient::MessageHandlersImpl<2>();
	//	//// Configure client options
	//	/*MqttClient::Options mqttOptions;*/
	//	////// Set command timeout to 10 seconds
	//	mqttOptions.commandTimeoutMs = 10000;
	//	//// Make client object
	//	mqtt = new MqttClient(
	//		mqttOptions, *mqttLogger, *mqttSystem, *mqttNetwork, *mqttSendBuffer,
	//		*mqttRecvBuffer, *mqttMessageHandlers
	//	);

	//}
}
//void MqttUtil::mqttConnect(void* (displayMsg)(String msg)) {
	void MqttUtil::mqttConnect() {

		#define GIVE_UP  "Can't establish the TCP connection, give up"
		#define CONNECTING  "Connecting"
		#define CONNECTED  "Connected"
		#define CONN_ERR "Connection error : "
		#define INT_FMT_SPEC "%i"
	// painful memory saving String concatenation BEGIN 
	String  CONN_ERR_P;
	CONN_ERR_P.reserve(sizeof(CONN_ERR) + sizeof(INT_FMT_SPEC) + 1);
	CONN_ERR_P += CONN_ERR;
	CONN_ERR_P += INT_FMT_SPEC;
	// painful memory saving String concatenation END

	// Check connection status
	if (!isConnected()) {
		// Close connection if exists
		wclient.stop();
		// Re-establish TCP connection with MQTT broker
		LOG_PRINTFLN(CONNECTING);
		wclient.connect("garden-control.fritz.box", 1883);
		if (!wclient.connected()) {
			LOG_PRINTFLN(GIVE_UP);
			//displayMsg(GIVE_UP);
			delay(5000);
			ESP.reset();
		}
		// Start new MQTT connection
		MqttClient::ConnectResult connectResult;
		// Connect
		
			MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
			options.MQTTVersion = 4;
			options.clientID.cstring = (char*)"UweSolar2";
			options.cleansession = true;
			options.keepAliveInterval = 15; // 15 seconds
			MqttClient::Error::type rc = connect(options, connectResult);
			if (rc != MqttClient::Error::SUCCESS) {
				LOG_PRINTFLN(CONN_ERR_P.c_str(), rc);
				//displayMsg(CONN_ERR + rc);
				return;
			}
	}
	else {
		LOG_PRINTFLN(CONNECTED);
		//displayMsg(CONNECTED);
	}

}
void processMessage(MqttClient::MessageData& md);
void MqttUtil::mqttSubscribe(void* (function)(char* payload), char * topic) {

	// Add subscribe here if required
	MqttClient::Error::type rc = subscribe(
		topic, MqttClient::QOS0, processMessage
	);
	if (rc != MqttClient::Error::SUCCESS) {
		LOG_PRINTFLN("Subscribe error: %i", rc);
		LOG_PRINTFLN("Drop connection");
		disconnect();
		return;
	}

		//    //subscribeTemp1.setCallback(CALLBACK_NAME_ONLY(Temp1));
		//    subscribeTemp1.setCallback(callbackTemp1);
		//    //temp2.setCallback(CALLBACK_REF(Temp2));
		//    //temp3.setCallback(CALLBACK_REF(Temp3));
		//    //press2.setCallback(CALLBACK_REF(Press2));
		//    //hum2.setCallback(CALLBACK_REF(Hum2));
		//    //rainProb.setCallback(CALLBACK_REF(RainProb));
		//    //sunRise.setCallback(CALLBACK_REF(SunRise));
		//    //sunSet.setCallback(CALLBACK_REF(SunSet));
		//    //moonRise.setCallback(CALLBACK_REF(MoonRise));
		//    //moonSet.setCallback(CALLBACK_REF(MoonSet));
		//    //moonPhase.setCallback(CALLBACK_REF(MoonPhase));
		//    //azimuth.setCallback(CALLBACK_REF(Azimut));
		//    //elevation.setCallback(CALLBACK_REF(Elevation));
		//    //astrotimestamp.setCallback(CALLBACK_REF(AstroTime));
		//    //sunculm.setCallback(CALLBACK_REF(SunCulm));
		//    //astroevent.setCallback(CALLBACK_REF(AstroEvent));
		//
		//    // Setup MQTT subscriptions
		//    mqtt.subscribe(&subscribeTemp1);
	}

void MqttUtil::unsubscribe()
{
}

void processMessage(MqttClient::MessageData& md) {
	const MqttClient::Message& msg = md.message;
#define BUFLEN 128
	if (msg.payloadLen + 1 > BUFLEN) {
		Serial.println("msg received too big");
		ESP.restart();
	}
	char buffer[BUFLEN + 1];
	memcpy(buffer, (char*)msg.payload, msg.payloadLen);
	buffer[msg.payloadLen] = '\0';
	
	Serial.println("received: "); Serial.println(buffer);
}

/* ###################################################################################################################### old code:*/
//
//Adafruit_MQTT_Client MqttUtil::getClient() {
//    return mqtt;
//}
//void MqttUtil::processPackets(int timeout) {
//   
//}
//
//#define TEMP_TOPIC(UNIT) "UweSolar" #UNIT "/bme/temp"
//
////#define CREATE_TEMP_SUBSCRIPTION(UNIT) Adafruit_MQTT_Subscribe temp##UNIT = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), TEMP_TOPIC(UNIT), MY_QOS);
//#define CREATE_TEMP_SUBSCRIPTION(UNIT) subscribeTemp##UNIT(Adafruit_MQTT_Subscribe(&mqtt, TEMP_TOPIC(UNIT), MY_QOS))
////#define CALLBACK_REF(NAME)  MqttUtil:: ## CALLBACK_REF_DECL(NAME)
//    //#define VALUE_OUT(NAME) Serial.println(String(#NAME " = ") + String(x))
//#define VALUE_OUT(NAME)
//// define callback function
//#define UPDATE_LAST_MSG timUtil.setTimeOfLastMsg();
//#define ADD_ON_FUNCTION(NAME) unitStorage.gTime##NAME = timUtil.getTime();
//#define CALLBACK(NAME, ADD_ON) void CALLBACK_REF_DECL(NAME) {UPDATE_LAST_MSG VALUE_OUT(NAME) unitStorage.g ## NAME = x;ADD_ON}
//
//MqttUtil::MqttUtil(WiFiClient wclient, UnitStorageClass unitStorage, TimUtilBase timUtil)
//    : mqtt(Adafruit_MQTT_Client(&wclient, AIO_SERVER, AIO_SERVERPORT, "","")), 
//    subscribeTemp1(Adafruit_MQTT_Subscribe(&mqtt, "UweSolar1/bme/temp", MY_QOS))
//{    
//    this->unitStorage = unitStorage;
//    this->timUtil = timUtil;
//
//    // Setup a consumer for subscribing to changes on the tempX topic, e.g. Temp1
//
//        //    CREATE_TEMP_SUBSCRIPTION(2)
//        //    CREATE_TEMP_SUBSCRIPTION(3)
//
//        //Adafruit_MQTT_Subscribe press2 = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "UweSolar2/bme/press", MY_QOS);
//        //Adafruit_MQTT_Subscribe hum2 = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "UweSolar2/bme/hum", MY_QOS);
//        //Adafruit_MQTT_Subscribe rainProb = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "rainProb", MY_QOS);
//        //Adafruit_MQTT_Subscribe sunRise = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "sunrise", MY_QOS);
//        //Adafruit_MQTT_Subscribe sunSet = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "sunset", MY_QOS);
//        //Adafruit_MQTT_Subscribe moonRise = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "moonrise", MY_QOS);
//        //Adafruit_MQTT_Subscribe moonSet = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "moonset", MY_QOS);
//        //Adafruit_MQTT_Subscribe moonPhase = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "moonphase", MY_QOS);
//        //Adafruit_MQTT_Subscribe azimuth = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "azimut", MY_QOS);
//        //Adafruit_MQTT_Subscribe elevation = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "elevation", MY_QOS);
//        //Adafruit_MQTT_Subscribe astrotimestamp = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "astrotimestamp", MY_QOS);
//        //Adafruit_MQTT_Subscribe sunculm = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "sunculm", MY_QOS);
//        //Adafruit_MQTT_Subscribe astroevent = Adafruit_MQTT_Subscribe(&mqttUtil.getClient(), "astroevent", MY_QOS);
//
//        mqttSubscribe();
//
//}
//void MqttUtil::mqttSubscribe() {
//    //subscribeTemp1.setCallback(CALLBACK_NAME_ONLY(Temp1));
//    subscribeTemp1.setCallback(callbackTemp1);
//    //temp2.setCallback(CALLBACK_REF(Temp2));
//    //temp3.setCallback(CALLBACK_REF(Temp3));
//    //press2.setCallback(CALLBACK_REF(Press2));
//    //hum2.setCallback(CALLBACK_REF(Hum2));
//    //rainProb.setCallback(CALLBACK_REF(RainProb));
//    //sunRise.setCallback(CALLBACK_REF(SunRise));
//    //sunSet.setCallback(CALLBACK_REF(SunSet));
//    //moonRise.setCallback(CALLBACK_REF(MoonRise));
//    //moonSet.setCallback(CALLBACK_REF(MoonSet));
//    //moonPhase.setCallback(CALLBACK_REF(MoonPhase));
//    //azimuth.setCallback(CALLBACK_REF(Azimut));
//    //elevation.setCallback(CALLBACK_REF(Elevation));
//    //astrotimestamp.setCallback(CALLBACK_REF(AstroTime));
//    //sunculm.setCallback(CALLBACK_REF(SunCulm));
//    //astroevent.setCallback(CALLBACK_REF(AstroEvent));
//
//    // Setup MQTT subscriptions
//    mqtt.subscribe(&subscribeTemp1);
//    //mqtt.subscribe(&temp2);
//    //mqtt.subscribe(&temp3);
//    //mqtt.subscribe(&press2);
//    //mqtt.subscribe(&hum2);
//    //mqtt.subscribe(&rainProb);
//    //mqtt.subscribe(&sunRise);
//    //mqtt.subscribe(&sunSet);
//    //mqtt.subscribe(&moonRise);
//    //mqtt.subscribe(&moonSet);
//    //mqtt.subscribe(&moonPhase);
//    //mqtt.subscribe(&azimuth);
//    //mqtt.subscribe(&elevation);
//    //mqtt.subscribe(&astrotimestamp);
//    //mqtt.subscribe(&sunculm);
//    //mqtt.subscribe(&astroevent);
//}
//void MqttUtil::unsubscribe() {
//    // Setup MQTT subscriptions
//    subscribeTemp1.removeCallback();
//    //temp2.removeCallback();
//    //temp3.removeCallback();
//    //press2.removeCallback();
//    //hum2.removeCallback();
//    //rainProb.removeCallback();
//    //sunRise.removeCallback();
//    //sunSet.removeCallback();
//    //moonRise.removeCallback();
//    //moonSet.removeCallback();
//    //moonPhase.removeCallback();
//    //azimuth.removeCallback();
//    //elevation.removeCallback();
//    //astrotimestamp.removeCallback();
//    //sunculm.removeCallback();
//    //astroevent.removeCallback();
//
//
//    mqtt.unsubscribe(&subscribeTemp1);
//    //mqtt.unsubscribe(&temp2);
//    //mqtt.unsubscribe(&temp3);
//    //mqtt.unsubscribe(&press2);
//    //mqtt.unsubscribe(&hum2);
//    //mqtt.unsubscribe(&rainProb);
//    //mqtt.unsubscribe(&sunRise);
//    //mqtt.unsubscribe(&sunSet);
//    //mqtt.unsubscribe(&moonRise);
//    //mqtt.unsubscribe(&moonSet);
//    //mqtt.unsubscribe(&moonPhase);
//    //mqtt.unsubscribe(&azimuth);
//    //mqtt.unsubscribe(&elevation);
//    //mqtt.unsubscribe(&astrotimestamp);
//    //mqtt.unsubscribe(&sunculm);
//    //mqtt.unsubscribe(&astroevent);
//}
//
//void MqttUtil::mqttConnect() {
//    mqttConnect(NULL);
//}
//void MqttUtil::mqttConnect(void (*displayMsg)(String msg)) {
//    // Stop if already connected.
//    if (mqtt.connected()) {
//        return;
//    }
//    int8_t ret;
//    String statusMsg = "Connecting to MQTT... ";
//    if (displayMsg != NULL) {
//      /*displayUtil.*/displayMsg(statusMsg);
//    }
//
//    uint8_t retries = 3;
//    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
//        Serial.println(mqtt.connectErrorString(ret));
//        statusMsg = String("Connect error, reconnect yielded: ") + String(mqtt.connectErrorString(ret));
//        Serial.println(statusMsg);
//      String statusMsg = "Connecting to MQTT... ";
//        /*displayUtil.*/displayMsg(statusMsg);
//        unsubscribe();
//        mqtt.disconnect();
//        delay(10000);  // wait 10 seconds
//        retries--;
//        if (retries == 0) { // give up
//            statusMsg = "MQTT connect FAILED -> restart ESP";
//            Serial.println(statusMsg);
//            /*displayUtil.*/displayMsg(statusMsg);
//            unsubscribe();
////            timUtil.setFirstMessageReceived(false); // not needed since we restart anyway
//            // restart
//            delay(5000);  // wait 5 seconds to allow reading display
//            ESP.restart();
//        }
//    }
//    statusMsg = (unitStorage.localIP + String(": MQTT Connected!")).c_str();
//    mqttSubscribe();
//    Serial.println(statusMsg);
//    if (displayMsg != NULL) {
//        /*displayUtil.*/displayMsg(statusMsg);
//    }
//}
//
//CALLBACK(Temp1, ADD_ON_FUNCTION(Temp1))
////CALLBACK(Temp2, ADD_ON_FUNCTION(Temp2))
////CALLBACK(Temp3, ADD_ON_FUNCTION(Temp3))
////CALLBACK(Press2, {})
////CALLBACK(Hum2, {})
////CALLBACK(RainProb, {})
////CALLBACK(SunRise, {})
////CALLBACK(SunSet, {})
////CALLBACK(MoonRise, {})
////CALLBACK(MoonSet, {})
////CALLBACK(MoonPhase, {})
////CALLBACK(Azimut, {})
////CALLBACK(Elevation, {})
////CALLBACK(AstroTime, {})
////CALLBACK(SunCulm, {})
////CALLBACK(AstroEvent, { unitStorage.gLastEventTime = timUtil.getTime(); })
