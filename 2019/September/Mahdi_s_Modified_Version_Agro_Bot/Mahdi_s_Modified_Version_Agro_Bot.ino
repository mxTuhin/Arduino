int RF=5;//BTS 1
int RB=6;
int L_EN=7;
int R_EN=8;

int LF=10;//BTS 2
int LB=11;
int L_EN_1=13;
int R_EN_1=12;

//Relay Module(4channel)
int R1=40;
int R2=42;
int R3=44;
int R4=46;


char command; //Int to store app command state.
int Speed = 200; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn,
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.
void setup() {

  //BT 1
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
  //BT 2
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(L_EN_1, OUTPUT);
  pinMode(R_EN_1, OUTPUT);
  //Relay
   pinMode(R1, OUTPUT);
   pinMode(R2, OUTPUT);
   pinMode(R3, OUTPUT);
   pinMode(R4, OUTPUT);
   
   digitalWrite(R1,HIGH);
   digitalWrite(R2,HIGH);
   digitalWrite(R3,HIGH);
   digitalWrite(R4,HIGH);
  Serial.begin(9600);  
}

void loop() {

//  Serial.println("EN High");
  digitalWrite(R_EN,HIGH);
  digitalWrite(L_EN,HIGH);
  digitalWrite(R_EN_1,HIGH);
  digitalWrite(L_EN_1,HIGH);
  //For the relay module
  
  //from here BT code start
  if (Serial.available() > 0) {
    command = Serial.read();
    Serial.print(command);
    Stop(); 
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
            
        //Relay Code start    
        case 'W':
         ActOn();
         break;
         break;
        case 'U':
         ActOff();
         break;
        case 'V':
         Mold();
         break;
         case 'X':
         Seed();
         break;
        
         //Relay Code End    
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
    }
    Speedsec = Turnradius;
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  }
}

void forward() {
 analogWrite(RF, Speed);
  analogWrite(RB, 0);
  analogWrite(LF, Speed);
  analogWrite(LB, 0);
}

void back() {
  analogWrite(RF, 0);
  analogWrite(RB, Speed);
  analogWrite(LF, 0);
  analogWrite(LB, Speed);
}
void AcLong(){
  
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
  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);
  digitalWrite(R3,HIGH);
  digitalWrite(R4,HIGH); 
}


//Relay Module Functions

void ActOn(){
  analogWrite(R1,HIGH);
  }
void ActOff(){
  analogWrite(R1,LOW);
  }
void Mold(){
  analogWrite(R3,HIGH);
  }
void Seed(){
  analogWrite(R4,HIGH);
  }  


void brakeOn() {
  buttonState = command;
  if (buttonState != lastButtonState) {
    if (buttonState == 'S') {
      if (lastButtonState != buttonState) {
        analogWrite(RF, 0);
        analogWrite(RB, 0);
        analogWrite(LF, 0);
        analogWrite(LB, 0);
        delay(brakeTime);
        Stop();
      }
    }
    lastButtonState = buttonState;
  }
}
void brakeOff() {

}
