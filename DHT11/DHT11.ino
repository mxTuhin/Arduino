#include<DHT.h>
DHT dht;

// if you require to change the pin number, Edit the pin with your arduino pin.

#define DHT11_PIN A0

void setup() {

Serial.begin(9600);

Serial.println("welcome to TechPonder Humidity and temperature Detector"); }

void loop() { // READ DATA

int chk = dht.read11(DHT11_PIN);

Serial.println(" Humidity " );

Serial.println(dht.humidity, 1);

Serial.println(" Temparature ");

Serial.println(dht.temperature, 1);

delay(2000);

}