/*THIS TUTORIAL USED GSM SIM900A MINI V3.9.2
 
  Connect 5VT to D9 and 5VR to D10
  Feed GSM SIM900A with Arduino's 5V

  Code by IDAYU SABRI - MYBOTIC
*/
#include "SIM900.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
#include "inetGSM.h"
char mg;
char call;


extern unsigned char SmallFont[];

InetGSM inet;

String result ="";

char msg[250];
int i=0;
boolean started=false;

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("GSM SIM900A BEGIN");
  Serial.println("Enter character for control option:");
  Serial.println("h : to disconnect a call");
  Serial.println("i : to receive a call");
  Serial.println("s : to send message");
  Serial.println("c : to make a call");  
  Serial.println("e : to redial");
  Serial.println();
  delay(100);


  Serial.begin(9600);
     Serial.println("GSM Shield testing.");
     //Start configuration of shield with baudrate.
     //For http uses is raccomanded to use 4800 or slower.

if (inet.attachGPRS("internet", "", ""))
          {
               Serial.println("status=ATTACHED");
               Serial.println("Connected!");
          }
               
          else Serial.println("status=ERROR");
          delay(1000);

          //Read IP address.
          gsm.SimpleWriteln("AT+CIFSR");
          delay(5000);
//          //Read until serial buffer is empty.
//          gsm.WhileSimpleRead();

          inet.httpGET("www.educ8s.tv", 80, "/test.txt", msg, 250);
          String result = String(msg);
          Serial.println(result);
          int StringLength = result.length();

          Serial.println(result);

  
}

void loop()
{  
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'c':
      MakeCall();
      break;
    case 'h':
      HangupCall();
      break;
    case 'e':
      RedialCall();
      break;
    case 'i':
      ReceiveCall();
      break;
      case 'r':
      ReceiveMessage();
      break;
  }
 if (mySerial.available()>0)
 Serial.write(mySerial.read());
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+8801678710456\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("sim900a sms");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void ReceiveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (mySerial.available()>0)
  {
    mg=mySerial.read();
    Serial.print(msg);
  }
  delay(10000);
}

void MakeCall()
{
  mySerial.println("ATD+8801678710456;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
}


void HangupCall()
{
  mySerial.println("ATH");
  Serial.println("Hangup Call");
  delay(1000);
}

void ReceiveCall()
{
  mySerial.println("ATA");
  delay(1000);
  {
    call=mySerial.read();
    Serial.print(call);
  }
}

void RedialCall()
{
  mySerial.println("ATDL");
  Serial.println("Redialing");
  delay(1000);
}
