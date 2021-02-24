String charsIn = "";
String data;
char printout[20];  //max char to print: 20
String flag="idle";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
  while (Serial.available()>0) {
      char charRead = Serial.read();
      charsIn.concat(charRead);
    }
    if(charsIn != ""){
      if(charsIn.equalsIgnoreCase("a")){
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else if(charsIn.equalsIgnoreCase("b")){
        digitalWrite(LED_BUILTIN, LOW);
      }
      else if(charsIn.equalsIgnoreCase("c")){
        flag="active";
      }
      else if(charsIn.equalsIgnoreCase("d")){
        flag="idle";
      }
      charsIn.toCharArray(printout, 21);
      charsIn = "";
    }
  }
  if(flag.equalsIgnoreCase("active")){
    Serial.println("12.0");
    delay(500);
    Serial.println("13.0");
    delay(500);
    Serial.println("14.0");
    delay(500);
  }
  
  
}
