/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "10001";

void setup() {
  Serial.begin(115200);
  if(radio.begin()){
    Serial.println("Radio Connected");
  }
  else{
    Serial.println("No Radio");
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
//  const char text[] = 
  String token="12,14,15,61,7,8";;
  char ch[32]= "";
    for(int i=0; i<token.length(); ++i){
      ch[i]=token.charAt(i);
    }
  radio.write(&ch, sizeof(ch));
  delay(1000);
}
