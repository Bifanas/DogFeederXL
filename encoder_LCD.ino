
#include <Wire.h>               // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for LCD
LiquidCrystal_I2C lcd(0x27, 16, 4);


 

int switchPin = 13;                        // button pin
int switchState = HIGH;                    // button value

int pinA = 12;                              // Rotary encoder Pin A
int pinB = 11;                              // Rotary encoder Pin B
int pinAstateCurrent = LOW;                // Current state of Pin A
int pinAStateLast = pinAstateCurrent;      // Last read value of Pin A


int  Cursor_nav(){
    int aux=0;
    
  while(1){
  // BUTTON
  switchState = digitalRead(switchPin);    // Read the digital value of the switch (LOW/HIGH)
  // If the switch is pressed (LOW), print message
  if (switchState == LOW) {
      break;
  }  

  // ROTATION DIRECTION
  pinAstateCurrent = digitalRead(pinA);    // Read the current state of Pin A
  
  // If there is a minimal movement of 1 step
  if ((pinAStateLast == LOW) && (pinAstateCurrent == HIGH)) {    
    if (digitalRead(pinB) == HIGH) {      // If Pin B is HIGH
      aux--; 
      if(aux < 0 ) aux=3;             // Print on screen
    } else {
      aux++;
      if(aux > 3) aux=0;          // Print on screen
    }
    Serial.println(aux);

    lcd.setCursor(0, 0);
    lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print("  ");
    lcd.setCursor(0, 2);
    lcd.print("  ");
    lcd.setCursor(0, 3);
    lcd.print("  ");


    lcd.setCursor(0,aux);
    lcd.print("->");
  }  
  pinAStateLast = pinAstateCurrent;        // Store the latest read value in the currect state variable
  }

  return aux;
}

void setup() {
  Serial.begin (9600);                     // Initialise the serial monitor

  pinMode (switchPin, INPUT_PULLUP);       // Enable the switchPin as input with a PULLUP resistor
  
  pinMode (pinA, INPUT);                   // Set PinA as input
  pinMode (pinB, INPUT);                   // Set PinB as input

  lcd.init();
  lcd.setBacklight(HIGH);

  lcd.setCursor(3, 0);
  lcd.print(1);
  lcd.setCursor(3, 1);
  lcd.print(2);
  lcd.setCursor(3, 2);
  lcd.print(3);
  lcd.setCursor(3, 3);
  lcd.print(4);
  
}

void loop() {

  int cu = Cursor_nav();

  lcd.setCursor(6, 1);
  lcd.print("cu: ");
  lcd.print(cu+1);
  Serial.print("the cu selected is: ");
  Serial.println(cu);
 

  delay(1000);


}