// This example code is in the public domain

int led1=3, led2=2, led3=5 ,led4=4, led5=7, led6=6, led7=10 ,led8=8 ,led9=9 ;
void setup() {

Serial.begin(9600);
for (int i=2; i<=10; ++i)
{
  pinMode(i, OUTPUT);
}

}

void loop() {

int s = analogRead(A0);

Serial.println(s);
if(s<=30){
for (int i=2; i<=10; ++i)
{
  digitalWrite(i, HIGH);
}
}

if(s>=900){
for (int i=2; i<=10; ++i)
{
  digitalWrite(i, LOW);
}
}
if(s>=35&& s<=80){
for (int i=2; i<=10; ++i)
{
  digitalWrite(i, HIGH);
  delay(50);
  digitalWrite(i, LOW);
}
}

if(s>=85 && s<=255){
  for (int i=2; i<=10; ++i)
{
  digitalWrite(i, HIGH);
  delay(100);
}
for (int i=10; i>=1; --i)
{
  digitalWrite(i, LOW);
  delay(100);
}
}

if(s>=300){
  for (int i=10; i>=1; --i)
{
  digitalWrite(i, HIGH);
  delay(100);
}
for (int i=10; i>=1; --i)
{
  digitalWrite(i, LOW);
}
}



}
