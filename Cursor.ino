
// Rotary Encoder Inputs
#define CLK 11
#define DT 12
#define SW 13




int Cursor(){

  int btnState = digitalRead(SW);

  int counter = 0;
  int currentStateCLK;
  int lastStateCLK = digitalRead(CLK);
 

  while(1){//&& (millis() - lastButtonPress > 50)){

  currentStateCLK = digitalRead(CLK);
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
		if (digitalRead(DT) != currentStateCLK) {
			counter --;
		} else {
			counter ++;
		}
		Serial.println(counter);
	}

	lastStateCLK = currentStateCLK;

	// Read the button state
	int btnState = digitalRead(SW);
  //lastButtonPress = millis();
  if(btnState == LOW){
    break;
  }

	delay(1);
  }
  return counter;
}



void setup() {
        
	// Set encoder pins as inputs
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);

	// Setup Serial Monitor
	Serial.begin(9600);

	
}

void loop() {
        
int cu = Cursor();
Serial.print("the cu selected is: ");
Serial.println(cu);

delay(1000);
	
}