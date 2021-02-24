/*
 * This is the Arduino code Infrared Obstacle Avoidance module
 * watch the video for details and demo https://youtu.be/T3Li128GBlM
 *  * 
 * Written by Ahmad Nejrabi for Robojax Video channel www.Robojax.com
 * Date: Dec 28, 2017, in Ajax, Ontario, Canada
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * this code has been downloaded from http://robojax.com/learn/arduino/
 * */
void setup() {
 Serial.begin(9600);
 pinMode(8, INPUT);// set pin as input

}

void loop() {
  //Written for Robojax on Dec 28, 2017
  int detect = digitalRead(8);// read obstacle status and store it into "detect"
  if(detect == LOW){
    
   Serial.println("Obastacle on the way"); 
  }else{
    
   Serial.println("All clear");  
  }
  delay(300);
}
    

