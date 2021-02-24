/////////////////////////////////////////////////////////////////// 
//   the header file named "Adafruit_SSD1306" in the "Adafruit_SSD1306-master" folder 
//   uncomment "#define SSD1306_128_64" and comment "#define SSD1306_128_32" the statement if ur using 128x64 led display
//////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize I2C addr to 0x3C ( for 128x64 Display )
  
  display.clearDisplay(); // clear the display before starting the program to avoid adafruit splashscreen ( *we can also skip it by modifing header file )
  // drawBitmap(x-axis position, y-axis position, bitmap data, bitmap width, bitmap height, color)

}

void loop() {
  // put your main code here, to run repeatedly:
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Bbbhaweeeee...");
//  display.println("Bbbhaweeeee...");
  display.display();
  delay(5000);

}
