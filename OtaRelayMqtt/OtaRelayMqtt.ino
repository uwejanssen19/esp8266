/*
Try to get that nice thing running inside visual studio
Project: $projectname$
*/
#include <Adafruit_MQTT_FONA.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_MQTT.h>

#include <WiFiUdp.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecure.h>
#include <WiFiServer.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include <CertStoreBearSSL.h>
#include <BearSSLHelpers.h>
#include <Arduino.h>
#include <ArduinoOTA.h>
#include "TimUtil.h"
//#include <TelnetStream.h>



#define OFF (boolean)false
#define ON (boolean)true
#define RELAIS_PIN D5
WiFiClient wclient;
const char* ssid = PRIVATE_SSID;
const char* wlanPwd = PRIVATE_WLAN_KEY;
// MQTT const
constexpr auto AIO_SERVER = "garden-control.fritz.box";
constexpr auto AIO_SERVERPORT = 1883;
constexpr auto MY_QOS = MQTT_QOS_0;
//constexpr auto AIO_USERNAME    ""
//constexpr auto AIO_KEY         ""
// define variable name of the callback function parameterized by 
#define CALLBACK_REF(NAME)  callback ## NAME
#define VALUE_OUT(NAME) Serial.println(String(#NAME " = ") + String(x))
//#define VALUE_OUT(NAME)
// define callback function
#define UPDATE_LAST_MSG(NAME) timUtil.setTimeOfLastMsg();
#define ADD_ON_FUNCTION(NAME) unitStorage.gTime##NAME = timUtil.getTime();UPDATE_LAST_MSG(NAME)
#define CALLBACK(NAME, ADD_ON) void CALLBACK_REF(NAME) (char* x, uint16_t dummy) {VALUE_OUT(NAME);g ## NAME = x;ADD_ON}

const unsigned int mqttPort = 1883;
boolean relayState = OFF;
void setupOTA();
void relaisControl(boolean value);
boolean toggleBoolean();
boolean gIrrOnOff = OFF;
String analogResult;

//mqtt
String unitName = "UweSolar2";
String tTemp = unitName + "/bme/temp";
String status = unitName + "/status";
String relayState = unitName + "/relayState";


// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&wclient, AIO_SERVER, AIO_SERVERPORT, "", "");

/****************************** Feeds ***************************************/

//#define TEMP_TOPIC(UNIT) "UweSolar" #UNIT "/bme/temp"
//#define CREATE_TEMP_SUBSCRIPTION( UNIT) Adafruit_MQTT_Subscribe temp##UNIT = Adafruit_MQTT_Subscribe(&mqtt, TEMP_TOPIC(UNIT), MY_QOS);


Adafruit_MQTT_Subscribe irrOnOff = Adafruit_MQTT_Subscribe(&mqtt,/* topic = */ "IrrOnOff", MY_QOS);

TimUtilBase timUtil;

void setup(void) {
    setupOTA();
    inithw();
    Serial.begin(115200);

    // connect to WLAN
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, wlanPwd);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    print_wifi_status();

    irrOnOff.setCallback(CALLBACK_REF(IrrOnOff));
    mqtt.subscribe(&irrOnOff);

}

void loop(void) {
    ArduinoOTA.handle();

    timUtil.update();
    // now connect to MQTT server 
    MQTT_connect();
    String temperature = getTemp();
    
    // this is our 'wait for incoming subscription packets and callback em' busy subloop
 // try to spend your time here:
 //   Serial.println(F("BEFORE processPackets"));
    mqtt.processPackets(1000);

    if (relayState == OFF) {
        relaisControl(ON);
        relayState = ON;
        // Pump ON
//        mqtt.publish(topic, "relay ON");
    }
    else {
        relaisControl(OFF);
        relayState = OFF;
  //      mqtt.publish(topic, "relay OFF");

        // Pump OFF
    }
    ArduinoOTA.handle();
    delay(1000);
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

void relaisControl(boolean value = OFF) {
    if (value) {
        digitalWrite(RELAIS_PIN, LOW);
        digitalWrite(BUILTIN_LED, LOW);
    }
    else {
        digitalWrite(RELAIS_PIN, HIGH);
        digitalWrite(BUILTIN_LED, HIGH);
    }
}

void inithw(void) {
    pinMode(BUILTIN_LED, OUTPUT);
    pinMode(RELAIS_PIN, OUTPUT);
    relaisControl(OFF);
}


boolean toggleBoolean() {
    relayState = (relayState == OFF) ? ON : OFF;
    Serial.println("State = " + relayState);
    return relayState;
}
const char* relayStateToString() {
    return relayState == OFF ? "OFF" : "ON";
}
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
    int8_t ret;
    String statusMsg;

    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }

    Serial.print("Connecting to MQTT... ");


    uint8_t retries = 3;
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
        Serial.println(mqtt.connectErrorString(ret));
        statusMsg = "Retrying MQTT conn in 10 seconds...";
        Serial.println(statusMsg);
        //unsubscribe();
        mqtt.disconnect();
        ArduinoOTA.handle();
        delay(1000);  // wait 10 seconds
        retries--;
        if (retries == 0) {
            statusMsg = "MQTT connect FAILED -> restart ESP";
            Serial.println(statusMsg);
            //unsubscribe();
            // restart
            ESP.restart();
        }
    }
    statusMsg = "MQTT Connected!";
    Serial.println(statusMsg);
}
// invoke macro CALLBACK(NAME,ADDON_CODE)
//CALLBACK(Hum2, { mqtt.publish(topic,(String("IP = ") + WiFi.localIP().toString() + String(" , hum2 = ") + String(gHum2)).c_str()); })
CALLBACK(IrrOnOff, {})
void print_wifi_status() {
    //   SSID des WiFi Netzwerkes ausgeben:
    Serial.print("SSID: ");
    Serial.println(ssid);

    // WiFi IP Adresse des ESP32 ausgeben:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // WiFi Signalstaerke ausgeben:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void publishMQTT(TimUtilBase) {
    /* we have to publish:
    1. time
    2. status ( = IP address, uptime, rssi, battery level )
    3. temperature
    4. Battery level 
    5. rssi
    6. IP address
    */

}
String getTemp() {

}
String readVoltage() {
    float outputValue = 0;
    unsigned int analogValue = 0;
    analogValue = analogRead(A0);
    Serial.println(analogValue);
    outputValue = map(analogValue, 0, 1023, 0, 255);
#ifdef VM_DEBUG
    Serial.println(outputValue);
#endif
    analogResult = String(outputValue,2); // 2 decimals
    analogResult =+ "V";
    return analogResult;
}