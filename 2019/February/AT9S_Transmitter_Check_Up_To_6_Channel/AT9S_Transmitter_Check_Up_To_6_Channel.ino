// Define Channel Pins:
const int chA=8;
const int chB=9;
const int chC=10;
const int chD=11;
const int chE=12;
const int chF=3;

// Define Relay Pins:
int relay1=4;
int relay2=5;
int relay3=6;
int relay4=7;
int relay5=26;
int relay6=27;

//Varibles to store and display the values of each channel
int ch1;//right/left
int ch2;
int ch3;//throttle
int ch4;
int ch5;//f/b
int ch6;

void setup() {
  Serial.begin(9600);
  pinMode(chA, INPUT);
  pinMode(chB, INPUT);
  pinMode(chC, INPUT);
  pinMode(chD, INPUT);
  pinMode(chE, INPUT);
  pinMode(chF, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
}

void loop() {
  ch1 = pulseIn(chA,HIGH);
  ch2 = pulseIn(chB,HIGH);
  ch3 = pulseIn(chC,HIGH);
  ch4 = pulseIn(chD,HIGH);
  ch5 = pulseIn(chE,HIGH);
  ch6 = pulseIn(chF,HIGH);
  
 Serial.println(ch1);
 Serial.println(ch2);
 Serial.println(ch3);
 Serial.println(ch4);
 Serial.println(ch5);
 Serial.println(ch6);
 
 
  
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
//  } else if(ch6>1500)
//  {
//    waterFlow();
//  }
//  else {
//    stopf();
//  }
}

void waterFlow(){
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  Serial.println("sggfs");
}


void forward(){
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
}

void backward(){
  digitalWrite(relay2, HIGH);
  digitalWrite(relay1, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay3, LOW);
}

void right(){
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay3, LOW);
}

void left(){
  digitalWrite(relay2, HIGH);
  digitalWrite(relay1, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
}

void bw_right(){
  digitalWrite(relay2, HIGH);
  digitalWrite(relay1, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
}

void bw_left(){
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay3, LOW);
}

void stopf(){
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
}
