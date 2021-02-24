#include <LiquidCrystal.h>

// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

int backLight = 13;    // pin 13 will control the backlight

void setup()
{
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  lcd.print("Done With Scroll");    // change text to whatever you like. keep it clean!
//  lcd.setCursor(0,1);           // set cursor to column 0, row 1
//  lcd.print("");
//  delay(2000);
//  lcd.clear();
//  lcd.print("");
//  lcd.blink();
//  delay(1000);
//  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
//  lcd.print("Second Project");    // change text to whatever you like. keep it clean!
//  lcd.setCursor(0,1);           // set cursor to column 0, row 1
//  lcd.print("With Display");
//  delay(2000);
//  lcd.clear();
//  lcd.print("The Way of Scrolling Display");
//  delay(1000);
//  for(int i=0; i<=12; i++){
//    lcd.scrollDisplayLeft();
//    delay(300);}
//    delay(2000);
//  lcd.clear();
//  lcd.print("");
//  lcd.blink();
//  delay(500);
//  lcd.print("On Next ??");
//  delay(2000);
//  lcd.clear();
//  lcd.print("");
//  lcd.blink();
//  lcd.print("ki korum :3");
//  delay(2000);
//  lcd.clear();
//  lcd.print("");
//  lcd.blink();           // set cursor to column 0, row 0 (the first row)
//  lcd.print("Bujhtechi na :(");
//  delay(2000);// change text to whatever you like. keep it clean
//  lcd.clear();
//  lcd.print("");
//  lcd.blink();
//  lcd.print("Pari na kichu :( !");
//  delay(2000);
//  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
//  lcd.print("Antajei !!! ulta");    // change text to whatever you like. keep it clean!
//  lcd.setCursor(0,1);           // set cursor to column 0, row 1
//  lcd.print("Palta Likhtechi !");
//  delay(2000);
//  lcd.clear();
//  lcd.print("");
//  lcd.blink();
//  lcd.begin(16,2);        
//   lcd.setCursor(0,0);                       // set cursor to column 0, row 0 (the first row)
//  lcd.print("With Respect");
//         // change text to whatever you like. keep it clean!
//  lcd.setCursor(0,1);           // set cursor to column 0, row 1
//  lcd.print("Love U BRACU <3 . Love U ROBU <3");
//  delay(2000);
//  for(int i=0; i<=15; i++){
//    lcd.scrollDisplayLeft();
//    delay(300);
//  }
//  
//  
//  
//  // if you have a 4 row LCD, uncomment these lines to write to the bottom rows
//  // and change the lcd.begin() statement above.
//  //lcd.setCursor(0,2);         // set cursor to column 0, row 2
//  //lcd.print("Row 3");
//  //lcd.setCursor(0,3);         // set cursor to column 0, row 3
//  //lcd.print("Row 4");
}

void loop()
{
}
