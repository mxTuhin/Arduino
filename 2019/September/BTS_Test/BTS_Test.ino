/*........................
BTS7960 Motor Driver Test
Written By : Mohannad Rawashdeh
Code for :
https://www.instructables.com/member/Mohannad+Rawashdeh/
*/
int RPWM=5;
int LPWM=6;
// timer 0
int L_EN=7;
int R_EN=8;

void setup() {
  // put your setup code here, to run once:
  for(int i=5;i<9;i++){
   pinMode(i,OUTPUT);
  }
    Serial.begin(9600);
  }



void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("EN High");
  digitalWrite(R_EN,HIGH);
  digitalWrite(L_EN,HIGH);
  analogWrite(RPWM,0);
  analogWrite(LPWM,100);
  
}
