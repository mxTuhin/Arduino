int irArray[] = {A0, A1, A2, A3, A4, A5}; //Defining an array of length 6 and storing the arduino analogPins
int irReadings[6]; ////Defining another array of length 6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Serial Begins
  for(int i=0; i<6; ++i){
    pinMode(irArray[i], INPUT);  //Defining pinMode of A0, A1, A2, A3, A4, A5 to Input. 
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<6; ++i)
  {
    int readSensor[6]; //Temporary Array to store analog Values that the sensor provides.
    readSensor[i]=analogRead(irArray[i]); //Storing the analog Values in the array list of "i"

    /*First Check the outputs without this if statement(leave it as it is) 
     * and then Use this if statements(Remove the comment slashes "//") 
     * to understand whats been done here.
     */
    
//    if(readSensor[i]<=200)
//    {
//      irReadings[i]=0;
//    }
//    else if(readSensor[i]>=900)
//    {
//      irReadings[i]=1;
//    }

    // Remove Slashes above this line. Shortcut (Select the lines and press " ctrl+/ ")
  }

  for(int i=0; i<6; ++i)
  {
    Serial.print(irReadings[i]);
    Serial.print(" ");
  }
  Serial.println();
  delay(300);

}
