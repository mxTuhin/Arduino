#include <ESP8266WiFi.h> // Library for using the NodeMCU  // Library for using the NodeMCU 
#include <PubSubClient.h> // Library for using the Network protcall MQTT in this case
#include <DHT.h> // DHT22 and other sensors in the DHT range

/************************* WiFi Access Point *********************************/
const char* ssid = "reptile";
const char* password = "12345678xxx";
                  /************************* LinuxMqtt Setup *********************************/
const char* mqtt_server = "broker.hivemq.com";
#define MQTT_USER "mtuhin"
#define MQTT_PASSWORD "dark12345"
WiFiClient espClient;
PubSubClient client(espClient);

/************************* DHT22 Setup *************************************/
#define DHTPIN 5  // GPIO 15 (D1) ***** what digital pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);



int flame_sensor_pin = 4 ;// initializing pin 7 as the sensor output pin
int flame_pin  ; // state of sensor
int mq_sensor_pin=2;
int mq_pin;
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

/************************* DHT22 Setup *************************************/
  Serial.println("DHTxx test!"); // Prints out to the serial monitor console
  dht.begin();// Starts the DHT sensor
  pinMode ( flame_sensor_pin , INPUT ); // declaring sensor pin as input pin for Arduino
  pinMode(mq_sensor_pin, INPUT);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  } // MQTT
/************************* DHT22 *************************************/
    // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");

  // Wait a few seconds between measurements.
  delay(2000);

  flame_pin = digitalRead ( flame_sensor_pin ) ;
  mq_pin=digitalRead(mq_sensor_pin);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

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
  Serial.println("Flame Reading");
  Serial.println(flame_pin);
  Serial.println("Gas Reading");
  Serial.println(mq_pin);
  
/************************* Publish String MQTT ************************/
  client.publish("wifiTemp17101029124268", String(temperature).c_str());
  client.publish("wifiHumidity17101029124268", String(humidity).c_str());
  client.publish("wifiFlame17101029124268", String(flame_pin).c_str());
  client.publish("wifiGas17101029124268", String(mq_pin).c_str());
  

  // DHT22 sampling rate is 1HZ.
  delay(1000);
}
