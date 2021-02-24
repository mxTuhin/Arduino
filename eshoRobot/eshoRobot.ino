int relay1 = 4;
int relay2 = 5;
int relay3 = 6;
int relay4 = 7;

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
}

void loop() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
}
