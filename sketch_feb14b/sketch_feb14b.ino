int ledPins[]={1,2,3};
int pinCount=3;
void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite (1, LOW);
  delay (100);
  digitalWrite (2, LOW);
  delay (59);
  digitalWrite (3, LOW);
  delay (58);
  digitalWrite (1, HIGH);
  delay (100);
  digitalWrite (2, HIGH);
  delay (59);
  digitalWrite (3, HIGH);
  delay (100);
}
