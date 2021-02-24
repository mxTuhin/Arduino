// Sharp IR GP2Y0A41SK0F Distance Test
// http://tinkcore.com/sharp-ir-gp2y0a41-skf/

#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define pot A1 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)


void setup() {
  Serial.begin(9600); // start the serial port
  pinMode(pot, INPUT); //Optional 
  pinMode(sensor, INPUT); //Optional 
}

void loop() {
  
  // 5v
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int angle = analogRead(pot);          //Read and save analog value from potentiometer
  angle = map(angle, 0, 1023, 0, 315); //Map value 0-1023 to 0-255 (PWM)
  
  
  int distance = 13*pow(volts, -1); // worked out from datasheet graph

  Serial.print("Sensor Reading: ");
  Serial.println(distance);   // print the distance
  Serial.print("Turret Angle: ");
  Serial.println(angle);
  if(distance<8){
    Serial.println("Missile Loaded");
  }
  delay(1000); // slow down serial port 
}
