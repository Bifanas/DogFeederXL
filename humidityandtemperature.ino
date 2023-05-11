#include <dht.h> //
#define dataPin 8
#define MAX_SIZE 10

dht DHT;

float temp[MAX_SIZE];
float hum[MAX_SIZE];
int index = 0;

void setup(){
  Serial.begin(9600);
  for(int i = 0; i < MAX_SIZE; i++) {
    temp[i] = 0.0;
    hum[i] = 0.0;
  }
}

void loop(){
  readAndPrintDHTData();
  delay(60000);
}

void readAndPrintDHTData() {
  int readData = DHT.read22(dataPin);
  float t = DHT.temperature;
  float h = DHT.humidity;

  temp[index] = t;
  hum[index] = h;

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print(" C | ");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" % ");
  Serial.println("");

  index = (index + 1) % MAX_SIZE;  // this will keep index in the range of 0 to MAX_SIZE-1
}
