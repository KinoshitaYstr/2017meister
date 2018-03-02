#include <WiFi.h>

const char SSID[] = "POPN'STAR MASTER AP";
const char PASSWORD[] = "1234567890";

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
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    client.println("/note/H");
    client.stop();
  }
}

