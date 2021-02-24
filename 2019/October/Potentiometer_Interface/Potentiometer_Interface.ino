/* Learn how to use a potentiometer to fade an LED with Arduino - Tutorial
   More info and circuit schematic: http://www.ardumotive.com/arduino-tutorials/arduino-fade-led
   Dev: Michalis Vasilakis / Date: 25/10/2014                                                   */
   

//Constants:
const int potPin = A0; //pin A0 to read analog input

int value; //save analog value


void setup(){

  pinMode(potPin, INPUT); //Optional 
  Serial.begin(9600);

}

void loop(){
  
  value = analogRead(potPin);          //Read and save analog value from potentiometer
  value = map(value, 0, 1023, 0, 315); //Map value 0-1023 to 0-255 (PWM)
  Serial.println(value);
  delay(100);                          //Small delay
  
}


                           
