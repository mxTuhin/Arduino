#include <ESP8266WiFi.h> // Library for using the NodeMCU 
#include <PubSubClient.h> // Library for using the Network protcall MQTT in this case
#include "DHT.h" // DHT22 and other sensors in the DHT range

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

/************************* WiFi Access Point *********************************/
const char* ssid = "reptile"; // Add your SSID(The Name of the Wifi Router you connect to)
const char* password = "12345678xxx"; // The PassWord (Wireless Key)
                  /************************* LinuxMqtt Setup *********************************/
const char* mqtt_server = "broker.hivemq.com";
WiFiClient espClient;
PubSubClient client(espClient);

String date_str , time_str , lat_str , lng_str;

/************************* DHT22 Setup *************************************/
#define DHTPIN 2  // GPIO 2 (D3) ***** what digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

int moisture_Pin= 0; // Soil Moisture Sensor input at Analog PIN A0
int moisture_value= 0;
DHT dht(DHTPIN, DHTTYPE);



static const int RXPin = 4, TXPin = 5;
//static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

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
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");

    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(6000);
    }
  }
} //end reconnect()

void setup() {
  Serial.begin(115200); // Starts the serial monitor at 115200
  ss.begin(9600);
  setup_wifi(); // add Method for the Wifi setup
  client.setServer(mqtt_server, 1883); // connects to the MQTT broker

/************************* DHT22 Setup *************************************/
  Serial.println("DHTxx test!"); // Prints out to the serial monitor console
  dht.begin();// Starts the DHT sensor
  
}

void loop() {

  if (!client.connected()) {
    reconnect();
  } // MQTT



while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      // Latitude in degrees (double)
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);      
      // Longitude in degrees (double)
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6); 
      lat_str=String(gps.location.lat(), 6);
      lng_str=String(gps.location.lng(), 6);
    }
  }


  
/************************* DHT22 *************************************/
//    // start working...
//  Serial.println("=================================");
//  Serial.println("Sample DHT22...");

  // Wait a few seconds between measurements.
//  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  // Check if any reads failed and exit early (to try again).
//  if (isnan(humidity) || isnan(temperature)) {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(temperature, humidity, false);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");

//  Serial.print("MOISTURE LEVEL : ");
    moisture_value= analogRead(moisture_Pin);
    int sensorValue = digitalRead(D0);
//    Serial.println(moisture_value);
String latLong=lat_str+","+lng_str;
  client.publish("locationData17101029", String(latLong).c_str());
/************************* Publish String MQTT ************************/
  client.publish("wifiTemp17101029", String(temperature).c_str());
  client.publish("wifiHumidity17101029", String(humidity).c_str());
  client.publish("moisture17101029", String(moisture_value).c_str());
  client.publish("flame17101029", String(sensorValue).c_str());
  
  

  // DHT22 sampling rate is 1HZ.
  delay(500);
}
