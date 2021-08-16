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
#include <PubSubClient.h>
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
#include "cred.h"

WiFiClient wclient;
PubSubClient mqttClient(wclient);
//Adafruit_BME280 bme;
const char* ssid = SSID;
const char* wlanPwd = WLAN_KEY;
const char* mqttServer = "garden-control";

const unsigned int mqttPort = 1883;

// topics to listen to 
const char* temp_1 = "UweSolar1/bme/temp";
const char* temp_2 = "UweSolar2/bme/temp";
const char* press_2 = "UweSolar2/bme/press";
const char* temp_3 = "UweSolar3/bme/temp";
#define PROGMEM
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

const unsigned char rain[] PROGMEM = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x00
,0x00,0x01,0xff,0xe0,0x00,0x00,0x00,0x00,0x07,0xff,0xf8,0x00,0x00,0x00,0x00,0x0f,0xff,0xfc,0x00,0x00,0x00,0x00,0x3f,0x80,0x7f,0x00,0x00,0x00
,0x00,0x7e,0x00,0x1f,0x80,0x00,0x00,0x00,0x78,0x00,0x07,0x80,0x00,0x00,0x00,0xf0,0x00,0x03,0xc0,0x00,0x00,0x01,0xe0,0x00,0x01,0xec,0x00,0x00
,0x01,0xe0,0x00,0x01,0xff,0xc0,0x00,0x03,0xc0,0x00,0x00,0xff,0xf0,0x00,0x03,0xc0,0x00,0x00,0xff,0xf8,0x00,0x03,0x80,0x00,0x00,0x40,0x7c,0x00
,0x03,0x80,0x00,0x00,0x00,0x3e,0x00,0x07,0x80,0x00,0x00,0x00,0x1e,0x00,0x07,0x80,0x00,0x00,0x00,0x0f,0x00,0x07,0x80,0x00,0x00,0x00,0x07,0x00
,0x07,0x80,0x00,0x00,0x00,0x07,0x00,0x03,0x80,0x00,0x00,0x00,0x07,0x80,0x03,0x80,0x00,0x00,0x00,0x07,0x80,0x03,0xc0,0x00,0x00,0x00,0x07,0x80
,0x03,0xc0,0x78,0x00,0x78,0x07,0x80,0x01,0xe0,0x78,0x00,0x78,0x07,0x00,0x01,0xe0,0x78,0x00,0x78,0x0f,0x00,0x00,0xf0,0x78,0x00,0x78,0x0f,0x00
,0x00,0x78,0x78,0x78,0x78,0x1e,0x00,0x00,0x78,0x78,0x78,0x78,0x3e,0x00,0x00,0x38,0x30,0x78,0x30,0x7c,0x00,0x00,0x08,0x00,0x78,0x00,0x78,0x00
,0x00,0x00,0x00,0x78,0x00,0x70,0x00,0x00,0x00,0x00,0x78,0x00,0x40,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00
,0x00,0x00,0x78,0x78,0x78,0x00,0x00,0x00,0x00,0x78,0x78,0x78,0x00,0x00,0x00,0x00,0x30,0x78,0x30,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00
,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

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

//WiFiClient client;
//JsonParser<32> parser;
String currentLine = "";
String currRates = "";
//boolean readingJson = false;
//#define BUFFERSIZE 5800
//static char inData[BUFFERSIZE + 1]; // string + terminator

void setup(void) {
  Serial.begin(115200);
  initialise_wifi();
  display.init(115200);
}

void loop() {
//    // JSON Daten parsen
//    StaticJsonBuffer<5800> jsonBuffer;
//    JsonObject& root = jsonBuffer.parseObject(inData);
//    if (!root.success())
//    {
//      Serial.print("parseObject(");
//      Serial.print(inData);
//      Serial.println(") failed");
//    } else {
//      Serial.println("[Parse Success]");
//      printJsonData(root);
//    }


      printJsonData(/*root*/);
      delay(10000);
}

