// prevent definition of display object inside "GxEPD2_display_selection_new_style.h"
#undef NEED_DISPLAY_DEF
#include "DisplayUtil.h"
#include "UnitStorage.h"
#include <Adafruit_MQTT_FONA.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_MQTT.h>
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
//#include <JsonParser.h>
//#include <ArduinoJson.h>

#include "TimUtil.h"

#include "cred.h" // do not maintain this file in source control



// MQTT const
constexpr auto AIO_SERVER = "192.168.178.23";
constexpr auto AIO_SERVERPORT = 1883;
constexpr auto MY_QOS = MQTT_QOS_0;
//constexpr auto AIO_USERNAME    ""
//constexpr auto AIO_KEY         ""
// define variable name of the callback function parameterized by 
#define CALLBACK_REF(NAME)  callback ## NAME
//#define VALUE_OUT(NAME) Serial.println(String(#NAME " = ") + String(x))
#define VALUE_OUT(NAME)
// define callback function
#define ADD_ON_FUNCTION(NAME) unitStorage.gTime##NAME = timUtil.getTime();
#define CALLBACK(NAME, ADD_ON) void CALLBACK_REF(NAME) (char* x, uint16_t dummy) {VALUE_OUT(NAME);unitStorage.g ## NAME = x;ADD_ON}

const char* ssid = SSID;
const char* wlanPwd = WLAN_KEY;

WiFiClient wclient;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&wclient, AIO_SERVER, AIO_SERVERPORT,"","");

/****************************** Feeds ***************************************/

// Setup a feed called 'tempX' for subscribing to changes on the tempX
#define TEMP_TOPIC(UNIT) "UweSolar" #UNIT "/bme/temp"
#define CREATE_TEMP_SUBSCRIPTION( UNIT) Adafruit_MQTT_Subscribe temp##UNIT = Adafruit_MQTT_Subscribe(&mqtt, TEMP_TOPIC(UNIT), MY_QOS);

CREATE_TEMP_SUBSCRIPTION(1)
CREATE_TEMP_SUBSCRIPTION(2)
CREATE_TEMP_SUBSCRIPTION(3)

Adafruit_MQTT_Subscribe press2 = Adafruit_MQTT_Subscribe(&mqtt, "UweSolar2/bme/press", MY_QOS);
Adafruit_MQTT_Subscribe hum2 = Adafruit_MQTT_Subscribe(&mqtt, "UweSolar2/bme/hum", MY_QOS);
Adafruit_MQTT_Subscribe rainProb = Adafruit_MQTT_Subscribe(&mqtt, "rainProb", MY_QOS);
Adafruit_MQTT_Subscribe sunRise = Adafruit_MQTT_Subscribe(&mqtt, "sunrise", MY_QOS);
Adafruit_MQTT_Subscribe sunSet = Adafruit_MQTT_Subscribe(&mqtt, "sunset", MY_QOS);
Adafruit_MQTT_Subscribe moonRise = Adafruit_MQTT_Subscribe(&mqtt, "moonrise", MY_QOS);
Adafruit_MQTT_Subscribe moonSet = Adafruit_MQTT_Subscribe(&mqtt, "moonset", MY_QOS);
Adafruit_MQTT_Subscribe moonPhase = Adafruit_MQTT_Subscribe(&mqtt, "moonphase", MY_QOS);
Adafruit_MQTT_Subscribe azimuth = Adafruit_MQTT_Subscribe(&mqtt, "azimut", MY_QOS);
Adafruit_MQTT_Subscribe elevation = Adafruit_MQTT_Subscribe(&mqtt, "elevation", MY_QOS);
Adafruit_MQTT_Subscribe astrotimestamp = Adafruit_MQTT_Subscribe(&mqtt, "astrotimestamp", MY_QOS);
Adafruit_MQTT_Subscribe sunculm = Adafruit_MQTT_Subscribe(&mqtt, "sunculm", MY_QOS);
Adafruit_MQTT_Subscribe astroevent = Adafruit_MQTT_Subscribe(&mqtt, "astroevent", MY_QOS);


UnitStorageClass unitStorage;
TimUtilClass timUtil;
DisplayUtil displayUtil;

