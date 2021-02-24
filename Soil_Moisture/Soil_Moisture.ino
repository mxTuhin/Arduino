/*
 * AskSensors IoT Platform. 
 * Description: Soil moisture monitoring using ESP8266 and the AskSensors IoT cloud.
 *  Author: https://asksensors.com, 2018 - 2019
 *  github: https://github.com/asksensors/AskSensors-ESP8266-Moisture
 */
int moisture_Pin= 0; // Soil Moisture Sensor input at Analog PIN A0
int moisture_value= 0;

void setup() {

  Serial.begin(115200);

}

void loop() {


    Serial.print("MOISTURE LEVEL : ");
    moisture_value= analogRead(moisture_Pin);
//    moisture_value= moisture_value/10;
    Serial.println(moisture_value);
    delay(1000);
   
}