void printJsonData(/*JsonObject& root*/)
{
  int dateSubstringStart = 11;
  int dateSubstringEnd = 16;
  double ozone = 1.2;
  String uvIndex = "335";
  String uvIndexStr = uvIndex;
  //uvIndexStr.replace("u00e4", "ae");
  //uvIndexStr.replace("u00df", "ss");
  String curTime = "12:30:45";
  String curDate = "14. Februar 2021";
  double outsideHumidity = 0.5602;
  double surplus = 34;
  double regard = 45;
  double precipProb = 0.67;
  double pressure = 1122;
  String currentIcon = "weather.darksky.home.currently.icon";
  String moonLight = "env.location.moonlight";
  String moonRise = "6:40";
  String moonSet = "15:30";
  String moonPhase = "7";
  String sunSet ="17:02";
  String sunRise = "7:23";
  String temperature = "45";
  String temperatureMin = "-14";
  String temperatureMax = "+2";
  String currentlySummary = "Wetter Zusammenfassung";
  String dailySummary = "Lokal veraenderliches Wetter, vereinzelt Schauer aber auch Sonnenschein oder Niederschlag";
  double windSpeed = 25.09;
  display.setRotation(2);
  display.setFont(&FreeMonoBold18pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();

  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMonoBold9pt7b);

    display.setCursor(0, 11); display.println(curTime);
    display.setCursor(150, 11); display.println("Kolbermoor");
    display.setCursor(290, 11); display.println(curDate);
    drawDashedHLine(0, 20, 420, GxEPD_BLACK);

    display_icon(330, 25, currentIcon);
    display.setCursor(270, 42);
    if (surplus > 0) {
      display.println(surplus);
    } else {
      display.println((-1)*regard);
    }
    display.setCursor(270, 62); display.println("kW");
    display.setCursor(270, 100); display.println("UV: "+uvIndex);
    display.setCursor(270, 115); display.println(uvIndexStr);
    display.setCursor(270, 140); display.print("Ozon: "); display.println((int)ozone, DEC);

    display.setFont(&FreeMonoBold12pt7b);
    dashedRect(0,25,260,125, GxEPD_BLACK);
    display_icon(2, 25, "temperature");
    display.setCursor(50, 47); display.println(temperature+" Grad");
    display.setCursor(50, 67); display.print(outsideHumidity*100,0); display.println("%");
    display_icon(2, 65, "prob_rain");
    display.setCursor(50, 98); display.print(precipProb*100,0); display.println("%");
    display_icon(100, 76, "wind_speed");
    display.setCursor(140, 98); display.print((int)windSpeed, DEC); display.println("km/h");

    //display.setFont(&FreeMonoBold9pt7b);
    display_icon(15, 113, "barometer");
    display.setCursor(50, 135); display.print((int)pressure, DEC); display.println("hPa");

    display.setFont(&FreeMonoBold9pt7b);
    drawDashedHLine(0, 155, 420, GxEPD_BLACK);
    display.setCursor(0, 170); display.println(dailySummary);
    drawDashedHLine(0, 220, 420, GxEPD_BLACK);
    display.setFont(&FreeMonoBold9pt7b);
    display_icon(0, 255, "sunrise_sunset");
    display.setCursor(60, 275); display.println(sunRise);
    display.setCursor(60, 289); display.println(sunSet);
    display.setFont(&FreeMonoBold18pt7b);
    display_icon(137, 265, "moon_"+moonPhase);
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(170, 275); display.println(moonRise);
    display.setCursor(170, 289); display.println(moonSet);
  }
  while (display.nextPage());
  delay(4000);
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
  if (icon_name == "partly-cloudy-day")
    display.drawBitmap(x, y, partly_cloudy_day, 54, 50, GxEPD_BLACK);
  else if (icon_name == "clear-day")
    display.drawBitmap(x, y, clear_day, 54, 50, GxEPD_BLACK);
  else if (icon_name == "rain")
    display.drawBitmap(x, y, rain, 54, 50, GxEPD_BLACK);
  else if (icon_name == "sunrise_sunset")
    display.drawBitmap(x, y, sunrise_sunset, 48, 36, GxEPD_BLACK);
  else if (icon_name == "prob_rain")
    display.drawBitmap(x, y, prob_rain, 54, 50, GxEPD_BLACK);
  else if (icon_name == "temperature")
    display.drawBitmap(x, y, temperature, 54, 50, GxEPD_BLACK);
  else if (icon_name == "pressure")
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
    display.drawBitmap(x, y, moon_7, 24, 24, GxEPD_BLACK);
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
    // connect to WLAN
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, wlanPwd);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Wifi Connected to ");
    Serial.println(ssid);
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP());

}

void print_wifi_status() {
  // SSID des WiFi Netzwerkes ausgeben:
//  Serial.print("SSID: ");
//  Serial.println(WiFi.SSID());

  // WiFi IP Adresse des ESP32 ausgeben:
  //IPAddress ip = WiFi.localIP();
  //Serial.print("IP Address: ");
  //Serial.println(ip);

  //// WiFi Signalst�rke ausgeben:
  //long rssi = WiFi.RSSI();
  //Serial.print("signal strength (RSSI):");
  //Serial.print(rssi);
  //Serial.println(" dBm");
}
