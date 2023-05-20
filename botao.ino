//Arduino Code - Rotary Encoder w push button

#include <BfButton.h>

int Key=10; //pressao
int S1=9; // 
int S2=6; // 
BfButton btn(BfButton::STANDALONE_DIGITAL, Key, true, LOW);

int counter = 0;
int angle = 0; 
int aState;
int aLastState;  

//Button press hanlding function
void pressHandler (BfButton *btn, BfButton::press_pattern_t pattern) {
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println("ENTER");
      break;
      
    case BfButton::DOUBLE_PRESS:
      Serial.println("BACK");
      break;
      
    case BfButton::LONG_PRESS:
      Serial.println("MENU");
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(angle);
  pinMode(S2,INPUT_PULLUP);
  pinMode(S1,INPUT_PULLUP);
  aLastState = digitalRead(S2);

  //Button settings
  btn.onPress(pressHandler)
  .onDoublePress(pressHandler) // default timeout
  .onPressFor(pressHandler, 1000); // custom timeout for 1 second
}

void loop() {
  // put your main code here, to run repeatedly:

  //Wait for button press to execute commands
  btn.read();
  
  aState = digitalRead(S2);

  //Encoder rotation tracking
  if (aState != aLastState){     
     if (digitalRead(S1) != aState) { 
       Serial.println("DOWN");
              
                     }
     else {
       Serial.println("UP");
         
     }
  
  }   
  aLastState = aState;
}