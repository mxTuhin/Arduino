#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

#define PIN_TX    10
#define PIN_RX    11
SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,
boolean readBool=true;

char con[100];

char http_cmd[] = "GET /h.php?lat=23.651054&lon=90.451039&devID=GH9IG5D6 HTTP/1.0\r\n"
                  "Host: mce.asia\r\n"
                  "\r\n";
char buffer[512];

int data1 = 0;
int ok = -1;
int yes = 13;
int no = 12;
int tag1[14] = {2,50,51,48,48,67,68,55,68,70,55,54,52,3};
int tag2[14] = {2,52,48,48,48,56,54,67,54,54,66,54,66,3};
int newtag[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // used for read comparisons
String s="";
void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600); // start serial to PC
  pinMode(yes, OUTPUT); // for status LEDs
  pinMode(no, OUTPUT);

  //******** Initialize sim808 module *************
  while(!sim808.init()) {
      delay(1000);
      Serial.print("Sim808 init error\r\n");
  }
  delay(3000);  
    
  //*********** Attempt DHCP *******************
  while(!sim808.join(F("gpinternet"))) {
      Serial.println("Sim808 join network error");
      delay(2000);
  }
  
//************ Successful DHCP ****************
  Serial.print("IP Address is ");
  Serial.println(sim808.getIPAddress());

   
}

void checkmytags() // compares each tag against the tag just read
{
  readBool=false;
  for(int z=0; z<14; ++z){
    s+=newtag[z];
  }
 char newChar[30];
 s.toCharArray(newChar, 30);
 s="";
  strcpy(http_cmd, "GET /log.php?rfid=");
  strcat(http_cmd, newChar);
  strcat(http_cmd,  " HTTP/1.0\r\n"
                    "Host: mce.asia\r\n"
                    "\r\n");
  Serial.println(http_cmd);

  //*********** Establish a TCP connection ************
  if(!sim808.connect(TCP,"mce.asia", 80)) {
      Serial.println("Connect error");
  }else{
      Serial.println("Connect mce.asia success");
  }

  //*********** Send a GET request *****************
  Serial.println("waiting to fetch...");
  sim808.send(http_cmd, sizeof(http_cmd)-1);
  while (true) {
      int ret = sim808.recv(buffer, sizeof(buffer)-1);
      if (ret <= 0){
          Serial.println("fetch over...");
          break; 
      }
      buffer[ret] = '\0';
      Serial.print("Recv: ");
      Serial.print(ret);
      Serial.print(" bytes: ");
      String s="";
      s+=buffer[ret-3];
      s+=buffer[ret-2];
      s+=buffer[ret-1];
      Serial.println(s);
      if(s.equalsIgnoreCase("yes")){
        digitalWrite(13, HIGH);
        readBool=true;
      }
      else{
        digitalWrite(13, LOW);
        readBool=true;
      }
      break;
  }

  //************* Close TCP or UDP connections **********
  sim808.close();

  //*** Disconnect wireless connection, Close Moving Scene *******


  
}
void readTags()
{
  ok = -1;
  if (Serial.available() > 0)
  {
    // read tag numbers
    delay(100); // needed to allow time for the data to come in from the serial buffer.
    for (int z = 0 ; z < 14 ; z++) // read the rest of the tag
    {
    data1 = Serial.read();
    newtag[z] = data1;
    }
    Serial.flush(); // stops multiple reads
    // do the tags match up?
    checkmytags();
  }
  // now do something based on tag type
  if (ok > 0) // if we had a match
  {
    Serial.println("Accepted");
    digitalWrite(yes, HIGH);
    delay(1000);
    digitalWrite(yes, LOW);
    ok = -1;
  }
  else if (ok == 0) // if we didn't have a match
  {
  Serial.println("Rejected");
  digitalWrite(no, HIGH);
  delay(1000);
  digitalWrite(no, LOW);
  ok = -1;
  }
}
void loop()
{if(readBool==true){
  readTags();
}
}
// ------------------------------------------------------------------------------------
