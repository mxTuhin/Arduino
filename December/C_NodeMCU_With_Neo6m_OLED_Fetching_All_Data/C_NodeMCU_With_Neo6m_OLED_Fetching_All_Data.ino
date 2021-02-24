/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
 * Copyright (c) 2018 by Fabrice Weinberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ThingPulse invests considerable time and money to develop these open source libraries.
 * Please support us by buying our products (and not the clones) from
 * https://thingpulse.com
 *
 */

// Include the correct display library
// For a connection via I2C using Wire include
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
// or #include "SH1106Wire.h", legacy include: `#include "SH1106.h"`
// For a connection via I2C using brzo_i2c (must be installed) include
// #include <brzo_i2c.h> // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Brzo.h"
// #include "SH1106Brzo.h"
// For a connection via SPI include
// #include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Spi.h"
// #include "SH1106SPi.h"

// Include custom images
#include "images.h"

// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
// SSD1306Spi        display(D0, D2, D8);
// or
// SH1106Spi         display(D0, D2);

// Initialize the OLED display using brzo_i2c
// D3 -> SDA
// D5 -> SCL
// SSD1306Brzo display(0x3c, D3, D5);
// or
// SH1106Brzo  display(0x3c, D3, D5);

// Initialize the OLED display using Wire library
SSD1306Wire  display(0x3c, D3, D5);
// SH1106 display(0x3c, D3, D5);


#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;



//Neo6m*NodeMCU==============================================================================

#include <TinyGPS++.h>
#include <SoftwareSerial.h>


//ESP...............

#include <ESP8266WiFi.h> // Library for using the NodeMCU 
#include <PubSubClient.h> // Library for using the Network protcall MQTT in this case

//ESP...............

/************************* WiFi Access Point *********************************/
const char* ssid = "Reptile";
const char* password = "shadowmate55";
                  /************************* LinuxMqtt Setup *********************************/
const char* mqtt_server = "broker.hivemq.com";

static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;

float latitude , longitude, gpsSpeed, altValue, satValue;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str, speed_str, alt_str, sat_str;
int pm;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

WiFiClient espClient;
PubSubClient client(espClient);
//WiFiServer server(80);

void setup_wifi() {
  delay(100);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
//    please change following line to    
//if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");

    }
    else {
//      digitalWrite(resetPin, LOW);
//      ESP.reset();
      ESP.restart();
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(6000);
    }
  }
} //end reconnect()


void gpsData(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
        
      
      }

      if (gps.date.isValid())
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)
          date_str = '0';
        date_str += String(date);

        date_str += " / ";

        if (month < 10)
          date_str += '0';
        date_str += String(month);

        date_str += " / ";

        if (year < 10)
          date_str += '0';
        date_str += String(year);
      }

      if (gps.time.isValid())
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();

        minute = (minute + 60);
        if (minute > 59)
        {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 5) ;
        if (hour > 23)
          hour = hour - 24;

        if (hour >= 12)
          pm = 1;
        else
          pm = 0;

        hour = hour % 12;

        if (hour < 10)
          time_str = '0';
        time_str += String(hour);

        time_str += " : ";

        if (minute < 10)
          time_str += '0';
        time_str += String(minute);

        time_str += " : ";

        if (second < 10)
          time_str += '0';
        time_str += String(second);

        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";

      }
       
     
      alt_str="";
      sat_str="";
      speed_str="";
      gpsSpeed=gps.speed.mps();
      speed_str+=String(gpsSpeed);
//      Serial.println(gpsSpeed); 
      altValue=gps.altitude.feet();
      alt_str+=String(altValue);
//      Serial.println(altValue); 

      // Number of satellites in use (u32)
//      Serial.print("Number os satellites in use = "); 
      satValue=gps.satellites.value();
      sat_str+=String(satValue);
//      Serial.println(satValue); 
//      Serial.print("Lat");
//      Serial.println(lat_str);
//      Serial.print("Long");
//      Serial.println(lng_str);
//      Serial.print("Time");
//      Serial.println(time_str);
//      Serial.print("Date");
//      Serial.println(date_str);
      
      
      
    }
  }
}

//Neo6m&NodeMCU==============================================================================


void setup() {
  Serial.begin(115200);
//  Serial.println();
//  Serial.println();


  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  setup_wifi(); // add Method for the Wifi setup
  client.setServer(mqtt_server, 1883); // connects to the MQTT broker
  ss.begin(GPSBaud);

}

void drawFontFaceDemo() {
    gpsData();
     display.setTextAlignment(TEXT_ALIGN_LEFT);
     display.setFont(ArialMT_Plain_10);
     display.drawString(0, 0, "Lat: "+lat_str);
     display.setFont(ArialMT_Plain_10);
     display.drawString(0, 10, "Long: "+lng_str);
     display.setFont(ArialMT_Plain_10);
     display.drawString(0, 20, "Speed: "+speed_str+"   Alt: "+alt_str);
     display.setFont(ArialMT_Plain_10);
     display.drawString(0, 30, "Sat: "+sat_str);
     display.setFont(ArialMT_Plain_10);
     display.drawString(0, 40, "Time: "+time_str);
     display.setFont(ArialMT_Plain_10);
     display.drawString(0, 50, "Date: "+date_str);
     
}

//void drawImageDemo() {
//    // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
//    // on how to create xbm files
//    display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
//}



Demo demos[] = {drawFontFaceDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;

void loop() {
if (!client.connected()) {
    reconnect();
  } // MQTT
  
  // clear the display
  display.clear();
  // draw the current demo method
  demos[demoMode]();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();

  if (millis() - timeSinceLastModeSwitch > DEMO_DURATION) {
    demoMode = (demoMode + 1)  % demoLength;
    timeSinceLastModeSwitch = millis();
  }
  counter++;
  String latLong=lat_str+","+lng_str+","+speed_str;
  client.publish("lat17101029", String(lat_str).c_str());
  client.publish("long17101029", String(lng_str).c_str());
  client.publish("dateFormat17101029", String(date_str).c_str());
  client.publish("hourFormat17101029", String(time_str).c_str());
  client.publish("locationData17101029", String(latLong).c_str());
  client.publish("altData17101029", String(alt_str).c_str());
  client.publish("speedData17101029", String(speed_str).c_str());
  client.publish("satData17101029", String(sat_str).c_str());
}
