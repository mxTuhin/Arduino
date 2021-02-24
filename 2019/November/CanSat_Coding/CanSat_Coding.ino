#include "DHT.h" // DHT22 and other sensors in the DHT range
#include <Wire.h>
#include <Adafruit_BMP085.h>


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define DHTPIN 8  // GPIO 2 (D3) ***** what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
RF24 radio(9, 10); // CE, CSN



String charsIn = "";
String data;
char printout[20];  //max char to print: 20
String flag="idle";
const byte address[][6] ={"1R0T1", "1R0T2"} ;



void setup() {
  Serial.begin(115200); // Starts the serial monitor at 115200
  dht.begin(); // Starts the DHT sensor
  
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  }
  
  if(radio.begin()){
//    Serial.println("Radio Connected");
  }
  else{
    Serial.println("No Radio");
  }
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);  //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
}

void loop() {

  
  String token="Data From Tx_Rx";;
  char ch[32]= "";
    for(int i=0; i<token.length(); ++i){
      ch[i]=token.charAt(i);
    }
//  radio.write(&ch, sizeof(ch));

  radio.startListening(); 
delay(5);
  if (radio.available()>0) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    String t="";
    t.concat(text);
    if(t.equalsIgnoreCase("c")){
      Serial.println("flagged");
      flag="active";
    }
    if(t.equalsIgnoreCase("d")){
      Serial.println("De Flagged");
      flag="idle";
    }
  }
delay(5);

  
  if(Serial.available()>0){
  while (Serial.available()>0) {
      char charRead = Serial.read();
      charsIn.concat(charRead);
    }
    if(charsIn != ""){
      if(charsIn.equalsIgnoreCase("a")){
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else if(charsIn.equalsIgnoreCase("b")){
        digitalWrite(LED_BUILTIN, LOW);
      }
      else if(charsIn.equalsIgnoreCase("c")){
        
      }
      else if(charsIn.equalsIgnoreCase("d")){
        flag="idle";
      }
      charsIn.toCharArray(printout, 21);
      charsIn = "";
    }
  }
  
//  Serial.print("Humidity: ");
//  Serial.println(humidity);
//  Serial.print("Temperature: ");
//  Serial.println(temperature);
//  Serial.print("Pressure: ");
//  Serial.println(pressure);

  
  if(flag.equalsIgnoreCase("active")){
    int humidity = dht.readHumidity();
    int temperature = dht.readTemperature();
    float pressure= bmp.readPressure();
    float alt=((pow((pressure/100325),(1/5.257))-1)*(temperature+273.15))/0.0065;
    alt-=50;
    String token="";
    token+=humidity;
    token+=",";
    token+=temperature;
    token+=",";
    token+=(long int)pressure;
    token+=",";
    token+=(int)alt;
    token+=",";
    token+=7.4;
//    Serial.println(token);
//    const char text[] = "";
    radio.stopListening();
    char ch[32]= "";
    for(int i=0; i<token.length(); ++i){
      ch[i]=token.charAt(i);
    }
    radio.write(&ch, sizeof(ch));
    delay(1000);
  }
//  delay(500);
}