void setup(void) {
  Serial.begin(115200);

  Serial.println(F("wifi BEGIN"));
  initialise_wifi();
  Serial.println(F("init wifi END "));
  
  temp1.setCallback(CALLBACK_REF(Temp1));
  temp2.setCallback(CALLBACK_REF(Temp2));
  temp3.setCallback(CALLBACK_REF(Temp3));
  press2.setCallback(CALLBACK_REF(Press2));
  hum2.setCallback(CALLBACK_REF(Hum2));
  rainProb.setCallback(CALLBACK_REF(RainProb));
  sunRise.setCallback(CALLBACK_REF(SunRise));
  sunSet.setCallback(CALLBACK_REF(SunSet));
  moonRise.setCallback(CALLBACK_REF(MoonRise));
  moonSet.setCallback(CALLBACK_REF(MoonSet));
  moonPhase.setCallback(CALLBACK_REF(MoonPhase));
  azimuth.setCallback(CALLBACK_REF(Azimut));
  elevation.setCallback(CALLBACK_REF(Elevation));
  astrotimestamp.setCallback(CALLBACK_REF(AstroTime));
  sunculm.setCallback(CALLBACK_REF(SunCulm));
  astroevent.setCallback(astroeventcallback);


  // Setup MQTT subscriptions
  mqtt.subscribe(&temp1);
  mqtt.subscribe(&temp2);
  mqtt.subscribe(&temp3);
  mqtt.subscribe(&press2);
  mqtt.subscribe(&hum2);
  mqtt.subscribe(&rainProb);
  mqtt.subscribe(&sunRise);
  mqtt.subscribe(&sunSet);
  mqtt.subscribe(&moonRise);
  mqtt.subscribe(&moonSet);
  mqtt.subscribe(&moonPhase);
  mqtt.subscribe(&azimuth);
  mqtt.subscribe(&elevation);
  mqtt.subscribe(&astrotimestamp);
  mqtt.subscribe(&sunculm);
  mqtt.subscribe(&astroevent);


//  timUtil.setTimeClient(timeClient);
  timUtil.init();
  displayUtil.init();

 }

void loop() {
    // update NTP 
    timUtil.update();
// Ensure the connection to the MQTT server is alive (this will make the first
// connection and automatically reconnect when disconnected).  See the MQTT_connect
// function definition further below.
    MQTT_connect();

    // this is our 'wait for incoming subscription packets and callback em' busy subloop
 // try to spend your time here:
 //   Serial.println(F("BEFORE processPackets"));
    mqtt.processPackets(10000);
 //   Serial.println(F("AFTER  processPackets"));

    displayUtil.displayData(timUtil, unitStorage);
    delay(20000);
}




// NETWORK STUFF

void initialise_wifi() {
    Serial.println(F("init Wifi"));
    WiFi.hostname(F("DisplayUnit"));
    // connect to WLAN
    WiFi.mode(WIFI_STA);
    uint8_t retries = 5;
    WiFi.begin(ssid, wlanPwd);
    while (WiFi.status() != WL_CONNECTED) {
        retries--;
        if (retries == 0) {
            Serial.println("Give up connecting to WLAN " + String(ssid));
            ESP.restart();
        }
        delay(5000);
        Serial.print(".");
    }
    Serial.print("Wifi Connected to ");
    Serial.println(ssid);
    Serial.println("IP Address: ");
    unitStorage.localIP = WiFi.localIP().toString();
    Serial.println(unitStorage.localIP);

}

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
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
    int8_t ret;

    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }

    Serial.print("Connecting to MQTT... ");

    uint8_t retries = 3;
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
        Serial.println(mqtt.connectErrorString(ret));
        Serial.println("Retrying MQTT conn in 10 seconds...");
        mqtt.disconnect();
        delay(10000);  // wait 10 seconds
        retries--;
        if (retries == 0) {
            Serial.println("Last attempt MQTT connect FAILED -> enter FOREVER loop");
            // restart
            ESP.restart();
        }
    }
    Serial.println("MQTT Connected!");
}

CALLBACK(Temp1, ADD_ON_FUNCTION(Temp1))
CALLBACK(Temp2, ADD_ON_FUNCTION(Temp2))
CALLBACK(Temp3, ADD_ON_FUNCTION(Temp3))
CALLBACK(Press2, {})
CALLBACK(Hum2, {})
CALLBACK(RainProb, {})
CALLBACK(SunRise, {})
CALLBACK(SunSet, {})
CALLBACK(MoonRise, {})
CALLBACK(MoonSet, {})
CALLBACK(MoonPhase, {})
CALLBACK(Azimut, {})
CALLBACK(Elevation, {})
CALLBACK(AstroTime, {})
CALLBACK(SunCulm, {})

void astroeventcallback(char* x, uint16_t dummy) {
    unitStorage.gAstroEvent = x;
    unitStorage.gLastEventTime = timUtil.getTime();
}
