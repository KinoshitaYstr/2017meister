#include <WiFi.h>

WiFiServer server(80);

const char ssid[] = "POPN'STAR ACCESS POINT";
const char pass[] = "1234567890";

const IPAddress ip(192, 168, 20, 2);
const IPAddress subnet(255, 255, 255, 0);

void setup() {
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
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println(currentLine);
            Serial.println("------");
            Serial.println(currentLine);
            Serial.println("------");
            client.println();
            currentLine = "";
          }
        }else if(c != '\r') {
          currentLine += c;
        } 
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(4, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(4, LOW);                // GET /L turns the LED off
        }       
      }
    }
    client.stop();
    Serial.println("client disonnected");
  }
}
