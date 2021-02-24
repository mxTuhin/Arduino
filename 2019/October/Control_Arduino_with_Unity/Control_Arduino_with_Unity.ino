#include <Servo.h>
char data;

Servo s1;  // create servo object to control a servo
Servo s2;  // create servo object to control a servo


int pos = 0;    // variable to store the servo position

void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  s1.attach(9);
  s2.attach(10);
  
}
void loop(){
  if(Serial.available()>0){
    data = Serial.read();
    Serial.println(data);
    switch(data){
    case '1':
    servoOneTwoUp();
    break;
    case '2':
    servoOneTwoDown();
    break;
    case '3':
    center();
    break;
    }
  }
}

void servoOneTwoUp(){
  s1.write(110);
  s2.write(110);
}
void servoOneTwoDown(){
  s1.write(70);
  s2.write(70);
}
void center(){
  s1.write(90);
  s2.write(90);
}
