int led=13;
const int buzzerPin = 8; // declaring the PWM pin
char dataLog;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
//  pinMode(buzz, OUTPUT); //addigning pin to Output mode</p><p>}</p><p>void loop() {
  Serial.begin(115200);
  pinMode(buzzerPin, INPUT); 
  noTone(buzzerPin);
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  while(Serial.available()){
    if(Serial.available()>0){
      dataLog=Serial.read();
    }
    Serial.println(dataLog);
    if(dataLog=='1'){
      digitalWrite(led, HIGH);
    }
    else if(dataLog=='0'){
      digitalWrite(led, LOW);
    }
    else if(dataLog=='2'){
//      tone(buzz, 1000, 500);
pinMode(buzzerPin, OUTPUT);
tone(buzzerPin, 50);
  delay(50);
  noTone(buzzerPin);
  delay(100);
    }
    else if(dataLog=='3'){
      noTone(buzzerPin);
      pinMode(buzzerPin, INPUT); 
//      digitalWrite(buzz, LOW);
    }
    
    
  }

}
