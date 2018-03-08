#include <WiFi.h>
#include <HTTPClient.h>

const char SSID[] = "POP'N STAR MASTER AP";
const char PASSWORD[] = "1234567890";
const char URL_R[] = "http://192.168.20.2/doll/R/val";
const char URL_L[] = "http://192.168.20.2/doll/L/val";

boolean conditionR = false;
boolean conditionL = false;

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(26,OUTPUT);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(26,HIGH);
  digitalWrite(14,HIGH);

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
  HTTPClient httpR;
  HTTPClient httpL;
  String body;
  char val;
  httpR.begin(URL_R);
  httpL.begin(URL_L);
  int httpCodeR = httpR.GET();
  Serial.printf("Response R: %d", httpCodeR);
  Serial.println();
  int httpCodeL = httpL.GET();
  Serial.printf("Response L: %d", httpCodeL);
  Serial.println();
  if(httpCodeR == HTTP_CODE_OK){
    body = httpR.getString();
    Serial.print("Response Body R: ");
    Serial.println(body);
    val = body[0];
    Serial.println(val);
    if(val == '0') conditionR = false;
    else conditionR = true;
  }
  if(httpCodeL == HTTP_CODE_OK){
    body = httpL.getString();
    Serial.print("Response Body L: ");
    Serial.println(body);
    val = body[0];
    Serial.println(val);
    if(val == '0') conditionL = false;
    else conditionL = true;
  }
  httpR.end();
  httpL.end();
  delay(100);
}


