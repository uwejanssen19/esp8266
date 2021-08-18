

#include <UnitLib.h>
#include "SoilSensor.h"

int cnt;
String msg = "UweSolar1 ";
SoilSensor soilSensor;
float hum = 0.0L;
float degrees = 0;
int vcc_raw = 0;
float vcc = 0.0;
int rssi = 0;
String ip = "";

void setup() {
  Serial.begin(115200);
  //logfln("%s %s", "in ", __FUNCTION__);
  wifiSetup();
  mqttSetup();
  cnt = 0;
  soilSensor.init();
  system_deep_sleep_set_option(2);
}

// the loop function runs over and over again forever
void loop() {
	
  mqttConnect("garden-control.fritz.box", "UweSolar1");

  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);              // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //delay(5);
  vcc_raw = analogRead(A0);
  vcc = vcc_raw * 4.2 / 1024;

//  logfln("%s %u", "vcc = ", vcc);
  delay(5);
  rssi = WiFi.RSSI();
 // logfln("%s %i", "signal strength =  ", rssi);
  delay(5);
  ip = WiFi.localIP().toString();
  //logfln("IP = %s", ip.c_str());
  delay(5);
  msg += "/ " + ip + " " + rssi + "dBm " + vcc + "V";
  //logfln("%s", msg.c_str());
  degrees = soilSensor.readSoilTemp();
  delay(5);
  //logfln("%s %f", "publishing vcc = ", vcc);
  mqttPublish("UweSolar1/a0/a0", String(vcc).c_str());
  delay(5);
  //logfln("%s %f", "publishing temperature = ", degrees);
  mqttPublish("UweSolar1/bme/temp", String(degrees).c_str());
  delay(5);
  hum = soilSensor.readSoilHum();
  //logfln("%s %f", "publishing humidity = ", hum);
  const char* soilhum = String(hum).c_str();
  mqttPublish("UweSolar1/bme/hum", soilhum);
  delay(5);
  mqttPublish("UweSolar2/bme/hum", soilhum);
  delay(5);
  mqttPublish("soilhum", soilhum);
  delay(5);
  //logfln("status =  %s", msg.c_str());
  mqttPublish("UweSolar1/status", msg.c_str());
  delay(5);
  delay(5000);              // wait before sleeping to let data out
  system_deep_sleep_instant(1800 * 1000 * 1000); // sleep x * 1000 * 1000 [secs]
  
}
