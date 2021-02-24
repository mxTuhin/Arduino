char data; 
void setup() {
pinMode(12,OUTPUT);
pinMode(11,OUTPUT);

Serial.begin(9600);

}


void loop() {
if(Serial.available()>0)
{
data=Serial.read();

}
  if(data=='a'){
    digitalWrite(12,HIGH);
    digitalWrite(11, LOW);

  }
  else if(data=='b'){
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
    
  
  }
}
