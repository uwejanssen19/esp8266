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
#include <ArduinoOTA.h>
#include <cred.h>
#define RELAY_PIN  (14)

// the setup function runs once when you press reset or power the board
void setup() {
        Serial.begin(115200);
        Serial.println("Booting");
        WiFi.mode(WIFI_STA);
        WiFi.begin(PRIVATE_SSID, PRIVATE_WLAN_KEY);
        while (WiFi.waitForConnectResult() != WL_CONNECTED) {
            Serial.println("Connection Failed! Rebooting...");
            delay(5000);
            ESP.restart();
        }

	ArduinoOTA.setHostname("UweSolar2");
    setupOTA();

  // initialize digital pin 13 as an output.
	pinMode(BUILTIN_LED, OUTPUT);
	pinMode(RELAY_PIN, OUTPUT);
	digitalWrite(RELAY_PIN, HIGH);   // turn the RELAY off (HIGH is the voltage level)
	delay(1000);              // wait for a second
	digitalWrite(RELAY_PIN, LOW);    // turn the LED off by making the voltage LOW
}

// the loop function runs over and over again forever
void loop() {
    ArduinoOTA.handle();
	digitalWrite(BUILTIN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.println("HIGH");
	delay(500);
	digitalWrite(BUILTIN_LED, LOW);    // turn the LED off by making the voltage LOW
    Serial.println("LOW");
    delay(500);              // wait for a second
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
