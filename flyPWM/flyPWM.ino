#include <WiFi.h>
#include <HTTPClient.h>

const char SSID[] = "POP'N STAR MASTER AP";
const char PASSWORD[] = "1234567890";
const char URL[] = "http://192.168.20.2/fly/val";

//WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //pwmGo(90);
  for(int i = 0;i < 100;i++) 
  {
    for(int j = 0;j < 10000;j++) pwmGo(i);
  }
}

void pwmGo(int per)
{
  digitalWrite(4,HIGH);
  for(int i = 0;i < 100-per;i++) digitalWrite(5,HIGH);
  for(int i = 0;i < per;i++) digitalWrite(5,LOW);
}

