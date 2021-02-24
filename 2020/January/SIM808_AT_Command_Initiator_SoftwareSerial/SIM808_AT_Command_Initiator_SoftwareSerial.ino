/*
***************************************************
Programmed by iakbasnayaka for www.easymades.com
This is for checking of AT commands for SIM800L
https://www.youtube.com/easymades
***************************************************
*/

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial Sim800l(10,11);
TinyGPSPlus gps;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Sim800l.begin(9600);
}

void loop() {
 while(Sim800l.available()){
//  Serial.write(Sim800l.read());
   if (gps.encode(Sim800l.read()))
      displayInfo();

 }

}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.println(gps.location.lng(), 6);
  }

}
