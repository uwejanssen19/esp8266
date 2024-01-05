// prevent definition of display object inside "GxEPD2_display_selection_new_style.h"
#undef NEED_DISPLAY_DEF
#define WEATHER_ASTRO
#include "DisplayUtil.h"
#include "UnitStorage.h"
//#include <WiFiServerSecureBearSSL.h>
//#include <WiFiServerSecureAxTLS.h>
//#include <WiFiServerSecure.h>
//#include <WiFiServer.h>
//#include <WiFiClientSecureBearSSL.h>
//#include <WiFiClientSecureAxTLS.h>
//#include <WiFiClientSecure.h>
#define _WIFI_CLIENT_H
//#include <WiFiClient.h>
//#include <ESP8266WiFiType.h>
//#include <ESP8266WiFiSTA.h>
//#include <ESP8266WiFiScan.h>
//#include <ESP8266WiFiMulti.h>
//#include <ESP8266WiFiGratuitous.h>
//#include <ESP8266WiFiGeneric.h>
//#include <ESP8266WiFiAP.h>
//#include <ESP8266WiFi.h>
//#include <CertStoreBearSSL.h>
//#include <BearSSLHelpers.h>
//#include <JsonParser.h>
//#include <ArduinoJson.h>

#include "TimUtilCheck.h"
//#include "MqttUtil.h"


//// MQTT const
//constexpr auto AIO_SERVER = "garden-control.fritz.box";
//constexpr auto AIO_SERVERPORT = 1883;
//constexpr auto MY_QOS = MQTT_QOS_0;
//constexpr auto AIO_USERNAME    ""
//constexpr auto AIO_KEY         ""
// define variable name of the callback function parameterized by 
//#define CALLBACK_REF(NAME)  callback ## NAME
////#define VALUE_OUT(NAME) Serial.println(String(#NAME " = ") + String(x))
//#define VALUE_OUT(NAME)
//// define callback function
//#define UPDATE_LAST_MSG timUtil.setTimeOfLastMsg();
//#define ADD_ON_FUNCTION(NAME) unitStorage.gTime##NAME = timUtil.getTime();
//#define CALLBACK(NAME, ADD_ON) void CALLBACK_REF(NAME) (char* x, uint16_t dummy) {UPDATE_LAST_MSG VALUE_OUT(NAME) unitStorage.g ## NAME = x;ADD_ON}


const char* ssid = PRIVATE_SSID; // defined in proj properties
const char* wlanPwd = PRIVATE_WLAN_KEY; // defined in proj properties

//WiFiClient wclient;


/****************************** Feeds ***************************************/


// all the topic values are stored here
UnitStorageClass unitStorage;
// gets NTP time and date and stores it
TimUtilCheck timUtil;
// manages e-paper display
DisplayUtil displayUtil;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
//Adafruit_MQTT_Client mqtt(&wclient, AIO_SERVER, AIO_SERVERPORT,"","");
//MqttUtil mqttUtil(wclient, unitStorage, timUtil);

void setup(void) {
  Serial.begin(115200);

  //Serial.println(F("wifi BEGIN"));
  //initialise_wifi();
  //Serial.println(F("init wifi END "));

  timUtil.init();
  displayUtil.init();
  //mqttUtil.mqttSubscribe((NULL),NULL);

}


void loop() {
    // update NTP 
    timUtil.update();
    displayUtil.init();
    // Ensure the connection to the MQTT server is alive (this will make the first
    // connection and automatically reconnect when disconnected).  See the MQTT_connect
    // function definition further below.
    String msg;
    /* todo uncomment*///mqttUtil.mqttConnect(displayUtil.displayMsg(msg));
//    mqttUtil.mqttConnect();

    // this is our 'wait for incoming subscription packets and callback em' busy subloop
    // try to spend your time here:
    //   Serial.println(F("BEFORE processPackets"));
/* todo uncomment*/    //mqttUtil.yield(10000);
    //   Serial.println(F("AFTER  processPackets"));
    displayUtil.displayData(timUtil, unitStorage);
    // reboot if there are no messages more than 2 hours ago 
    boolean tooLate = timUtil.lastMsgTooLate(msg);
    displayUtil.init();
    displayUtil.displayStatusMsg(msg);
    Serial.print("msg = ");
    Serial.println(msg);
    if  (tooLate) {

        delay(10000); // msg readable 10 secs
          // remove MQTT subscriptions
        /* todo uncomment*///mqttUtil.unsubscribe();
        ESP.restart();
    }
    delay(20000);
}



// NETWORK STUFF

//void initialise_wifi() {
//    //Serial.println(F("init Wifi"));
//    WiFi.hostname(F("DisplayUnit"));
//    // connect to WLAN
//    WiFi.mode(WIFI_STA);
//    uint8_t retries = 5;
//    WiFi.begin(ssid, wlanPwd);
//    while (WiFi.status() != WL_CONNECTED) {
//        retries--;
//        if (retries == 0) {
//            Serial.println("Give up connecting to WLAN " + String(ssid));
//            ESP.restart();
//        }
//        delay(5000);
//        Serial.print(".");
//    }
//    unitStorage.localIP = WiFi.localIP().toString();
//    print_wifi_status();
//}

//void print_wifi_status() {
////   SSID des WiFi Netzwerkes ausgeben:
//  Serial.print("SSID: ");
//  Serial.println(ssid);
//
//  // WiFi IP Adresse des ESP32 ausgeben:
//  IPAddress ip = WiFi.localIP();
//  Serial.print("IP Address: ");
//  Serial.println(ip);
//
//  // WiFi Signalstaerke ausgeben:
//  long rssi = WiFi.RSSI();
//  Serial.print("signal strength (RSSI):");
//  Serial.print(rssi);
//  Serial.println(" dBm");
//}
//// Function to connect and reconnect as necessary to the MQTT server.
//// Should be called in the loop function and it will take care if connecting.
////void x(void(*function)())
//
//void MQTT_connect(void (*displayMsg)(String msg)) {
//    // Stop if already connected.
//    if (mqtt.connected()) {
//        return;
//    }
//    int8_t ret;
//    String statusMsg = "Connecting to MQTT... ";
//    /*displayUtil.*/displayMsg(statusMsg);
//
//    uint8_t retries = 3;
//    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
//        Serial.println(mqtt.connectErrorString(ret));
//        statusMsg = String("Connect error, reconnect yielded: ") + String(mqtt.connectErrorString(ret));
//        Serial.println(statusMsg);
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
//            timUtil.setFirstMessageReceived(false);
//            // restart
//            delay(5000);  // wait 5 seconds to allow reading display
//            ESP.restart();
//        }
//    }
//    statusMsg = (unitStorage.localIP + String(": MQTT Connected!")).c_str();
//    mqttSubscribe();
//    Serial.println(statusMsg);
//    /*displayUtil.*/displayMsg(statusMsg);
//}

