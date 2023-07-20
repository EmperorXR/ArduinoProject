#include <OneWire.h>
#include <DallasTemperature.h>

#define PIN_INPUT 3

OneWire ourWire(PIN_INPUT);

DallasTemperature sensors(&ourWire);

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("Temperature Sensors Test Program");
  Serial.println("Temperature Sensors DS18b20");
  delay(1000);
}

void loop() {
  Serial.println();
  Serial.print("Requesting Temperature...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  Serial.print("Device 1 (index 0) = ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" Degress C");
  Serial.print("Device 1 (index 0) = ");
  Serial.print(sensors.getTempFByIndex(0));
  Serial.println(" Degress F");
  delay(5000);
}
