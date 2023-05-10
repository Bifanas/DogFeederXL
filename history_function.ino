
void History(int, float, float []);


void setup() {

  Serial.begin(9600);
  

  // put your setup code here, to run once:
}

int aux = 0;
const int arraySize = 16;
int cu[arraySize];                    // = { 220, 232, 123, 234, 345, 321, 121, 321, 123, 123, 321, 123, 123, 321, 321, 321 };
  

void loop() {
  
  /*
  for (int i = 0; i < 16; i++) {
    cu[i] = aux++;
  }*/
  aux++;
  History(aux, arraySize, cu);



  for (int i = 0; i < 16; i++) {
    Serial.print(" | ");
    Serial.print(cu[i]);
    Serial.print(" | ");
  }
  Serial.println();
  Serial.print("-------------------------------------------------------------------------------------------------------------------------");
  Serial.println();
  delay(1000);
  // put your main code here, to run repeatedly:
}

void History (int latest, int arraySize, int old[] ){
  for (int i = 0; i < arraySize; ++i) {
    old[ i ] = old[ i + 1 ];
  }
  old[16] = latest;
}

