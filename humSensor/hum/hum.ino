/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

//#include <seesaw_servo.h>
//#include <seesaw_neopixel.h>
//#include <seesaw_motor.h>
//#include <Adafruit_TFTShield18.h>

#include <UnitLib.h>
#include "SoilSensor.h"
//#include <Adafruit_NeoTrellis.h>
//#include <Adafruit_NeoKey_1x4.h>
//#include <Adafruit_miniTFTWing.h>
//#include <Adafruit_Crickit.h>

// the setup function runs once when you press reset or power the board
//#include <cred.h>
//#include <WiFiUdp.h>
//#include <WiFiServerSecureBearSSL.h>
//#include <WiFiServerSecureAxTLS.h>
//#include <WiFiServerSecure.h>
//#include <WiFiServer.h>
//#include <WiFiClientSecureBearSSL.h>
//#include <WiFiClientSecureAxTLS.h>
//#include <WiFiClientSecure.h>
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
//#include <MqttClient.h>
int cnt;
String msg = "hugo";
SoilSensor soilSensor;
float hum = 0.0L;
uint16_t degrees = 0;
void setup() {
  // initialize digital pin 13 as an output.
	Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  logfln("%s %s", "in ", __FUNCTION__);
  wifiSetup();
  mqttSetup();
  cnt = 0;
  soilSensor.init();
  system_deep_sleep_set_option(2);
}

// the loop function runs over and over again forever
void loop() {
	
  mqttConnect("garden-control.fritz.box", "UweSolar4");

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5000);              // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  degrees = soilSensor.readSoilTemp();
  logfln("%s %u", "publishing temperature = ", degrees);
  mqttPublish("UweSolar2/bme/temp", String(degrees).c_str());
  hum = soilSensor.readSoilHum();
  logfln("%s %f", "publishing humidity = ", hum);
  mqttPublish("UweSolar2/bme/hum", String(hum).c_str());
  delay(2000);              // wait for a second
  system_deep_sleep_instant(5000 * 1000);

  
}
