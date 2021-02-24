#include <WiFi.h>
 
const char* ssid = "reptile";
const char* password =  "12345678xxx";
float sensor=23;
float gas_value;
 
void setup() {
 
  Serial.begin(115200);
  pinMode(sensor,INPUT);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
 
gas_value=analogRead(sensor);
Serial.println(gas_value);
}
