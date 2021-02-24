#include<Wire.h>
int irArray[] = {A0, A1, A2, A3, A4, A5, A6, A7};
int irReadings[8];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0; i<8; ++i){
    pinMode(irArray[i], INPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<8; ++i)
  {
    int readSensor[8];
    readSensor[i]=analogRead(irArray[i]);
    if(readSensor[i]<=200)
    {
      irReadings[i]=0;
    }
    else if(readSensor[i]>=900)
    {
      irReadings[i]=1;
    }
  }

  for(int i=0; i<8; ++i)
  {
    Serial.print(irReadings[i]);
    Serial.print(" ");
  }
  Serial.println();
  delay(300);

}
