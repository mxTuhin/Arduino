// Define Channel Pins:
const int chA=8;

// Define Relay Pins:
int relay1=A1;

//Varibles to store and display the values of each channel
int ch1; //WaterFlow

void setup() {
  Serial.begin(9600);
  pinMode(chA, INPUT);
  pinMode(relay1, OUTPUT);
}

void loop() {
  ch1 = pulseIn(chA,HIGH);
  Serial.println(ch1);
  if(ch1>1800){
    waterFlow();
  } else{
    waterFlowBack();
  }
}


void waterFlow(){
  digitalWrite(relay1, HIGH);
}

void waterFlowBack(){
  digitalWrite(relay1, LOW);
}
