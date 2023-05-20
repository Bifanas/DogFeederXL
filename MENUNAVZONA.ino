#include <Wire.h>               // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for LCD
#include <LcdMenu.h>

#define TIMEOUT_COUNT 100 // tempo max até voltar automaticamente pra tela main

LiquidCrystal_I2C lcd(0x27, 16, 4);

int switchPin = 13;      // button pin KEY
int click = HIGH;  // button value

int pinA = 12;                         // Rotary encoder Pin S1
int pinB = 11;                         // Rotary encoder Pin S2
int pinAstateCurrent = LOW;            // Current state of Pin S1
int pinAStateLast = pinAstateCurrent;  // Last read value of Pin S2

int st=0; //setting state 0 - main screen state

bool refresh_screen=true; // impede q fique printando a tela 900x até ir pra proxima (NÃO FICA PISCANDO
)

int aux = 0;
int encoder = 0;

int timer = 0; // pra contar o num de ciclos até voltar pra tela inicial

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";

void setup() {

  Serial.begin(9600);  // Initialise the serial monitor

  pinMode(switchPin, INPUT_PULLUP);  // Enable the switchPin as input with a PULLUP resistor

  pinMode(pinA, INPUT);  // Set PinA as input
  pinMode(pinB, INPUT);  // Set PinB as input

  lcd.init();
  lcd.setBacklight(HIGH);

}

void loop() {

  /*
  ###################
  ## Input Capture ##
  ###################
  */

  // BUTTON
  click = digitalRead(switchPin);  // Read the digital value of the switch (LOW/HIGH)
  // If the switch is pressed (LOW), print message

  // ROTATION DIRECTION
  // int read_encoder();
  //     return 0 se ninguem mexer no encoder
  //     return 1 se encoder girar para direita
  //     return -1 se encoder girar para esquerda

  encoder = read_encoder();


  // pinAstateCurrent = digitalRead(pinA);  // Read the current state of S1
  // if ((pinAStateLast == LOW) && (pinAstateCurrent == HIGH)) {
  //   if (digitalRead(pinB) == HIGH) {  // If Pin B is HIGH
  //     aux++;
  //     if (aux > 3) aux = 0;  // Print on screen
  //     encoderV=1;
  //   } else {
  //     aux--;
  //     if (aux < 0) aux = 3;  // Print on screen
  //     encoderV=-1;
  //     // Serial.println("left");
  //   }
  //   //Serial.println(aux);
  //   //delay(5000);
  // }
  // pinAStateLast = pinAstateCurrent;  // Store the latest read value in the currect state variable

  /*
  #######################
  ## End Input Capture ##
  #######################
  */
  
  // Serial.println("oi tamo no loop");
  // Serial.print("Click: "); Serial.println(click);



  Serial.print("Rotation: "); //Serial.println(pinAstateCurrent);
  switch(encoder){
    case 0:
      Serial.println("0");
    break;
    case 1:
      Serial.println("right");
    break;
    case -1:
      Serial.println("left");
    break;
  }


  // Serial.print("Timer: "); Serial.println(timer);

  /*
  ###################
  ## State Machine ##
  ###################
  */

  switch(st){
    case 0: // main screen 
      // Serial.println("main(st=0)");
      if (refresh_screen) {
        Home_screen();
        refresh_screen=false;
      }
      if (click==LOW){
        st=1;
        refresh_screen=true;
      }
      timer = 0;
      //delay(50);
      break;
    case 1: // settings screen
      // Serial.println("settings(st=1)");
      if (refresh_screen) {
        Settings_screen();
        refresh_screen=false;
        timer = 0;
      }
      
      if(click==LOW){
        st=0;
        refresh_screen=true;
      }
      else{
        if(timer>=TIMEOUT_COUNT){
          st = 0;
          refresh_screen=true;
        }
      }
      break;
    
  }

  /*
  #######################
  ## End State Machine ##
  #######################
  */

  delay(15);

  timer++;


}


int read_encoder(void){
  int currentDir = 0;
  currentStateCLK = digitalRead(pinA);


	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(pinB) != currentStateCLK) {
			// counter --;
      currentDir = -1;
			// currentDir ="CCW";
		} else {
			// Encoder is rotating CW so increment
			// counter ++;
      currentDir = 1;
			// currentDir ="CW";
		}

		// Serial.print("Direction: ");
		// Serial.print(currentDir);
		// Serial.print(" | Counter: ");
		// Serial.println(counter);
    return currentDir;
	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;
}

// CURSOR NAVIGATION ===============================================

// int Cursor_nav(int n) {
//   int aux = 0;
 
//     // If there is a minimal movement of 1 step
//     if ((pinAStateLast == LOW) && (pinAstateCurrent == HIGH)) {
//       if (digitalRead(pinB) == HIGH) {  // If Pin B is HIGH
//         aux++;
//         if (aux > n) aux = 0;  // Print on screen
//       } else {
//         aux--;
//         if (aux < 0) aux = n;  // Print on screen
//       }
//       Serial.println(aux);

//       lcd.setCursor(0, 0);
//       lcd.print("  ");
//       lcd.setCursor(0, 1);
//       lcd.print("  ");
//       lcd.setCursor(0, 2);
//       lcd.print("  ");
//       lcd.setCursor(0, 3);
//       lcd.print("  ");


//       lcd.setCursor(0, aux);
//       lcd.print("->");
//     }
//     pinAStateLast = pinAstateCurrent;  // Store the latest read value in the currect state variable
  

//   return aux;
// }

// MAIN SCREEN +++++++++++++++++++++++++++++++++++++++++++++++

void Home_screen(void) {

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("20/04/2023");
  lcd.setCursor(1, 1);
  lcd.print("14:00");
  lcd.setCursor(1, 2);
  lcd.print("Next meal: 16:30 ");
  // delay(100);
  //NÂO POE DELAY AQUI PRA NAO Ferrar  COM NOIS 

}// END MAIN SCREEN

// SETTINGS SCREEN +++++++++++++++++++++++++++++++++++++++++++++++
void Settings_screen(void) {
  int curs=0;
    
  lcd.clear();
  lcd.setCursor(12,0);  // HEADER ----------------------------------
  lcd.print("Settings");
  lcd.setCursor(2,0);  // Treat --------------------------------
  lcd.print("Treat");
  lcd.setCursor(2,1);  // SCHEDULE --------------------------------
  lcd.print("Schedule");
  lcd.setCursor(2, 2);  // CALIBRATE------------------------------
  lcd.print("Calibrate");
  lcd.setCursor(2, 3);  // SOUND ---------------------------------
  lcd.print("Sound");
      
  //curs=Cursor_nav(3);
  // delay(100);
      
  /*lcd.setCursor(12,0);  // HEADER ----------------------------------
  lcd.print("Settings");

  lcd.setCursor(2, 0);  // HISTORY -------------------------------
  lcd.print("History");
  */     
}      
    