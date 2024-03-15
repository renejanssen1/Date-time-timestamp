#include <ESP8266WiFi.h>  // or WiFi.h for ESP32 boards
#include <time.h>
char ssid[] = "	";
char pass[] = "	";
char timeString[9];
char dateString[11];
int u = 0;
int m = 0;
int s = 0;
int y = 0;
int mo = 0;
int d = 0;

#define MY_NTP_SERVER "pool.ntp.org"           
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"   

time_t now;  // this are the seconds since Epoch (1970) - UTC
tm tm;       // the structure tm holds time information in a more convenient way

void setup() {
  Serial.begin(115200);
  configTime(MY_TZ, MY_NTP_SERVER); // --> Here is the IMPORTANT ONE LINER needed in your sketch!
// replace configTime(MY_TZ, MY_NTP_SERVER); if you use ESP32 board with this
// configTime(0, 0, MY_NTP_SERVER);
// setenv("TZ", MY_TZ, 1); 
// tzset();
  WiFi.hostname("ESP8266");
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);     
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); 
}

void loop() {
  time(&now);             // read the current time
  localtime_r(&now, &tm); // update the structure tm with the current time
  Serial.print("Timestamp: ");
  Serial.println(now);
  u = tm.tm_hour;
  m = tm.tm_min;
  s = tm.tm_sec;
  y = tm.tm_year + 1900;
  mo = tm.tm_mon + 1;
  d = tm.tm_mday;
  Serial.print("Tijd: "); 
  snprintf(timeString, 9, "%02d%02d%02d", u, m, s);
  Serial.println(timeString);
  Serial.print("Datum: ");
  snprintf(dateString, 11, "%04d%02d%02d", y, mo, d);
  Serial.println(dateString);
  if (tm.tm_isdst == 1)             // Daylight Saving Time flag
    Serial.print("Zomertijd");
  else
    Serial.print("Wintertijd");
  Serial.println();
  delay(1000); 
}
