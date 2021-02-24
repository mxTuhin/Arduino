#include<HardwareSerial.h>

HardwareSerial MySerial(1);

void setup() {
    MySerial.begin(9600, SERIAL_8N1, 1, 3);
}

void loop() {
    while (MySerial.available() > 0) {
        uint8_t byteFromSerial = MySerial.read();
        // Do something
    }
    
    //Write something like that
    MySerial.write(1);
}
