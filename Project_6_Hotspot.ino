#include <ESP8266WiFi.h>

const char* ssid = "khunnet.com";
const char* password = "1234567890";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  //Mengatur WiFi
  Serial.println();
  Serial.print("Configuring Acces Point");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  //Start the Server
  server.begin();
  Serial.println("Server Dijalankan");

  //Print the IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
