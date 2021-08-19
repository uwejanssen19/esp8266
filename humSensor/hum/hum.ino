

#include <UnitLib.h>
#include "SoilSensor.h"
#include <ArduinoOTA.h>
#include "TimUtil.h"

int cnt;
String msg;
SoilSensor soilSensor;
float hum = 0.0L;
float degrees = 0;
int vcc_raw = 0;
float vcc = 0.0;
int rssi = 0;
String ip = "";
boolean pmode = false;
void setupOTA();
void prepMsg(boolean pmode, String& msg);
TimUtilBase timUtil;
String timeString = "";


void setup() {
  Serial.begin(115200);
  //logfln("%s %s", "in ", __FUNCTION__);
  wifiSetup();
  mqttSetup();
  pinMode(D5, INPUT); // used for detecting programming mode via external switch
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   // OFF
  cnt = 0;
  soilSensor.init();
  system_deep_sleep_set_option(2);
  timUtil.init();
  //timUtil.showTime();
  setupOTA();

}
// the loop function runs over and over again forever
void loop() {
  ArduinoOTA.handle();
	             
  timUtil.update();
  //timUtil.showTime();
  timeString = timUtil.getTime();
  mqttConnect("garden-control.fritz.box", "UweSolar1");
  ArduinoOTA.handle();

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
  //logfln("%s", msg.c_str());
  degrees = soilSensor.readSoilTemp()-2;
  delay(5);
  //logfln("%s %f", "publishing vcc = ", vcc); 
  mqttPublish("UweSolar1/a0/a0", String(vcc).c_str());
  delay(5);
  //logfln("%s %f", "publishing temperature = ", degrees);
  mqttPublish("UweSolar1/bme/temp", String(degrees).c_str());
  delay(5);
  mqttPublish("UweSolar1/systime", timeString.c_str());
  delay(5);
  hum = soilSensor.readSoilHum();
  //logfln("%s %f", "publishing humidity = ", hum);
  char soilhumbuf[8];
  String(hum, 0).toCharArray(soilhumbuf, sizeof(soilhumbuf));
  //logfln("%s %s", "const char * soilhum = ", soilhumbuf);
  mqttPublish("UweSolar1/bme/hum", soilhumbuf);
  delay(10);
  mqttPublish("UweSolar2/bme/hum", soilhumbuf);
  delay(10);
  mqttPublish("soilhum", soilhumbuf);
  delay(10);
  //logfln("status =  %s", msg.c_str());

  pmode = digitalRead(D5); // check if pmode switch is set to programming mode
  //logfln("pmode = %i", pmode);
  prepMsg(pmode, msg);
  ArduinoOTA.handle();
  mqttPublish("UweSolar1/status", msg.c_str());
  delay(5);
  // wait before sleeping to let data out
  ArduinoOTA.handle();
  delay(5000);
  ArduinoOTA.handle();
  if (pmode) {
	  digitalWrite(LED_BUILTIN, HIGH);   // OFF
	  system_deep_sleep_instant(1800 * 1000 * 1000); // sleep x * 1000 * 1000 [secs]
  }
  else {
	  digitalWrite(LED_BUILTIN, LOW); // ON
//	  logfln("do not sleep");
  }
  ArduinoOTA.handle();
}
void prepMsg(boolean pmode, String& msg) {
	msg.reserve(70);
	msg = "UweSolar1 ";
	msg += "/ ";
	msg += ip; msg += " "; msg += rssi; msg += "dBm "; msg += vcc;
	msg += "V, pmode = "; msg += (pmode ? "sleeep" : "pgm");
}
