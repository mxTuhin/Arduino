
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

const byte address[][6] ={"1R0T1", "1R0T2"} ;
String charsIn="";

void setup() {
  Serial.begin(115200);
  if(radio.begin()){
//    Serial.println("Radio Connected");
  }
  else{
    Serial.println("No Radio");
  }
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);  //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);
  
}

void loop() {




  if(Serial.available()>0){
    radio.stopListening();
  String token=Serial.readString();
  char ch[32]= "";
    for(int i=0; i<token.length(); ++i){
      ch[i]=token.charAt(i);
    }
  radio.write(&ch, sizeof(ch));
  }

  radio.startListening(); 
delay(5);
  if (radio.available()>0) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
delay(5);

  
//  delay(1000);
}
