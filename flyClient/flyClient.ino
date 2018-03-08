#include <WiFi.h>
#include <HTTPClient.h>

const char SSID[] = "POP'N STAR MASTER AP";
const char PASSWORD[] = "1234567890";
const char URL[] = "http://192.168.20.2/fly/val";

char val = '0';

WiFiServer server(80);

void setup() {
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
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  Serial.println("---------------------------------");
  Serial.println(val);
  if(val == '0') {
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    Serial.println("stop");
  }else if(val == '1') {
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    Serial.println("start");
  }
  HTTPClient http;
  http.begin(URL);
  int httpCode = http.GET();
  Serial.printf("Response: %d", httpCode);
  Serial.println();
  if (httpCode == HTTP_CODE_OK) {
    String body = http.getString();
    Serial.print("Response Body: ");
    Serial.println(body);
    val = body[0];
    Serial.println(val);
    Serial.println("---------------------------------");
  }
  http.end();
  //digitalWrite(4,HIGH);
  //digitalWrite(5,HIGH);
  delay(100);
}
