#include "CTBot.h"
CTBot myBot;

String ssid = "KhunC2";
String pass = "khunedahn";
String token = "976262732:AAHkmmg4kDmKCn0feEFbFCOnYghmyiHOsu8";
const int id = 960603871;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting TelegramBot..");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if(myBot.testConnection()){
    Serial.println("Koneksi Berhasil");
  }else{
    Serial.println("Koneksi Gagal");
  }

  myBot.sendMessage(id, "NodeMCU On");
  Serial.println("Pesan Terkirim");
}

void loop() {

}
