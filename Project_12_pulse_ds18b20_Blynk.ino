#define USE_ARDUINO_INTERRUPTS true
#define BLYNK_PRINT Serial

#include<ESP8266WiFi.h>
char ssid[] = "KhunC2";
char password[] = "khunedahn";

#include<BlynkSimpleEsp8266.h>
char auth[] = "gO9EUXAefOQe4eHdqKxzC0wDGUHih6Lw";

#include<PulseSensorPlayground.h>
int PulseWire = 0;
int pinBuzzer = 8;
int pinLEDgreen = 13;
int pinLEDred = 4;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

#include <OneWire.h>
#include <DallasTemperature.h>

#define PIN_INPUT 3
OneWire ourWire(PIN_INPUT);

DallasTemperature ds18b20(&ourWire);

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("Monitoring Detak Jantung Program");
  Serial.println("Temperature Sensors DS18B20");
  delay(1000);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  pinMode(pinBuzzer, OUTPUT);

  Blynk.begin(auth, ssid, password);
  if(pulseSensor.begin()){
    Serial.println("Let's Started");
  }
  delay(1000);
}

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute();

  if(pulseSensor.sawStartOfBeat()){
    Serial.print("BPM : ");
    Serial.println(myBPM);
    Serial.print("Suhu = ");
    Serial.print(ds18b20.getTempCByIndex(0));
    Serial.print(" Celcius");
    delay(200);
    if(myBPM > 0){
      digitalWrite(pinBuzzer, HIGH);
      digitalWrite(pinLEDgreen, HIGH);
      delay(200);
      digitalWrite(pinBuzzer, LOW);
      digitalWrite(pinLEDgreen, LOW);
      delay(200);
      if(myBPM > 100){
        digitalWrite(pinBuzzer, HIGH);
        digitalWrite(pinLEDred, HIGH);
        delay(500);
        digitalWrite(pinBuzzer, LOW);
        digitalWrite(pinLEDred, LOW);
        delay(500);
      }
    }
  }
  Blynk.run();
}
