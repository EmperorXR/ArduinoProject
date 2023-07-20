#include <ESP8266WiFi.h>
#include <WifiClientSecure.h>
#include <TelegramBot.h>

#define LED 13

const char* ssid = "Khun";
const char* password = "khunedahn";

const char BotToken[] = "976262732:AAHkmmg4kDmKCn0feEfbFCOnYghmyiHOsu8;

WifiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);

void setup() {
  Serial.begin(115200);
  while (!Serial) {} // Start Running when the serial is open
  delay(3000);
  Serial.print("Connecting Wifi...");
  Serial.println(ssid);
  while (WiFi.begin(ssid, password) != WL_CONNECTED)
  {
    Serial.print(",");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  bot.begin();
  pinMode(LED, OUTPUT);
}

void loop() {
  message m = bot.getUpdates(); // Read New Message
  if (m.text.equals("on"))
  {
    digitalWrite(LED, 1);
    bot.sendMessage(m.chat_id, "LED is ON");
    Serial.println("LED is ON");
  }
  else if (m.text.equals("off"))
  {
    digitalWrite(LED, 0);
    bot.sendMessage(m.chat_id, "LED is OFF");
    Serial.println("LED is OFF");
  }
}
