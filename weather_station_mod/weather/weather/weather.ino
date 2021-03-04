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
#include <gfxfont.h>
#include <Adafruit_GFX.h>
//#include <JsonParser.h>
//#include <ArduinoJson.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
// select the display class and display driver class in the following file (new style):
#include "GxEPD2_display_selection_new_style.h"

#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
//#include <Fonts/FreeMonoBold24pt7b.h>

#include "TimUtil.h"

#include "cred.h" // do not maintain this file in source control


#define AIO_SERVER      "192.168.178.23"
#define AIO_SERVERPORT  1883
//#define AIO_USERNAME    ""
//#define AIO_KEY         ""

//Adafruit_BME280 bme;
const char* ssid = SSID;
const char* wlanPwd = WLAN_KEY;

// topics to listen to 
//const char* temp_1 = "UweSolar1/bme/temp";
//const char* temp_2 = "UweSolar2/bme/temp";
//const char* press_2 = "UweSolar2/bme/press";
//const char* hum_2 = "UweSolar2/bme/hum";
//const char* temp_3 = "UweSolar3/bme/temp";

String localIP = ""; 
char* gTemp2 = "-1";
char* gPress2  = "-1";
char* gHum2 = "-1";
char* gRainProb = "-1";
char* gMoonPhase = "-1";
char* gMoonRise = "-1";
char* gMoonSet = "-1";
char* gSunRise = "-1";
char* gSunSet = "-1";
char* gAzimut = "-1";
char* gElevation = "-1";
//#define PROGMEM

WiFiClient wclient;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&wclient, AIO_SERVER, AIO_SERVERPORT,"","");

/****************************** Feeds ***************************************/

//// Setup a feed called 'time' for subscribing to current time
//Adafruit_MQTT_Subscribe time2 = Adafruit_MQTT_Subscribe(&mqtt, "UweSolar2/time/value");

// Setup a feed called 'slider' for subscribing to changes on the slider
//Adafruit_MQTT_Subscribe slider = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/slider", MQTT_QOS_1);
Adafruit_MQTT_Subscribe temp2 = Adafruit_MQTT_Subscribe(&mqtt, "UweSolar2/bme/temp");
Adafruit_MQTT_Subscribe press2 = Adafruit_MQTT_Subscribe(&mqtt, "UweSolar2/bme/press");
Adafruit_MQTT_Subscribe hum2 = Adafruit_MQTT_Subscribe(&mqtt, "UweSolar2/bme/hum");
Adafruit_MQTT_Subscribe rainProb = Adafruit_MQTT_Subscribe(&mqtt, "rainProb");
Adafruit_MQTT_Subscribe sunRise = Adafruit_MQTT_Subscribe(&mqtt, "sunrise");
Adafruit_MQTT_Subscribe sunSet = Adafruit_MQTT_Subscribe(&mqtt, "sunset");
Adafruit_MQTT_Subscribe moonRise = Adafruit_MQTT_Subscribe(&mqtt, "moonrise");
Adafruit_MQTT_Subscribe moonSet = Adafruit_MQTT_Subscribe(&mqtt, "moonset");
Adafruit_MQTT_Subscribe moonPhase = Adafruit_MQTT_Subscribe(&mqtt, "moonphase");
Adafruit_MQTT_Subscribe azimuth = Adafruit_MQTT_Subscribe(&mqtt, "azimut");
Adafruit_MQTT_Subscribe elevation = Adafruit_MQTT_Subscribe(&mqtt, "elevation");

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "fritz.box", 3600, 60000);

TimUtilClass timUtil;

// Define each of the *icons for display

