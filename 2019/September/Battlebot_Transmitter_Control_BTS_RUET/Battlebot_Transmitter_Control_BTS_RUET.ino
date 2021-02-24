int RF=5;//BTS 1
int RB=6;
int L_EN=7;
int R_EN=8;

int LF=10;//BTS 2
int LB=11;
int L_EN_1=13;
int R_EN_1=12;

int Speed = 200; // 0 - 255.

// Define Channel Pins:
const int chA=24;
const int chB=25;
const int chC=26;
const int chD=27;
const int chE=28;
const int chF=29;
const int chG=30;
const int chH=31;

int count=0;
int pos=0;


//Varibles to store and display the values of each channel
int ch1;//right/left
int ch2;
int ch3;//throttle
int ch4;
int ch5;//f/b
int ch6; 
int ch7; 
int ch8;



void setup() {
  // put your setup code here, to run once:

  //Transmitter Pin Input
  pinMode(chA, INPUT);
  pinMode(chB, INPUT);
  pinMode(chC, INPUT);
  pinMode(chD, INPUT);
  pinMode(chE, INPUT);
  pinMode(chF, INPUT);
  pinMode(chG, INPUT);
  pinMode(chH, INPUT); 

  
  //BTS 1
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
  //BTS 2
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(L_EN_1, OUTPUT);
  pinMode(R_EN_1, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

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
  Serial.print(" || ");
  Serial.print(ch5);
  Serial.print(" || ");
  Serial.print(ch6);
  Serial.print(" || ");
  Serial.print(ch7);
  Serial.print(" || ");
  Serial.print(ch8);
  Serial.print(" || ");
  Serial.println();

  //Write Condition to control Bot (Example set is written)

  if(ch3 > 1200 && ch5 < 1200){
    forward();
  } else if(ch3 > 1200 && ch5 > 1600){
    backward();
  } else {
    Stop();
  }

}



void forward() {
  analogWrite(RF, Speed);
  analogWrite(RB, 0);
  analogWrite(LF, Speed);
  analogWrite(LB, 0);
}

void backward() {
  analogWrite(RF, 0);
  analogWrite(RB, Speed);
  analogWrite(LF, 0);
  analogWrite(LB, Speed);
}

void left() {
  analogWrite(RF, Speed);
  analogWrite(LF, 0);
  analogWrite(RB, 0);
  analogWrite(LB, Speed);
}

void right() {
  analogWrite(RF, 0);
  analogWrite(LF, Speed);
  analogWrite(RB, Speed);
  analogWrite(LB,0);
}

void forwardleft() {
  analogWrite(RF, Speed);
  analogWrite(LF, 0);
  analogWrite(RB, 0);
  analogWrite(LB,0);
}

void forwardright() {
  analogWrite(RF, 0);
  analogWrite(LF, Speed);
  analogWrite(RB,0);
  analogWrite(LB, 0);
}

void backright() {
  analogWrite(RF, 0);
  analogWrite(LF, 0);
  analogWrite(RB, Speed);
  analogWrite(LB,0);
}
void backleft() {
  analogWrite(RF, 0);
  analogWrite(LF, 0);
  analogWrite(RB, 0);
  analogWrite(LB,Speed);
}


void Stop() {
  analogWrite(RF, 0);
  analogWrite(RB, 0);
  analogWrite(LF, 0);
  analogWrite(LB, 0); 
}
