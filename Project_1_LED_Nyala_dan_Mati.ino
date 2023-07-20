int led = 13;
char val;

void setup() {

  pinMode(led, OUTPUT); //Pin 13 sebagai OUTPUT
  Serial.begin(9600); //Kecepatan Transfer Arduino Uno
}

void loop() {

  if(Serial.available() > 0) //Kondisi
  {
    val = Serial.read(); //Membaca Variable
    Serial.println(val);
  }

  if(val == '1')
  {
    digitalWrite(led, HIGH); //Fungsi Nyala Lampu
    Serial.println("Lampu Menyala");
    delay(500); //Delay Waktu
  }

  if(val == '0')
  {
    digitalWrite(led, LOW); //Fungsi Mati Lampu
    Serial.println("Lampu Mati");
    delay(500); //Delay Waktu
  }
}
