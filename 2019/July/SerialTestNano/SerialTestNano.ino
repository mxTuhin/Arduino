#include <Servo.h>
char data;

Servo f1;  // create servo object to control a servo
Servo f2;  // create servo object to control a servo
Servo f3;  // create servo object to control a servo

void setup() {
  Serial.begin(115200);
  f1.attach(A0);  // attaches the servo on pin 9 to the servo object
  f2.attach(A1);
  f3.attach(A2);
  f1.write(15);
  f2.write(15);
  f3.write(15);
  pinMode(8, OUTPUT);
  for(int i=1; i<=2; ++i){
     digitalWrite(8, LOW);
  delay(10);
  digitalWrite(8, HIGH);
  delay(10);
  }
  digitalWrite(8, HIGH);
}
void loop() {
  if(Serial.available() > 0) {
    data=Serial.read();
    Serial.println(data);
    switch(data){
      case '0':
      closeHand();
      break;
      case '1':
      fingerSetOne();
      break;
      case '2':
      fingerSetTwo();
      break;
      case '4':
      fingerSetThree();
      break;
      case '5':
      openHand();
      break;
      
    }
  }
}

void closeHand(){
  f1.write(160);
  for(int i=1; i<=3; ++i){
     digitalWrite(8, LOW);
  delay(10);
  digitalWrite(8, HIGH);
  delay(10);
  }
  digitalWrite(8, HIGH);
  f2.write(160);
  f3.write(100);
}

void openHand(){
  f1.write(15);
  for(int i=1; i<=3; ++i){
     digitalWrite(8, LOW);
  delay(10);
  digitalWrite(8, HIGH);
  delay(10);
  }
  digitalWrite(8, HIGH);
  f2.write(15);
  f3.write(15);
  
}

void fingerSetOne(){
  f1.write(160);
  f2.write(15);
  f3.write(15);
}

void fingerSetTwo(){
  f1.write(15);
   for(int i=1; i<=3; ++i){
     digitalWrite(8, LOW);
  delay(10);
  digitalWrite(8, HIGH);
  delay(10);
  }
  digitalWrite(8, HIGH);
  f2.write(160);
  f3.write(15);
}

void fingerSetThree(){
  f1.write(15);
  f2.write(15);
  f3.write(100);
}
