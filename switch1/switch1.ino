#include <WiFi.h>
#include <HTTPClient.h>

int R_PIN = 4;
int count = 0;

const char SSID[] = "POP'N STAR MASTER AP";
const char PASSWORD[] = "1234567890";
const char URL[] = "http://192.168.20.2/note/H";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  
  delay(1000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(R_PIN);
  Serial.println(val);
  Serial.println(count);
  
  if(val < 1000) {
    count++;
    while(analogRead(R_PIN) < 1000);

    if(count > 5) {
      HTTPClient http;

      WiFi.begin(SSID, PASSWORD);
      Serial.print("WiFi connecting");
    
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
      }
    
      Serial.println(" connected");
    
      server.begin();
    
      Serial.print("HTTP Server: http://");
      Serial.print(WiFi.localIP());
      Serial.println("/");
      
      http.begin(URL);
      int httpCode = http.GET();
      Serial.printf("Response: %d", httpCode);
      Serial.println();
      http.end();
    }
    
  }
  delay(100);
}
