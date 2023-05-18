#include <Wire.h>               // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for LCD
LiquidCrystal_I2C lcd(0x27, 16, 4);




int switchPin = 13;      // button pin
int switchState = HIGH;  // button value

int pinA = 12;                         // Rotary encoder Pin A
int pinB = 11;                         // Rotary encoder Pin B
int pinAstateCurrent = LOW;            // Current state of Pin A
int pinAStateLast = pinAstateCurrent;  // Last read value of Pin A

//int menucounter=0; //counts the clicks of encoder button 

int Cursor_nav() {
  int aux = 0;

  while (1) {
    // BUTTON
    switchState = digitalRead(switchPin);  // Read the digital value of the switch (LOW/HIGH)
    // If the switch is pressed (LOW), print message
    if (switchState == LOW) {
      break;
    }

    // ROTATION DIRECTION
    pinAstateCurrent = digitalRead(pinA);  // Read the current state of Pin A

    // If there is a minimal movement of 1 step
    if ((pinAStateLast == LOW) && (pinAstateCurrent == HIGH)) {
      if (digitalRead(pinB) == HIGH) {  // If Pin B is HIGH
        aux++;
        if (aux > 3) aux = 0;  // Print on screen
      } else {
        aux--;
        if (aux < 0) aux = 3;  // Print on screen
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


      lcd.setCursor(0, aux);
      lcd.print("->");
    }
    pinAStateLast = pinAstateCurrent;  // Store the latest read value in the currect state variable
  }

  return aux;
}

void setup() {
  Serial.begin(9600);  // Initialise the serial monitor

  pinMode(switchPin, INPUT_PULLUP);  // Enable the switchPin as input with a PULLUP resistor

  pinMode(pinA, INPUT);  // Set PinA as input
  pinMode(pinB, INPUT);  // Set PinB as input

  lcd.init();
  lcd.setBacklight(HIGH);

 
  


  
}


void loop() {

  // BUTTON
  switchState = digitalRead(switchPin);  // Read the digital value of the switch (LOW/HIGH)
  // If the switch is pressed (LOW), print message

  // HOME SCREEN
  lcd.setCursor(1, 0);
  lcd.print("20/04/2023");
  lcd.setCursor(1, 1);
  lcd.print("14:00");
  lcd.setCursor(1, 2);
  lcd.print("Next meal: 16:30 ");
  delay(50); // END HOMESCREEEn

    if (switchState == LOW) {
      Settings_screen();
      delay(2000);
    }
  
  
  
  delay(100);
}

/*
void Home_screen(void) {

  lcd.clear();


  // DATE ---------------------------------------
  lcd.setCursor(1, 0);
  lcd.print("20/04/2023");

  //lcd.print(clock.day);
  //lcd.print("/");
  //lcd.print(clock.month);
  //lcd.print("/");
  //lcd.print(clock.year);

  // CURENT TIME -------------------------------
  lcd.setCursor(1, 1);

  lcd.print("14:00");

  //lcd.print(clock.hours);
  //lcd.print(":");
  //lcd.print(clock.minutes);


  // NEXT MEAL TIME --------------------------
  lcd.setCursor(1, 2);
  lcd.print("Next meal: 16:30 ");

  //lcd.print(next_meal(hour));
  //lcd.print(":");
  //lcd.print(next_meal(minute));

  /* lcd.setCursor(6, 55);
  lcd.print("20");  // storage()/Mealsize()
  lcd.print(" []");

  lcd.setCursor(52, 55);  // HUMIDITY INSIDE THE RESIVOIR -----------
  lcd.print("20");        // Humidity()
  lcd.print(" %");

  lcd.setCursor(95, 55);  // TEMPERATURE INSIDE THE RESIVOIR --------
  lcd.print("20");
  lcd.print(" ");
  lcd.write(0xF7);
  lcd.print("C");
  
  delay(50);
}
*/
  void Settings_screen(void) {
    int curs=0;
    lcd.clear();
    while(1){
       
    
    
    
    lcd.setCursor(2,0);  // HEADER ----------------------------------
    lcd.print("Settings: ");

    lcd.setCursor(2,1);  // SCHEDULE --------------------------------
    lcd.print("Schedule");


    lcd.setCursor(2, 2);  // CALIBRATE------------------------------
    lcd.print("Calibrate");

    lcd.setCursor(2, 3);  // SOUND ---------------------------------
    lcd.print("Sound");

    curs=Cursor_nav();
    delay(10);
    }

   // lcd.setCursor(15, 55);  // HISTORY -------------------------------
   // lcd.print("History");

    
  }

