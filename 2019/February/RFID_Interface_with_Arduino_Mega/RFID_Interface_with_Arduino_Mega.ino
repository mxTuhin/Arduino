int i;
String data;

void setup()
{
  Serial.begin(9600);  // start serial to PC 
  Serial.println("RFID Started...");
}

void loop()
{
  if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.readString();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor     
      Serial.println();  
   }
}
