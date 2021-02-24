/* www.learningbuz.com */
/*Impport following Libraries*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);



  float temp;
int tempPin = A0;
int flamePin=A1;


void setup(){
  Serial.begin(9600);
  lcd.begin(20,4);//Defining 16 columns and 2 rows of lcd display
lcd.backlight();//To Power ON the back light
//lcd.backlight();// To Power OFF the back light
pinMode(flamePin, INPUT);
}

void loop()
{

temp = analogRead(tempPin);
Serial.println(analogRead(flamePin));

temp = temp * 0.28828125;

Serial.print("TEMPRATURE = ");

Serial.print(temp);

Serial.print("*C");

Serial.println();

delay(1000);

  lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print("Temperature  "); //You can write 16 Characters per line .
lcd.print(temp);
if(analogRead(flamePin)<=1000){
lcd.setCursor(0,1);
lcd.print("Flame ");
lcd.print("== Yes");
}
else{
  lcd.setCursor(0,1);
lcd.print("Flame ");
lcd.print("== No");
}
lcd.setCursor(0,2);
lcd.print("Gas Detection ");
lcd.print("== No");

}
