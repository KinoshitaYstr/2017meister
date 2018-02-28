#include <WiFi.h>

WiFiServer server(80);

const char ssid[] = "POPN'STAR MASTER AP";
const char pass[] = "1234567890";

const IPAddress ip(192, 168, 20, 2);
const IPAddress subnet(255, 255, 255, 0);

boolean note1 = false;

void setup() {
  int i = 0;
  Serial.begin(115200);

  WiFi.softAP(ssid, pass);
  delay(100);
  WiFi.softAPConfig(ip, ip, subnet);
  
  IPAddress myIP = WiFi.softAPIP();
  server.begin();

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("Server start!");

  pinMode(4, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    String currentLine = "";
    Serial.println("new client!");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if(c == '\n') {
          if (currentLine.length() == 0) {
            break;
          }else{
            Serial.println("------");
            Serial.println(currentLine);
            Serial.println("------");
            currentLine = "";
          }
        }else if(c != '\r') {
          currentLine += c;
        }
        if (currentLine == "GET /note/H") {
          client.println(currentLine);
          note1 = true;
        }
        if (currentLine.endsWith("GET /note/L")) {
          client.println(currentLine);
          note1 = false;
        }
        if(currentLine.endsWith("GET /note/val")) {
          client.println(note1);
        }
      }
    }
    client.stop();
    Serial.println("client disonnected");
  }
}
