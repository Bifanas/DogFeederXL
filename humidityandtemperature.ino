#include <dht.h>
#define dataPin 8

dht DHT;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temperature, humidity;
  readDHTData(temperature, humidity);
  printDHTData(temperature, humidity);
  delay(5000);
}

void readDHTData(float& temperature, float& humidity) {
  int readData = DHT.read22(dataPin);
  temperature = DHT.temperature;
  humidity = DHT.humidity;
}

void printDHTData(float temperature, float humidity) {
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print(" C | ");
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" % ");
  Serial.println("");
}
