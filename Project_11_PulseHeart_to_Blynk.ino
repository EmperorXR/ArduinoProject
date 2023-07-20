#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Connect to WiFi
char* ssid[] = "Khun" ;
char* password[] = "khunedahn" ;

//Connect to Blynk
char auth[] = "gO9EUXAefOQe4eHdqKxzC0wDGUHih6Lw" ;

//Variable Pulse Sensor
const int PulseWire = 0; //Pin 0
const int LED13 = 13;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Blynk.begin(auth, ssid, password);

 Blynk.begin(auth,ssid,password, IPAddress(192.168.43.11),8080);

 pulseSensor.analogInput(PulseWire);
 pulseSensor.blinkOnPulse(LED13);
 pulseSensor.setThreshold(Threshold);
}

void loop() {
  // put your main code here, to run repeatedly:
 int myBPM = pulseSensor.getBeatsPerMinute();
}
