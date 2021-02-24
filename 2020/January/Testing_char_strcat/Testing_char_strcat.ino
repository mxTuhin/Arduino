
char http_cmd[] = "GET /h.php?lat=23.45&long=99.45 HTTP/1.0\r\n"
                  "Host: mce.asia\r\n"
                  "\r\n";


char con[100];
char http_con[100]="GET /h.php?lat=";
float latitude=23.666054;
float longitude=90.480039;
char devID[10]="GH9IG5D6";



void setup() {
//  sprintf(con,"GET /h.php?lat=%d.%02d$lon=",(int)latitude, (int)(latitude*1000)%1000);
dtostrf(latitude, 2, 6, con);
strcat(http_con, con);
strcat(http_con, "&lon=");
dtostrf(longitude, 2, 6, con);
strcat(http_con, con);
strcat(http_con, "&devID=");
strcat(http_con, devID);
strcat(http_con,  " HTTP/1.0\r\n"
                  "Host: mce.asia\r\n"
                  "\r\n");





  Serial.begin(9600);
  Serial.println(http_con); 
  Serial.println(strlen(http_con)); 
  
}

void loop() {
}
