#include <SoftwareSerial.h>
SoftwareSerial lat_long(10,11); //rx, tx - 9,10 for arduino uno - 10,11 for arduino mega rx, tx
char messageminor[]= "Message Content: Minor";
char messagemajor[]= "Message Content: Help!";
String data[5];

#define DEBUG true

String state, timegps, latitude, longitude;
int pb_minor = 52;
int sendsmsminor;
int sendsmsmajor;
int accelero;

void setup() {
  lat_long.begin(9600);
  Serial.begin(9600);
  pinMode(52,INPUT);
  delay(50);
//  lat_long.print("AT+CSMP=17,167,0,0"); // set this parameter if empty SMS received
  delay(100);
  lat_long.print("AT+CMGF=1\r");
  delay(400);
  sendData("AT+CGNSPWR=1",1000,DEBUG);
  delay(50);
  sendData("AT+CGNSSEQ=RMC",1000,DEBUG);
  delay(150);
}

void loop() {
 pb_minor = digitalRead(52);
 if (pb_minor==LOW) {
  sendTabData("AT+CGNSINF",1000,DEBUG);
  sendsmsminor=1;
 }
/* else if (accelero==LOW) {
  sendTabData("AT+CGNSINF",1000,DEBUG);
  sendsmsmajor=1;
  }
  */
 else {
  sendsmsminor=0;
  sendsmsmajor=0;
 }
 
  if (state != 0 && sendsmsminor==1) {
    Serial.println("State :"+state);             
    Serial.println("Time :"+timegps);
    Serial.println("Latitude :"+latitude);
    Serial.println("Longitude :"+longitude);
//    lat_long.print("AT+CMGS=\"01994335868\"\r");
    delay(300);
    lat_long.println(messageminor); 
    delay(200);
    lat_long.print("Location:");
    lat_long.print("http://maps.google.com/maps?q=loc:");
    lat_long.print(latitude);
    lat_long.print(",");
    lat_long.print(longitude);
    delay(200);
    lat_long.println((char)26); //End AT command with a ^Z, ASCII code 26
    delay(200); 
    lat_long.println();
    delay(10000);
    lat_long.flush();
    }
   else if (state != 0 && sendsmsmajor==1) {
    Serial.println("State :"+state);             
    Serial.println("Time :"+timegps);
    Serial.println("Latitude :"+latitude);
    Serial.println("Longitude :"+longitude);
//    lat_long.print("AT+CMGS=\"01994335868\"\r");
    delay(300);
    lat_long.println(messagemajor); 
    delay(200);
    lat_long.print("Location:");
    lat_long.print("http://maps.google.com/maps?q=loc:");
    lat_long.print(latitude);
    lat_long.print(",");
    lat_long.print(longitude);
    delay(200);
    lat_long.println((char)26); //End AT command with a ^Z, ASCII code 26
    delay(200); 
    lat_long.println();
    delay(10000);
    lat_long.flush();
    }
  else {
    Serial.println("GPS Initializing...");
    delay(200);
  }
}
  void sendTabData(String command, const int timeout, boolean debug){
 
    lat_long.println(command);
    long int time = millis();
    int i = 0;   
   
    while((time+timeout) > millis()){
      while(lat_long.available()){       
        char c = lat_long.read();
        if(c != ','){ //read characters until you find comma, if found increment
          data[i]+=c;
          delay(100);
        }else{
          i++;       
        }
        if(i == 5){
          delay(100);
          goto exitL;
        }       
      }   
    }exitL:   
    if(debug){
      /*or you just can return whole table, in case if its not global*/
      state = data[1];  //state = recieving data - 1, not recieving - 0
      timegps = data[2];
      latitude = data[3];     //latitude
      longitude = data[4];    //longitude
    }
}
 
  String sendData (String command , const int timeout , boolean debug){
    String response = "";
    lat_long.println(command);
    long int time = millis();
    int i=0;
    while ((time+timeout) > millis()) {
      while (lat_long.available()){
        char c = lat_long.read();
        response +=c;
        }
    }
    if(debug){
      Serial.print(response);
    }
    return response;
  }
