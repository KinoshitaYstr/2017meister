#include <WiFi.h>
#include <HTTPClient.h>

const char SSID[] = "POP'N STAR MASTER AP";
const char PASSWORD[] = "1234567890";
const char URL_PWM[] = "http://192.168.20.2/fly/pwm/val";
const char URL_GO[] = "http://192.168.20.2/fly/go/val";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);

  WiFi.begin(SSID,PASSWORD);
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
  
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http;
  http.begin(URL_GO);
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
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      Serial.println("stop");
    }else if(val == '1') {
      http.begin(URL_PWM);
      httpCode = http.GET();
      Serial.printf("Response: %d", httpCode);
      Serial.println();
      if(httpCode == HTTP_CODE_OK) {
        body = http.getString();
        int pwmVal = 10*body.toInt();
        Serial.printf("pwm : %d",pwmVal);
        Serial.println();
        pwmGo(pwmVal);
      }
    }
  }
}

void pwmGo(int per)
{
  digitalWrite(4,HIGH);
  for(int i = 0;i < 100-per;i++) digitalWrite(5,HIGH);
  for(int i = 0;i < per;i++) digitalWrite(5,LOW);
}

