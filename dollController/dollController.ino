#include <WiFi.h>
#include <HTTPClient.h>

const char SSID[] = "POP'N STAR MASTER AP";
const char PASSWORD[] = "1234567890";
const char URL[] = "http://192.168.20.2/doll/val";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  pinMode(16,OUTPUT);
  digitalWrite(4,HIGH);
  digitalWrite(16,HIGH);

  Serial.begin(115200);
  while (!Serial);

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
  Serial.println("---------------------------------");
  HTTPClient http;
  http.begin(URL);
  int httpCode = http.GET();
  Serial.printf("Response: %d", httpCode);
  Serial.println();
  if (httpCode == HTTP_CODE_OK) {
    String body = http.getString();
    Serial.print("Response Body: ");
    Serial.println(body);
    char val = body[0];
    Serial.println(val);
    if(val == '0') {
      Serial.println("stop");
      digitalWrite(4,HIGH);
      digitalWrite(16,HIGH);
    }else if(val == '1') {
      Serial.println("start");
      digitalWrite(4,HIGH);
      digitalWrite(16,LOW);
    }
    Serial.println("---------------------------------");
  }
  http.end();
  delay(100);
}


