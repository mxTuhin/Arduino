const byte channel1 = 18;
const byte channel2= 3;
int relay1 = 22;
int relay2=23;
int relay3=24;
int relay4=25;
boolean running;

void setup() {
  // put your setup code here, to run once:
    pinMode(channel2, INPUT_PULLUP);
  pinMode(channel1, INPUT_PULLUP);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  
  //digitalWrite(relay, HIGH);
  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(channel2), test2, CHANGE);   
   attachInterrupt(digitalPinToInterrupt(channel1), test, CHANGE);
}

void loop() {
  
  if(running)
  {
    int ch1 = pulseIn (channel1,HIGH);
  Serial.println(ch1);
  if(ch1 < 1300){
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);
  }
  else if(ch1 > 1600){
    digitalWrite(relay2, HIGH);
    digitalWrite(relay1, LOW);
  }
  }
  else{
    int ch2 = pulseIn (channel2,HIGH);
  Serial.println(ch2);
  if(ch2 < 1300){
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, LOW);
  }
  else if(ch2 > 1600){
    digitalWrite(relay4, HIGH);
    digitalWrite(relay3, LOW);
  }
   
}
}

void test(){
  running = true;
}

void test2(){
  running=false;
}
