//#include <Servo.h>

//Servo myservo;  // create servo object to control a servo

// Define Channel Pins:
const int chA=8;
const int chB=9;
const int chC=10;
const int chD=11;
const int chE=12;
const int chF=3;
const int chG=2;
const int chH=46;
  int count=0;
  int pos=0;

// Define Relay Pins:
int relay1=4;
int relay2=5;
int relay3=6;
int relay4=7;
int relay5=42;
int relay6=43;
int relay7=44;

//Varibles to store and display the values of each channel
int ch1;//right/left
int ch2;
int ch3;//throttle
int ch4;
int ch5;//f/b
int ch6; //WaterFlow
int ch7; //WaterFlowBack
int ch8;

void setup() {
  Serial.begin(9600);
  pinMode(chA, INPUT);
  pinMode(chB, INPUT);
  pinMode(chC, INPUT);
  pinMode(chD, INPUT);
  pinMode(chE, INPUT);
  pinMode(chF, INPUT);
  pinMode(chG, INPUT);
  pinMode(chH, INPUT); 
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
//  myservo.attach(45);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  ch1 = pulseIn(chA,HIGH);
  ch2 = pulseIn(chB,HIGH);
  ch3 = pulseIn(chC,HIGH);
  ch4 = pulseIn(chD,HIGH);
  ch5 = pulseIn(chE,HIGH);
  ch6 = pulseIn(chF,HIGH);
  ch7 = pulseIn(chG, HIGH);
  ch8 = pulseIn(chH, HIGH);

  Serial.print(ch1);
  Serial.print(" || ");
  Serial.print(ch2);
  Serial.print(" || ");
  Serial.print(ch3);
  Serial.print(" || ");
  Serial.print(ch4);
  Serial.println();
  
  if(ch3 > 1200 && ch5 < 1200){
    forward();
  } else if(ch3 > 1200 && ch5 > 1600){
    backward();
  } else {
    stopf();
  }

  if(ch6 > 1600){
    digitalWrite(relay5, HIGH);
    digitalWrite(relay6, HIGH);
    digitalWrite(relay7, HIGH);
  } else {
    digitalWrite(relay5, LOW);
    digitalWrite(relay6, LOW);
    digitalWrite(relay7, LOW);
  }
 
  
//  if(ch3 > 1200 && ch5 < 1200 && ch1 > 1600){
//    right();
//  } else if(ch3 > 1200 && ch5 < 1200 && ch1 < 1200){
//    left();
//  } else if(ch3 > 1200 && ch5 > 1600 && ch1 > 1600){
//    bw_right();
//  } else if(ch3 > 1200 && ch5 > 1600 && ch1 < 1200){
//    bw_left();
//  } else if(ch3 > 1200 && ch5 < 1200){
//    forward();
//  } else if(ch3 > 1200 && ch5 > 1600){
//    backward();
//  } else if(ch3 < 1200 && ch1 > 1600){
//    right();
//  } else if(ch3 < 1200 && ch1 < 1200){
//    left();
//  } else if(ch6>1500){
//    waterFlow();
//  } else if(ch7>1500){
//    waterFlowBack();
//  } else if(ch8>1500){
//    servoControl();
//  }
//  else {
//    stopf();
//  }
}



//void servoControl(){
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//}
//
//void waterFlow(){
//
//  digitalWrite(relay5, HIGH);
//}
//
//void waterFlowBack(){
//  digitalWrite(relay5, LOW);0
//}

void forward(){
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
}

void backward(){
  digitalWrite(relay2, HIGH);
  digitalWrite(relay1, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay3, LOW);
}

//void right(){
//  digitalWrite(relay1, HIGH);
//  digitalWrite(relay2, LOW);
//  digitalWrite(relay4, HIGH);
//  digitalWrite(relay3, LOW);
//}
//
//void left(){
//  digitalWrite(relay2, HIGH);
//  digitalWrite(relay1, LOW);
//  digitalWrite(relay3, HIGH);
//  digitalWrite(relay4, LOW);
//}
//
//void bw_right(){
//  digitalWrite(relay2, HIGH);
//  digitalWrite(relay1, LOW);
//  digitalWrite(relay3, HIGH);
//  digitalWrite(relay4, LOW);
//}
//
//void bw_left(){
//  digitalWrite(relay1, HIGH);
//  digitalWrite(relay2, LOW);
//  digitalWrite(relay4, HIGH);
//  digitalWrite(relay3, LOW);
//}
//
void stopf(){
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
}
