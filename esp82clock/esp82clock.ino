//You need to set offsettime for me it is 19800
//Because my timezone is utc+5:30 so
//UTC +5:30=5.5*60*60=19800
//UTC+1=1*60*60=3600
//CALCULATE your timezone and edit it and then upload the code.


#include "NTPClient.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
const char *ssid = "Airel_9891989587";
const char *password = "air14211";

const long utcOffsetInSeconds = 19800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(){

 
Serial.begin(115200);

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

WiFi.begin(ssid, password);

while ( WiFi.status() != WL_CONNECTED ) {
delay ( 500 );
Serial.print ( "." );
}

timeClient.begin();
}

void loop() {
display.clearDisplay();
timeClient.update();

display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(45, 10);
Serial.print(daysOfTheWeek[timeClient.getDay()]);

display.println(daysOfTheWeek[timeClient.getDay()]);

display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.setCursor(15, 30);
//display.println(timeClient.getHours()":"timeClient.getMinutes()":"timeClient.getSeconds());

Serial.print(", ");
Serial.print(timeClient.getHours());
Serial.print(":");
Serial.print(timeClient.getMinutes());
Serial.print(":");
Serial.println(timeClient.getSeconds());

display.print(timeClient.getHours());
display.print(":");
display.print(timeClient.getMinutes());
display.print(":");
display.println(timeClient.getSeconds());
//Serial.println(timeClient.getFormattedTime());
display.display();

delay(1000);
}