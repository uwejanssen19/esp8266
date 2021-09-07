

#include <UnitLib.h>
#include "SoilSensor.h"
#include <ArduinoOTA.h>
#include "TimUtil.h"
//  prototype hardware: hardware WITHOUT (no adafruit bmpXX nor bme280 sensor AND pmode switch)  but *WITH* display : #define _PROTOTYPE
//  final hardware: hardware WITH (either adafruit bmpXX or bme280 sensor AND pmode switch) but without display : #undef _PROTOTYPE
#undef _PROTOTYPE

#ifdef _PROTOTYPE
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C 
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
#endif
#ifdef _PROTOTYPE 
# define HOSTNAME "UweSolar4_Prototype"
#else 
# define HOSTNAME "UweSolar1"
#endif 
#define VCC_TOPIC (HOSTNAME "/a0/a0")
#define SOIL_HUM_TOPIC (HOSTNAME "/bme/hum")
#define TIME_TOPIC (HOSTNAME "/time/value")
#define STATUS_TOPIC (HOSTNAME "/status")
#define SOIL_TEMP_TOPIC (HOSTNAME "/bme/temp")

#define RUN_MODE_STR "runMode = "
#define RUN_MODE_SLEEP (RUN_MODE_STR "SLEEP")
#define RUN_MODE_PGM (RUN_MODE_STR "PGM")
#define BOOLSTR(b) (b?RUN_MODE_SLEEP:RUN_MODE_PGM)
#define SLEEPMODE true
#define PMODE false

int cnt;
String msg;
SoilSensor soilSensor;
float hum = 0.0L;
float degrees = 0;
int vcc_raw = 0;
float vcc = 0.0;
int rssi = 0;
String ip = "";
boolean runMode = SLEEPMODE;
void setupOTA();
void prepMsg(boolean runMode, String& msg);
TimUtilBase timUtil;
String timeString = "";
#ifndef _PROTOTYPE
float bmeTemp = 99;
float bmePress = 888;
void printValues(); // test only
#endif // END #ifndef _PROTOTYPE

void setup() {
  Serial.begin(115200);
  //logfln("%s %s", "in ", __FUNCTION__);
  wifiSetup();
  mqttSetup();
  pinMode(D5, INPUT_PULLUP); // D5 used for run mode, default = open = HIGH = true = sleep 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   // OFF
  cnt = 0;
  soilSensor.init();
  system_deep_sleep_set_option(2);
  timUtil.init();
  //timUtil.showTime();
#ifndef _PROTOTYPE
  Serial.println(bme.begin(0x76));
#endif
#ifdef _PROTOTYPE
  u8g2.begin();
#endif
  setupOTA();

}
// the loop function runs over and over again forever
void loop() {
	             
  timUtil.update();
  //timUtil.showTime();
  timeString = timUtil.getTime();
  mqttConnect("garden-control.fritz.box", HOSTNAME);
#ifndef _PROTOTYPE
  // use the printValues method for the appropiate sensor
  //printValues <Adafruit_BMP085>() ;
  //printValues();
  bmeTemp = bme.readTemperature();
  bmePress = bme.readPressure();
#endif
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);              // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //delay(5);
#ifdef _PROTOTYPE
  vcc_raw = ESP.getVcc();
#else
  vcc_raw = analogRead(A0);
  vcc = vcc_raw * 4.2 / 1024;
#endif

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
  mqttPublish(VCC_TOPIC, String(vcc).c_str());
  delay(5);
  //logfln("%s %f", "publishing temperature = ", degrees);
  mqttPublish(SOIL_TEMP_TOPIC, String(degrees).c_str());
  delay(5);
  mqttPublish(TIME_TOPIC, timeString.c_str());
  delay(5);
  hum = soilSensor.readSoilHum();
  mqttPublish(SOIL_HUM_TOPIC, String(hum, 0).c_str());
  delay(10);
#ifndef _PROTOTYPE
  mqttPublish("UweSolar2/bme/temp", String(bmeTemp).c_str());
  delay(10);
  mqttPublish("UweSolar2/bme/press", String(bmePress/100).c_str());
  delay(10);
#endif
  mqttPublish("UweSolar2/bme/hum", String(hum, 0).c_str());
  delay(10);
  //logfln("status =  %s", msg.c_str());
#ifdef _PROTOTYPE
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.sendBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
 //u8g2.setFont(u8g2_font_t0_22b_tr);	// choose a suitable font
//  u8g2.drawStr(0, 11, "Hello v1.1");	
//  u8g2.drawStr(0, 22, "from VS mic!");

  // display IP address
  IPAddress localIP = WiFi.localIP();
  String ip = localIP.toString();

  u8g2.drawStr(15, 11, HOSTNAME);
  u8g2.drawStr(15, 22, String(hum, 0).c_str());
  //// display IP address
  u8g2.drawStr(15, 33, timeString.c_str());	// write something to the internal memory
  //// display IP address
  u8g2.drawStr(15, 44, (String("IP: ") + ip).c_str());
  u8g2.drawStr(15, 55, (String(rssi)+String("dBm")).c_str());

  u8g2.sendBuffer();

#endif // END #ifdef _PROTOTYPE
  runMode = digitalRead(D5); // check if pmode switch is set to programming mode
  //logfln("%s", BOOLSTR(runMode));
  prepMsg(runMode, msg);
//  logfln("status = %s", msg.c_str());
  mqttPublish(HOSTNAME "/status", msg.c_str());
  delay(5);
  // wait before sleeping to let data out
  delay(5000);
  if (runMode == SLEEPMODE) {
	  logfln("%s", "SLEEP mode active");
	  digitalWrite(LED_BUILTIN, HIGH);   // OFF
	  delay(1);
	  system_deep_sleep_instant(1800 * 1000 * 1000); // sleep x * 1000 * 1000 [secs] 
//	  system_deep_sleep_instant(2 * 1000 * 1000); // sleep x * 1000 * 1000 [secs] // short sleep for test only
  }
  else {
	  logfln("%s", "PROGRAMMING mode active");
	  digitalWrite(LED_BUILTIN, LOW); // ON
	  delay(1);
	  while (true) { // enter programming mode
		  delay(2000);
		  runMode = digitalRead(D5); // check if D5 switch is set to programming mode (active LOW)
		  logfln("waiting for to be set to sleep mode");
		  // check if OTA programming loop can be left
		  if (runMode == SLEEPMODE) {
			  // external switch was set to non programming mode -> leave programming loop 
			  Serial.println("set to sleepmode");
			  break;
		  }
		  else {// runMode = false = PGM
			  // continue programming mode 
			  ArduinoOTA.handle();
			  delay(1);
		  }
	  }
  }
}
//void prepMsg(boolean pmode, String& msg) {
//	msg.reserve(80);
//	msg += HOSTNAME;
//	msg += " / ";
//	msg += ip; msg += " "; msg += rssi; msg += "dBm "; msg += vcc;
//	msg += "V, pmode = "; msg += (pmode ? "sleep" : "pgm");
//}
void prepMsg(boolean runMode, String& msg) {
	msg = 
		String(HOSTNAME) + 
		" / "+ 
		ip + 
		" " + 
		rssi + 
		"dBm " + 
		vcc + 
		"V, pmode = " + 
		(runMode ? "sleep" : "pgm");
}
