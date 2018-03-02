#include <WiFi.h>
#include <HTTPClient.h>

int R_PIN = 4;

const char SSID[] = "POPN'STAR MASTER AP";
const char PASSWORD[] = "1234567890";
const char URL[] = "http://192.168.20.2/note/H";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
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
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(R_PIN);
  Serial.println(val);
  delay(100);
  /*
  if(val < 100) {
    HTTPClient http;
    http.begin(URL);
    int httpCode = http.GET();
    Serial.printf("Response: %d", httpCode);
    Serial.println();
    http.end();
  }
  */
}
