/*
  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected
 
  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.
*/

#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "heartRate.h"

MAX30105 particleSensor;

#include <SoftwareSerial.h>
SoftwareSerial wifi(A1,A2);

#include <OneWire.h>
#include <DallasTemperature.h>

#define PIN_INPUT 3
OneWire ourWire(PIN_INPUT);
DallasTemperature sensor(&ourWire);

#define MAX_BRIGHTNESS 255

int Suhu;

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
//Arduino Uno doesn't have enough SRAM to store 50 samples of IR led data and red led data in 32-bit format
//To solve this problem, 16-bit MSB of the sampled data will be truncated. Samples become 16-bit data.
uint16_t irBuffer[50]; //infrared LED sensor data
uint16_t redBuffer[50];  //red LED sensor data
#else
uint32_t irBuffer[50]; //infrared LED sensor data
uint32_t redBuffer[50];  //red LED sensor data
#endif

int32_t Oxy; //SPO2 value
int8_t validOxy; //indicator to show if the SPO2 calculation is valid
int32_t BPM; //heart rate value
int8_t validBPM; //indicator to show if the heart rate calculation is valid

void setup()
{
  Serial.begin(115200); // initialize serial communication at 115200 bits per second:
  wifi.begin(115200);

  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  
  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println(F("MAX30105 was not found. Please check wiring/power."));
    while (1);
  }
  particleSensor.setup(55, 4, 2, 200, 411, 4096); //Configure sensor with these settings
}

void loop()
{
  sensor.requestTemperatures();
  Suhu = sensor.getTempCByIndex(0);
  //read the first 50 samples, and determine the signal range
  for (byte i = 0 ; i < 50 ; i++)
  {
    while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample(); //We're finished with this sample so move to next sample
    Serial.print(F("red="));
    Serial.print(redBuffer[i], DEC);
    Serial.print(F(", ir="));
    Serial.println(irBuffer[i], DEC);
  }

  //calculate heart rate and SpO2 after first 50 samples (first 4 seconds of samples)
  maxim_heart_rate_and_oxygen_saturation(irBuffer, 50, redBuffer, &Oxy, &validOxy, &BPM, &validBPM);
  
  //Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
  while (1)
  {
    //dumping the first 25 sets of samples in the memory and shift the last 25 sets of samples to the top
    for (byte i = 25; i < 50; i++)
    {
      redBuffer[i - 25] = redBuffer[i];
      irBuffer[i - 25] = irBuffer[i];
    }

    //take 25 sets of samples before calculating the heart rate.
    for (byte i = 25; i < 50; i++)
    {
      while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data
        digitalWrite(11, !digitalRead(11));

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample
      Serial.print(F("red="));
      Serial.print(redBuffer[i], DEC);
      Serial.print(F(", ir="));
      Serial.print(irBuffer[i], DEC);
      
      Serial.print(F(", HR="));
      Serial.print(BPM, DEC);

      Serial.print(F(", HRvalid="));
      Serial.print(validBPM, DEC);

      Serial.print(F(", SPO2="));
      Serial.print(Oxy, DEC);

      Serial.print(F(", SPO2Valid="));
      Serial.println(validOxy, DEC);

      Serial.print(F(", Suhu="));
      Serial.println(Suhu);
    }

    //After gathering 25 new samples recalculate HR and SP02
    maxim_heart_rate_and_oxygen_saturation(irBuffer, 50, redBuffer, &Oxy, &validOxy, &BPM, &validBPM);
    sendData();
  }
}

void sendData(){
  if(wifi.available() > 0){
    wifi.write(BPM);
    wifi.write(Oxy);
    wifi.write(Suhu);
  }
}
