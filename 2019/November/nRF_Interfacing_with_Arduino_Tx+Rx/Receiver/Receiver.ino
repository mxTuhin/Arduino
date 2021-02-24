/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "1R0T1";

void setup() {
  Serial.begin(115200);
  if(radio.begin()){
    Serial.println("Radio Connected");
  }
  else{
    Serial.println("No Radio");
  }
  
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()>0) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
