
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h> // Library for using the NodeMCU 
#include <PubSubClient.h> // Library for using the Network protcall MQTT in this case
#include <DHT.h> // DHT22 and other sensors in the DHT range


TinyGPSPlus gps;  // The TinyGPS++ object

SoftwareSerial ss(2, 5); // The serial connection to the GPS device

/************************* WiFi Access Point *********************************/
const char* ssid = "reptile";
const char* password = "12345678xxx";
                  /************************* LinuxMqtt Setup *********************************/
const char* mqtt_server = "broker.hivemq.com";
//#define MQTT_USER "mtuhin"
//#define MQTT_PASSWORD "dark12345"

float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;
int resetPin=2;



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

void setup() {
  digitalWrite(resetPin, HIGH);
  delay(200);
  // initialize the digital pin as an output.
  pinMode(resetPin, OUTPUT);     
  Serial.begin(115200); // Starts the serial monitor at 115200
  setup_wifi(); // add Method for the Wifi setup
  client.setServer(mqtt_server, 1883); // connects to the MQTT broker
  ss.begin(9600);
  

}

void loop() {

  if (!client.connected()) {
    reconnect();
  } // MQTT
/************************* GPS *************************************/
while (ss.available() > 0)
    gps.encode(ss.read());
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
      float altData= gps.altitude.feet();
      Serial.print("Alt");
      Serial.println(altData);
      float satCount = gps.satellites.value();
      Serial.print("Sat");
      Serial.println(gps.satellites.value());
      float gpsSpeed= gps.speed.kmph();
      Serial.print("Gps");
      Serial.println(gpsSpeed);
      Serial.println(time_str);
      Serial.println(date_str);
      Serial.println(lat_str);
      Serial.println(lng_str);
      
      


  String latLong=lat_str+","+lng_str;
  client.publish("locationData17101029", String(latLong).c_str());
  delay(500);

}
