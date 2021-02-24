#include <Arduino.h>

#include <SoftwareSerial.h>
SoftwareSerial SIM900(9, 10);

// this constant won't change:
const int  Pin3 = 7;      

// Variables will change:

int pin3State;             // the current reading from the input pin
int lastpin3State = HIGH;   // the previous reading from the input pin


unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  Serial.begin(19200);
  SIM900.begin(19200);
  pinMode(Pin3, INPUT);
  Serial.println("Initialiing...");
}


void sendSMS_pin3()
{
   SIM900.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  SIM900.println("AT+CMGS=\"+8801678710456\"\r"); // Replace x with mobile number
  delay(1000);
  SIM900.println("sim900a sms");// The SMS text you want to send
  delay(100);
   SIM900.println((char)26);// ASCII code of CTRL+Z
  delay(10000);
  Serial.println("SMS Sent");
}



void loop() {
  {

    int reading = digitalRead(Pin3);

    // If the switch changed, due to noise or pressing:
    if (reading != lastpin3State) {
      // reset the debouncing timer
      lastDebounceTime = millis();
      Serial.println("Button pressed");
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:

      // if the pin3 state has changed:
      if (reading != pin3State) {
        pin3State = reading;


        if (pin3State == HIGH) {

//          digitalWrite(9, HIGH);
//          delay(1000);
//          digitalWrite(9, LOW);
//          delay(5000);                                          // turn on GSM shield

          delay(1000);
          Serial.println("Sending Message");
          sendSMS_pin3();                                                        // send sms

//          digitalWrite(9, HIGH);
//          delay(1000);
//          digitalWrite(9, LOW);
//          delay(5000);
        }
      }

    }
    lastpin3State = reading;

  }
}
