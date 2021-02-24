#include <WiFi.h>
#include<PubSubClient.h>

int ENA = 23; //4;
int IN1 = 22; //0;
int IN2 = 21; //2;

const char *ssid = "reptile"; // cannot be longer than 32 characters!
const char *pass = "12345678xxx";

const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char *mqttuser = "******";
const char *mqttpass = "*********";

const int pin = 2;

void callback(String topic,byte* payload,unsigned int length1){ 
Serial.print("message arrived[");
Serial.print(topic);
Serial.println("]");
String msgg;

for(int i=0;i<length1;i++){
 Serial.print((char)payload[i]);
 msgg += (char)payload[i]; 
 
}
if(topic == "ledcontrol")
{
 if(msgg == "1"){
 digitalWrite(pin,HIGH); 
// digitalWrite(LED_BUILTIN, LOW);
digitalWrite(ENA, HIGH);  // set speed to 200 out of possible range 0~255
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);

delay(3000); // now change motor directions

digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);

delay(3000); // now turn off motors
 Serial.print("\n up \n ");

}
else if(msgg == "0")
{
 digitalWrite(pin,LOW);
// digitalWrite(LED_BUILTIN, HIGH);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);

Serial.print("\n down");
}
}
}

WiFiClient espclient;
PubSubClient client(mqtt_server,1883,callback,espclient);

void setup() {
 Serial.begin(115200);
 pinMode(pin,OUTPUT);
 pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
 WiFi.begin(ssid, pass);
 while (WiFi.status() != WL_CONNECTED) {
 delay(1000);
 Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 client.setServer(mqtt_server, mqtt_port);
 client.setCallback(callback);
 }


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
       client.subscribe("ledcontrol");

    }
    else {
      ESP.restart();
    }
  }
} //end reconnect()

// void reconnect(){
// while (!client.connected()) {
// Serial.println("Connecting to MQTT…");
// if (client.connect("ESP8266Client")) {
// Serial.println("connected"); 
// client.subscribe("ledcontrol");
// } else {
// Serial.print("failed with state ");
// Serial.print(client.state());
// delay(2000);
// }
// }
//}

void loop() 
{
 if(!client.connected()){
 reconnect();
 }
 client.loop();

}
