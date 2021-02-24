void setup()

{ // initialize serial communication at 9600 bits per second: Serial.begin(9600); }

// the loop routine runs over and over again forever:
Serial.begin(115200);
}
void loop()

{ 

int sensorValue = digitalRead(D0);

Serial.println(sensorValue);

delay(100);
}