const unsigned char moon_0_8[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xff,0xf8,0x3f,0xff,0xfc,0x3f,0xff,0xfc,0x7f,0xff,0xfe
,0x7f,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xff,0xfe
,0x7f,0xff,0xfe,0x3f,0xff,0xfc,0x3f,0xff,0xfc,0x1f,0xff,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_1[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xe1,0xf8,0x3f,0xf0,0x7c,0x3f,0xfc,0x3c,0x7f,0xfc,0x1e
,0x7f,0xfe,0x1e,0xff,0xfe,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xfe,0x0f,0x7f,0xfe,0x1e
,0x7f,0xfc,0x1e,0x3f,0xfc,0x3c,0x3f,0xf0,0x7c,0x1f,0xe1,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_2[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xe1,0xf8,0x3f,0xf0,0x7c,0x3f,0xfc,0x3c,0x7f,0xfc,0x1e
,0x7f,0xfe,0x1e,0xff,0xfe,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xff,0x0f,0xff,0xfe,0x0f,0x7f,0xfe,0x1e
,0x7f,0xfc,0x1e,0x3f,0xfc,0x3c,0x3f,0xf0,0x7c,0x1f,0xe1,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_3[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xf1,0xf8,0x3f,0xf0,0x7c,0x3f,0xf0,0x3c,0x7f,0xf0,0x1e
,0x7f,0xf0,0x1e,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0x7f,0xf0,0x1e
,0x7f,0xf0,0x1e,0x3f,0xf0,0x3c,0x3f,0xf0,0x7c,0x1f,0xf1,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_4[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0xc1,0xf8,0x3f,0xc0,0x7c,0x3f,0x80,0x3c,0x7f,0x00,0x1e
,0x7f,0x00,0x1e,0xff,0x00,0x0f,0xff,0x00,0x0f,0xff,0x00,0x0f,0xff,0x00,0x0f,0xff,0x00,0x0f,0xff,0x00,0x0f,0x7f,0x00,0x1e
,0x7f,0x00,0x1e,0x3f,0x80,0x3c,0x3f,0xc0,0x7c,0x1f,0xc1,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_5[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0x81,0xf8,0x3e,0x00,0x7c,0x3c,0x00,0x3c,0x78,0x00,0x1e
,0x78,0x00,0x1e,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0xf0,0x00,0x0f,0x78,0x00,0x1e
,0x78,0x00,0x1e,0x3c,0x00,0x3c,0x3e,0x00,0x7c,0x1f,0x81,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_6[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0x8f,0xf8,0x3e,0x0f,0xfc,0x3c,0x0f,0xfc,0x78,0x0f,0xfe
,0x78,0x0f,0xfe,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0xf0,0x0f,0xff,0x78,0x0f,0xfe
,0x78,0x0f,0xfe,0x3c,0x0f,0xfc,0x3e,0x0f,0xfc,0x1f,0x8f,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_7[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0x87,0xf8,0x3e,0x0f,0xfc,0x3c,0x3f,0xfc,0x78,0x3f,0xfe
,0x78,0x7f,0xfe,0xf0,0x7f,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0x7f,0xff,0x78,0x7f,0xfe
,0x78,0x3f,0xfe,0x3c,0x3f,0xfc,0x3e,0x0f,0xfc,0x1f,0x87,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char moon_8[] PROGMEM = {
0x00,0x3c,0x00,0x01,0xff,0x80,0x07,0xff,0xe0,0x0f,0xff,0xf0,0x1f,0x87,0xf8,0x3e,0x0f,0xfc,0x3c,0x3f,0xfc,0x78,0x3f,0xfe
,0x78,0x7f,0xfe,0xf0,0x7f,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0xff,0xff,0xf0,0x7f,0xff,0x78,0x7f,0xfe
,0x78,0x3f,0xfe,0x3c,0x3f,0xfc,0x3e,0x0f,0xfc,0x1f,0x87,0xf8,0x0f,0xff,0xf0,0x07,0xff,0xe0,0x01,0xff,0x80,0x00,0x3c,0x00
};

const unsigned char pressure[] PROGMEM = {
0x00, 0x00, 0x84, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x84, 0x44, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc4, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x4c, 0x88, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x88, 0x88, 0x80, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x40, 0x00, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0x11, 0x08, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x01, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xc0, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x30, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x01, 0x80, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x04, 0x18, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x01, 0x00
, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x18, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x80, 0x00, 0x01, 0x80
, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x80, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x61, 0x80, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x80, 0x00, 0x03, 0xc0
, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x03, 0x80
, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00
, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00
, 0x00, 0x08, 0x00, 0x00, 0x03, 0x80, 0x3f, 0x80, 0x00, 0x00, 0x10, 0x00, 0x00, 0x03, 0x80, 0x3f, 0xe0, 0x00
, 0x00, 0x20, 0x00, 0x00, 0x03, 0x80, 0x30, 0xe0, 0x00, 0x3c, 0xc0, 0x00, 0x00, 0x03, 0xfc, 0x30, 0xe7, 0xf0
, 0xff, 0x80, 0x00, 0x00, 0x03, 0xfc, 0x30, 0xe3, 0xf0, 0xe3, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x3b, 0xe0, 0x38
, 0x01, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x3f, 0xc1, 0xf8, 0x01, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x3f, 0x07, 0xf8
, 0x01, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x30, 0x0e, 0x38, 0x01, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x30, 0x0e, 0x38
, 0x03, 0x80, 0x00, 0x00, 0x03, 0x8e, 0x30, 0x07, 0xf8, 0x01, 0x00, 0x00, 0x00, 0x01, 0x8e, 0x30, 0x03, 0xf0
};

const unsigned char sunrise_sunset[] PROGMEM = {
0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00
,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x01,0xc0,0x01,0x80,0x03,0x80
,0x01,0xe0,0x00,0x00,0x07,0x80,0x01,0xf0,0x00,0x00,0x0f,0x80,0x00,0xf8,0x00,0x00,0x1f,0x00,0x00,0x78,0x00,0x00,0x1e,0x00
,0x00,0x38,0x03,0xc0,0x1c,0x00,0x00,0x00,0x1f,0xf8,0x00,0x00,0x00,0x00,0x7f,0xfe,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00
,0x00,0x01,0xf8,0x1f,0x80,0x00,0x00,0x03,0xe0,0x07,0xc0,0x00,0x00,0x03,0xc0,0x03,0xc0,0x00,0x00,0x07,0x80,0x01,0xe0,0x00
,0x00,0x07,0x80,0x01,0xe0,0x00,0x00,0x0f,0x00,0x00,0xf0,0x00,0x7e,0x0f,0x00,0x00,0xf0,0x7e,0xff,0x0f,0x00,0x00,0xf0,0xff
,0xff,0x0f,0x00,0x00,0xf0,0xff,0x7e,0x0f,0x00,0x00,0xf0,0x7e,0x00,0x07,0x00,0x00,0xe0,0x00,0x00,0x07,0x80,0x01,0xe0,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x07,0xff,0xff,0xe0,0x00,0x00,0x0f,0xff,0xff,0xf0,0x00,0x00,0x0f,0xff,0xff,0xf0,0x00,0x00,0x07,0xff,0xff,0xe0,0x00
};

const unsigned char clear_day[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x38, 0x00, 0x30, 0x00, 0x70, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0xf0, 0x00
, 0x00, 0x3e, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x03, 0xe0, 0x00
, 0x00, 0x0f, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0x00, 0x78, 0x03, 0x80, 0x00
, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00
, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x03, 0xf0, 0x00, 0x00
, 0x00, 0x00, 0x7c, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x78, 0x00, 0x00
, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00
, 0x00, 0x01, 0xe0, 0x00, 0x1e, 0x00, 0x00, 0x0f, 0xc1, 0xe0, 0x00, 0x1e, 0x0f, 0xc0
, 0x1f, 0xe1, 0xe0, 0x00, 0x1e, 0x1f, 0xe0, 0x1f, 0xe1, 0xe0, 0x00, 0x1e, 0x1f, 0xe0
, 0x0f, 0xc1, 0xe0, 0x00, 0x1e, 0x0f, 0xc0, 0x00, 0x01, 0xe0, 0x00, 0x1e, 0x00, 0x00
, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00
, 0x00, 0x00, 0x78, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0xf8, 0x00, 0x00
, 0x00, 0x00, 0x3f, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00
, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00
, 0x00, 0x07, 0x00, 0x78, 0x03, 0x80, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x03, 0xc0, 0x00
, 0x00, 0x1f, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0xf0, 0x00
, 0x00, 0x3c, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x38, 0x00, 0x30, 0x00, 0x70, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char temperature[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xcf, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x07, 0xb7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xb7, 0xc0, 0x00, 0x00
, 0x00, 0x00, 0x0f, 0x33, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x79, 0xe0, 0x00, 0x00
, 0x00, 0x00, 0x1e, 0xfd, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1e, 0xfd, 0xe0, 0x00, 0x00
, 0x00, 0x00, 0x1e, 0x79, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x33, 0xc0, 0x00, 0x00
, 0x00, 0x00, 0x0f, 0x87, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x80, 0x00, 0x00
, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char prob_rain[] PROGMEM = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xc0,0x00,0x00
,0x00,0x00,0x3f,0xff,0xf0,0x00,0x00,0x00,0x00,0x7f,0xff,0xfc,0x00,0x00,0x00,0x01,0xff,0xff,0xfe,0x00,0x00,0x00,0x03,0xff,0xff,0xff,0x00,0x00
,0x00,0x07,0xff,0xff,0xff,0x80,0x00,0x00,0x07,0xff,0xff,0xff,0xc0,0x00,0x00,0x0f,0xff,0xff,0xff,0xe0,0x00,0x00,0x0f,0xff,0xff,0xff,0xe0,0x00
,0x00,0x00,0x30,0x30,0x18,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00
,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00
,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x40,0x00,0x00,0x00,0x00,0x00,0x38,0xe0,0x00,0x00,0x00,0x00,0x00,0x38,0xe0,0x00,0x00
,0x00,0x00,0x00,0x1f,0xc0,0x00,0x00,0x00,0x00,0x00,0x1f,0x80,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const unsigned char barometer[] PROGMEM = {
0x00,0x1f,0xe0,0x00,0x00,0x7f,0xf8,0x00,0x01,0xff,0xfe,0x00,0x03,0xf0,0x3f,0x00,0x0f,0x80,0x07,0xc0,0x0f,0x00,0x03,0xc0,0x1e,0x00,0x01,0xe0,0x3c,0x00,0x00,0xf0
,0x38,0x00,0x3c,0x70,0x70,0x00,0x3c,0x38,0x70,0x00,0x7c,0x38,0xf0,0x00,0xfc,0x3c,0xe0,0x07,0xf0,0x1c,0xe0,0x0f,0xe0,0x1c,0xe0,0x0f,0xc0,0x1c,0xe0,0x0f,0xc0,0x1c
,0xe0,0x1f,0x80,0x1c,0xe0,0x3f,0x80,0x1c,0xf3,0xfc,0x00,0x3c,0x71,0xf8,0x00,0x38,0x70,0xf0,0x00,0x38,0x38,0x70,0x00,0x70,0x3c,0x30,0x00,0xf0,0x1e,0x10,0x01,0xe0
,0x0f,0x00,0x03,0xc0,0x0f,0x80,0x07,0xc0,0x03,0xf0,0x3f,0x00,0x01,0xff,0xfe,0x00,0x00,0x7f,0xf8,0x00,0x00,0x1f,0xe0,0x00
};

const unsigned char wind_speed[] PROGMEM = {
0x00,0x00,0x00,0x00,0x01,0xfc,0x00,0x00,0x03,0x3f,0xf0,0x00,0x85,0x3e,0x1f,0x80,0xd9,0x3e,0x1f,0x38,0xf1,0x3e,0x0f,0x0c,0xc1,0x3e,0x0f,0x0c,0xc1,0x3e,0x0f,0x0c
,0xf1,0x3e,0x0f,0x0c,0xd9,0x3e,0x0f,0x18,0xc5,0x3e,0x1f,0xc0,0xc3,0x3f,0xf0,0x00,0xc1,0xfe,0x00,0x00,0xc0,0x80,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00
,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00
,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

//const unsigned char rain[] PROGMEM = {
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x00
//,0x00,0x01,0xff,0xe0,0x00,0x00,0x00,0x00,0x07,0xff,0xf8,0x00,0x00,0x00,0x00,0x0f,0xff,0xfc,0x00,0x00,0x00,0x00,0x3f,0x80,0x7f,0x00,0x00,0x00
//,0x00,0x7e,0x00,0x1f,0x80,0x00,0x00,0x00,0x78,0x00,0x07,0x80,0x00,0x00,0x00,0xf0,0x00,0x03,0xc0,0x00,0x00,0x01,0xe0,0x00,0x01,0xec,0x00,0x00
//,0x01,0xe0,0x00,0x01,0xff,0xc0,0x00,0x03,0xc0,0x00,0x00,0xff,0xf0,0x00,0x03,0xc0,0x00,0x00,0xff,0xf8,0x00,0x03,0x80,0x00,0x00,0x40,0x7c,0x00
//,0x03,0x80,0x00,0x00,0x00,0x3e,0x00,0x07,0x80,0x00,0x00,0x00,0x1e,0x00,0x07,0x80,0x00,0x00,0x00,0x0f,0x00,0x07,0x80,0x00,0x00,0x00,0x07,0x00
//,0x07,0x80,0x00,0x00,0x00,0x07,0x00,0x03,0x80,0x00,0x00,0x00,0x07,0x80,0x03,0x80,0x00,0x00,0x00,0x07,0x80,0x03,0xc0,0x00,0x00,0x00,0x07,0x80
//,0x03,0xc0,0x78,0x00,0x78,0x07,0x80,0x01,0xe0,0x78,0x00,0x78,0x07,0x00,0x01,0xe0,0x78,0x00,0x78,0x0f,0x00,0x00,0xf0,0x78,0x00,0x78,0x0f,0x00
//,0x00,0x78,0x78,0x78,0x78,0x1e,0x00,0x00,0x78,0x78,0x78,0x78,0x3e,0x00,0x00,0x38,0x30,0x78,0x30,0x7c,0x00,0x00,0x08,0x00,0x78,0x00,0x78,0x00
//,0x00,0x00,0x00,0x78,0x00,0x70,0x00,0x00,0x00,0x00,0x78,0x00,0x40,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00
//,0x00,0x00,0x78,0x78,0x78,0x00,0x00,0x00,0x00,0x78,0x78,0x78,0x00,0x00,0x00,0x00,0x30,0x78,0x30,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00
//,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//};

const unsigned char partly_cloudy_day[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x06, 0x00, 0x0e, 0x00
, 0x00, 0x07, 0x80, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x3e, 0x00
, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x78, 0x00
, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00
, 0x00, 0x00, 0x01, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x00, 0x00
, 0x00, 0x07, 0xe7, 0xe0, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x80, 0x1f, 0x00, 0x00
, 0x00, 0xff, 0xff, 0x00, 0x0f, 0x00, 0x00, 0x03, 0xff, 0xff, 0x80, 0x07, 0x80, 0x00
, 0x07, 0xf0, 0x0f, 0xe0, 0x07, 0x80, 0x00, 0x0f, 0xc0, 0x03, 0xf0, 0x03, 0xc0, 0x00
, 0x1f, 0x00, 0x00, 0xf8, 0x03, 0xc1, 0xf8, 0x1e, 0x00, 0x00, 0x78, 0x03, 0xc3, 0xfc
, 0x3c, 0x00, 0x00, 0x3f, 0xc3, 0xc3, 0xfc, 0x3c, 0x00, 0x00, 0x3f, 0xfb, 0xc1, 0xf8
, 0x78, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x78, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00
, 0x70, 0x00, 0x00, 0x08, 0x1f, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00
, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00
, 0xf0, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00
, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00
, 0x78, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00
, 0x3c, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00
, 0x1e, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00
, 0x0f, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x1f, 0x80, 0x00
, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00
, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00
};

//GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=D8*/ EPD_CS, /*DC=D3*/ 16, /*RST=D4*/ 5, /*BUSY=D2*/ 19));

void setup(void) {
  Serial.begin(115200);

  Serial.println(F("wifi BEGIN"));
  initialise_wifi();
  Serial.println(F("init wifi END "));
  
  temp2.setCallback(tempcallback);
  press2.setCallback(presscallback);
  hum2.setCallback(humcallback);
  rainProb.setCallback(rainProbcallback);
  sunRise.setCallback(sunrisecallback);
  sunSet.setCallback(sunsetcallback);
  moonRise.setCallback(moonrisecallback);
  moonSet.setCallback(moonsetcallback);
  moonPhase.setCallback(moonphasecallback);
  azimuth.setCallback(azimutcallback);
  elevation.setCallback(elevationcallback);


  // Setup MQTT subscriptions
  mqtt.subscribe(&temp2);
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


  timUtil.setTimeClient(timeClient);
  timUtil.init();
  display.init(115200);

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
    Serial.println(F("BEFORE processPackets"));
    mqtt.processPackets(10000);
    Serial.println(F("AFTER  processPackets"));

    displayData();
    delay(20000);
}


void displayData()
{
  
//  String currentIcon = "weather.darksky.home.currently.icon";
  String dailySummary = F("Lokal veraenderliches Wetter, vereinzelt Schauer aber auch Sonnenschein");
//  double windSpeed = 25.09;
  display.setRotation(2);
  display.setFont(&FreeMonoBold18pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();

  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMonoBold9pt7b);

    display.setCursor(10, 21); display.println(timUtil.getTime());
    display.setCursor(160, 21); display.print("Version 1.3");
    display.setCursor(300, 21); display.print(localIP);
    display.setCursor(500, 21); display.println(timUtil.getDate());
    drawDashedHLine(10, 30, 720, GxEPD_BLACK);

    display.setFont(&FreeMonoBold12pt7b);
    dashedRect(10,35,360,125, GxEPD_BLACK);
    display_icon(2, 35+2, F("temperature"));
    display.setCursor(70, 47+8); display.println(String(gTemp2)+F(" Grad"));
    display.setCursor(70, 67+8); display.print(gHum2); display.println("%");
    display_icon(2, 65+8, F("prob_rain"));
    display.setCursor(70, 98+8); display.print(gRainProb); display.println(F(" Liter/qm"));
//    display_icon(100, 76+5, "wind_speed");
//    display.setCursor(140, 98+5); display.print((int)windSpeed, DEC); display.println("km/h");

    //display.setFont(&FreeMonoBold9pt7b);
    display_icon(15, 113+8, F("barometer"));
    display.setCursor(70, 135+8); display.print(gPress2); display.println("hPa");

    display.setFont(&FreeMonoBold9pt7b);
    drawDashedHLine(0, 155+20, 720, GxEPD_BLACK);
    display.setCursor(50, 170+25); display.println(dailySummary);
    drawDashedHLine(0, 220+20, 720, GxEPD_BLACK);
    display.setFont(&FreeMonoBold9pt7b);
    display_icon(10, 255+15, "sunrise_sunset");
    display.setCursor(60, 275+15); display.println(gSunRise);
    display.setCursor(60, 289+15); display.println(gSunSet);
    display.setFont(&FreeMonoBold18pt7b);
    display_icon(237, 265+15, "moon_"+String(gMoonPhase));
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(270, 275+15); display.println(gMoonRise);
    display.setCursor(270, 289+15); display.println(gMoonSet);
    drawDashedHLine(0, 320, 720, GxEPD_BLACK);
    display.setCursor(60, 368); display.println("Azimut: " + String(gAzimut));
    display.setCursor(60, 408); display.println("Hoehe: " + String (gElevation));
  }
  while (display.nextPage());
}

void drawDashedHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  display.startWrite();
  writeDashedLine(x, y, x + w - 1, y, color);
  display.endWrite();
}

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

void writeDashedLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  int16_t steep = abs(y1-y0) > abs(x1-x0);
  bool hole = false; //make it dash by using a hole every second pixel
  if (steep) {
    _swap_int16_t(x0, y0);
    _swap_int16_t(x1, y1);
  }

  if (x0 > x1) {
    _swap_int16_t(x0, x1);
    _swap_int16_t(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  }
  else {
    ystep = -1;
  }

  for (; x0 <= x1; x0++) {
    if (steep) {
      if (!hole) display.writePixel(y0, x0, color);
      hole = !hole;
    } else {
      if (!hole) display.writePixel(x0, y0, color);
      hole = !hole;
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

void dashedRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  display.startWrite();
  writeDashedLine(x, y, x + w - 1, y, color);
  writeDashedLine(x, y, x, y + h - 1, color);
  writeDashedLine(x + w - 1, y, x + w - 1, y + h - 1, color);
  writeDashedLine(x, y + h - 1, x + w - 1, y + h - 1, color);
  display.endWrite();
}

void display_icon(int x, int y, String icon_name) {
  int scale = 10; // Adjust size as necessary
  if (icon_name == F("partly-cloudy-day"))
    display.drawBitmap(x, y, partly_cloudy_day, 54, 50, GxEPD_BLACK);
  else if (icon_name == F("clear-day"))
    display.drawBitmap(x, y, clear_day, 54, 50, GxEPD_BLACK);
  //else if (icon_name == "rain")
  //  display.drawBitmap(x, y, rain, 54, 50, GxEPD_BLACK);
  else if (icon_name == F("sunrise_sunset"))
    display.drawBitmap(x, y, sunrise_sunset, 48, 36, GxEPD_BLACK);
  else if (icon_name == F("prob_rain"))
    display.drawBitmap(x, y, prob_rain, 54, 50, GxEPD_BLACK);
  else if (icon_name == F("temperature"))
    display.drawBitmap(x, y, temperature, 54, 50, GxEPD_BLACK);
  else if (icon_name == F("pressure"))
    display.drawBitmap(x, y, pressure, 69, 64, GxEPD_BLACK);
  else if (icon_name == "moon_0")
    display.drawBitmap(x, y, moon_0_8, 24, 24, GxEPD_BLACK);
  else if (icon_name == "moon_1")
    display.drawBitmap(x, y, moon_2, 24, 24, GxEPD_BLACK);
  else if (icon_name == "moon_2")
    display.drawBitmap(x, y, moon_3, 24, 24, GxEPD_BLACK);
  else if (icon_name == "moon_3")
    display.drawBitmap(x, y, moon_4, 24, 24, GxEPD_BLACK);
  else if (icon_name == "moon_4")
    display.drawBitmap(x, y, moon_5, 24, 24, GxEPD_BLACK);
  else if (icon_name == "moon_5")
    display.drawBitmap(x, y, moon_6, 24, 24, GxEPD_BLACK);
  else if (icon_name == "moon_6")
    display.drawBitmap(x, y, moon_6, 24, 24, GxEPD_BLACK);
  else if (icon_name == "moon_7")
    display.drawBitmap(x, y, moon_8, 24, 24, GxEPD_BLACK);
  else if (icon_name == "moon_8")
    display.drawBitmap(x, y, moon_0_8, 24, 24, GxEPD_BLACK);
  else if (icon_name == "barometer")
    display.drawBitmap(x, y, barometer, 30, 30, GxEPD_BLACK);
  else if (icon_name == "wind_speed")
    display.drawBitmap(x, y, wind_speed, 30, 30, GxEPD_BLACK);
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
    localIP = WiFi.localIP().toString();
    Serial.println(localIP);

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
void tempcallback(char* x, uint16_t dummy) {
    Serial.print("temperature change: ");
    Serial.println(x);
    gTemp2 = x;
}

void presscallback(char* x, uint16_t dummy) {
    Serial.print("pressure: ");
    Serial.println(x);
    gPress2 = x;
}
void humcallback(char* x, uint16_t dummy) {
    Serial.print("humidity: ");
    Serial.println(x);
    gHum2 = x;
}
void rainProbcallback(char* x, uint16_t dummy) {
    Serial.print("rain: ");
    Serial.println(x);
    gRainProb = x;
}
void sunrisecallback(char* x, uint16_t dummy) {
    Serial.print("sunrise: ");
    Serial.println(x);
    gSunRise = x;
}
void sunsetcallback(char* x, uint16_t dummy) {
    Serial.print("sunset: ");
    Serial.println(x);
    gSunSet = x;
}
void moonrisecallback(char* x, uint16_t dummy) {
    Serial.print("moonrise: ");
    Serial.println(x);
    gMoonRise = x;
}
void moonsetcallback(char* x, uint16_t dummy) {
    Serial.print("moonset: ");
    Serial.println(x);
    gMoonSet = x;
}
void moonphasecallback(char* x, uint16_t dummy) {
    Serial.print(("moonphase: "));
    Serial.println(x);
    gMoonPhase = x;
}
void azimutcallback(char* x, uint16_t dummy) {
    Serial.print(("azimut: "));
    Serial.println(x);
    gAzimut = x;
}
void elevationcallback(char* x, uint16_t dummy) {
    Serial.print(("elevation: "));
    Serial.println(x);
    gElevation = x;
}
