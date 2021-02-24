#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
char msg;
char call;

int ledPin = 13;   // LED connected to digital pin 13
int inPin = 7;     // pushbutton connected to digital pin 7
int val = 0;       // variable to store the read value
int resetPin=11;


void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  pinMode(ledPin, OUTPUT);      // sets the digital pin 13 as output
  pinMode(inPin, INPUT);        // sets the digital pin 7 as input
  
  digitalWrite(resetPin, HIGH);
  delay(200);
  // initialize the digital pin as an output.
  pinMode(resetPin, OUTPUT);     
  Serial.println("reset");//print reset to know the program has been reset and 
  //the setup function happened
  delay(200);
}

void loop()
{

  val = digitalRead(inPin);     // read the input pin
    Serial.println(val);
  digitalWrite(ledPin, val);    // sets the LED to the button's value
  if(val==1)
  {
    SendMessage();
    
  }
  if (mySerial.available()>0)
 Serial.write(mySerial.read());
  delay(1000);

  }

  void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+8801682512456\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Alert...");// The SMS text you want to send
  mySerial.println("I am in Danger");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
   Serial.println("Sending SMS");
  delay(10000);
  digitalWrite(resetPin, LOW);
}

 
