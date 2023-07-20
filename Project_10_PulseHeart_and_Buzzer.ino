#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

int PulseWire = 0;
int pinBuzzer = 8;
int pinLEDred = 4;
int pinLEDgreen = 13;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  pinMode(pinBuzzer, OUTPUT);

  if(pulseSensor.begin()){
    Serial.println("Let's Started !");
  }
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int myBPM = pulseSensor.getBeatsPerMinute();

  if(pulseSensor.sawStartOfBeat()){
    Serial.print("BPM: ");
    Serial.println(myBPM);
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
  delay(20);

  
}
