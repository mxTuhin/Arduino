#include <WiFi.h> // Library for using the NodeMCU  // Library for using the NodeMCU 
#include <PubSubClient.h> // Library for using the Network protcall MQTT in this case

/************************* WiFi Access Point *********************************/
const char* ssid = "IOT";
const char* password = "12345678";
                  /************************* LinuxMqtt Setup *********************************/
const char* mqtt_server = "broker.hivemq.com";
#define MQTT_USER "mtuhin"
#define MQTT_PASSWORD "dark12345"

// defines pins numbers
const int trigPin = 2;
const int echoPin = 5;

// defines variables
long duration;

int distance;

String sensorID="s1";
WiFiClient espClient;
PubSubClient client(espClient);


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
  setup_wifi(); // add Method for the Wifi setup
  client.setServer(mqtt_server, 1883); // connects to the MQTT broker

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

/************************* DHT22 Setup *************************************/

  

}

void loop() {

  if (!client.connected()) {
    reconnect();
  } // MQTT

  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

Serial.print("Distance: ");
Serial.println(distance);    

if(distance<=30){
  client.publish("wifiDistance17101029", sensorID.c_str());
}
else if(distance>30){
  client.publish("wifiDistanceNull17101029", sensorID.c_str());
}




  // DHT22 sampling rate is 1HZ.
  delay(200);
}
