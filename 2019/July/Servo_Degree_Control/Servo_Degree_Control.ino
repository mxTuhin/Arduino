/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo f1;  // create servo object to control a servo
Servo f2;  // create servo object to control a servo
Servo f3;  // create servo object to control a servo

// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  f1.attach(A0);  // attaches the servo on pin 9 to the servo object
  f2.attach(A1);
  f3.attach(A2);
  
  f1.write(0);
  f2.write(10);
  f3.write(0);

}

void loop() {

 
}
