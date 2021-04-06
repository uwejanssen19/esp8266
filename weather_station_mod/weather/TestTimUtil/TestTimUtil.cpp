// TestTimUtil.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <time.h>
#include <Windows.h>
time_t now;// this is the epoch
tm myTm;     // the structure tm holds time information in a more convient way

//void TimUtilClass::setTime()
//{
//	constexpr auto LENGTH = 6;
//	char buffer[LENGTH];
//	//String localTime = String(myTm.tm_hour) + ":" + String(myTm.tm_min);
//	strftime(buffer, LENGTH, "%H:%M", &tm);
//}

//void TimUtilClass::setDate(const String date)
//{
//	mDate = date;
//}

void init() {
	//	Serial.println("TimUtilClass::init()");
	configTime(MY_TZ, "de.ntp.pool.org");
}

void showTime() {
time(&now);                       // read the current time
localtime_r(&now, &myTm);           // update the structure tm with the current time
printf("year:");
printf(myTm.tm_year + 1900);  // years since 1900
printf("\tmonth:");
printf(myTm.tm_mon + 1);      // January = 0 (!)
printf("\tday:");
printf(myTm.tm_mday);         // day of month
printf("\thour:");
printf(myTm.tm_hour);         // hours since midnight  0-23
printf("\tmin:");
printf(myTm.tm_min);          // minutes after the hour  0-59
printf("\tsec:");
printf(myTm.tm_sec);          // seconds after the minute  0-61*
printf("\twday");
printf(myTm.tm_wday);         // days since Sunday 0-6
if (myTm.tm_isdst == 1)             // Daylight Saving Time flag
printf("\tDST");
else
printf("\tstandard");
printfln();
}



int main()
{
    std::string myString( "HEELOOO");
    std::cout << myString << "Hello World!\n";

}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
