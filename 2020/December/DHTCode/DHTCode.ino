 
#include "DHT.h"                //Including DHT Library
#define DHTPIN 4                //Defining DHTPIN
#define DHTTYPE DHT11           //Defining DHTVersion
DHT dht(DHTPIN, DHTTYPE);       //DHT Initialisation

#include<SoftwareSerial.h>      //Including SoftwareSerial Library
int smokemq2 = A3;              //Declaring that smokemq2 variable will trigger A3(Analog 3) pin
int sensorThres = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           //Serial Communication begins and the port will transfer data in 9600 baud rate
  dht.begin();                  //calling the begin() method from dht library to start data trasfer of DHT Sensor
  pinMode(smokemq2, INPUT);     //Declaring Pin Mode for smokemq2 as Input Pin
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(250);                    //Delay for 250ms
  int t = (int)dht.readTemperature();   //Reading temperature from the sensor and preserving it to t variable
  Serial.println(t);                    //Printing the value of t on Serial monitor

  int analogSensor = analogRead(smokemq2);  //Reading the value of smoke sensor and preserving it to analogSensor variable
  Serial.println(analogSensor);         //Printing the value of analogSensor variable on Serial Monitor
  delay(100);                     //Delay for 100ms
}
