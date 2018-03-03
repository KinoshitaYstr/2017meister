#include <WiFi.h>

WiFiServer server(80);

const char ssid[] = "POP'N STAR MASTER AP";  // SSID
const char pass[] = "1234567890";   // password

const IPAddress ip(192, 168, 20, 2);      // IPアドレス
const IPAddress subnet(255, 255, 255, 0); // サブネットマスク

boolean noteFlag = false;
boolean dollFlag = false;

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, pass);           // SSIDとパスの設定
  delay(100);                        // 追記：このdelayを入れないと失敗する場合がある
  WiFi.softAPConfig(ip, ip, subnet); // IPアドレス、ゲートウェイ、サブネットマスクの設定
  
  IPAddress myIP = WiFi.softAPIP();  // WiFi.softAPIP()でWiFi起動
  server.begin();                    // サーバーを起動(htmlを表示させるため)

  /* 各種情報を表示 */
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("Server start!");
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    String currentLine = "";
    char c;
    Serial.println("new client!");

    while(client.connected()) {
      if (client.available()) { 
        c = client.read();
        //Serial.write(c);
        if(c == '\n') {
          if (currentLine.length() == 0) {
            break;
          } else {
            Serial.println("-------------------------------");
            Serial.println(currentLine);
            if(currentLine.startsWith("GET /all/H")) {
              dollFlag = true;
              noteFlag = true;
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println("set all");
            }else if(currentLine.startsWith("GET /all/L")) {
              dollFlag = false;
              noteFlag = false;
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println("reset all");
            }else if(currentLine.startsWith("GET /note/val")) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println(noteFlag);
            }else if(currentLine.startsWith("GET /note/H")) {
              noteFlag = true;
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println("set note");
            }else if(currentLine.startsWith("GET /note/L")) {
              noteFlag = false;
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println("reset note");
            }else if(currentLine.startsWith("GET /doll/val")) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println(dollFlag);
            }else if(currentLine.startsWith("GET /doll/H")) {
              dollFlag = true;
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println("set doll");
            }else if(currentLine.startsWith("GET /doll/L")) {
              dollFlag = false;
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println("reset doll");
            }
            Serial.println("-------------------------------");
            currentLine = "";
          }
        }else if(c != '\r') {
          currentLine += c;
        }
      }
    }
    // 接続が切れた場合
    client.stop();
    Serial.println("client disonnected");
  }
}
