// ALL INCLUDES HERE
#include <virtuabotixRTC.h>

#include <Wire.h>               // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for LCD

#include "pitches.h"

#include "HX711.h"

// ALL DEFINES HERE


// ALL CONSTS HERE

// 




//screen --------------------------------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 4);// SCREEN TESTE

//sound------------------------------------------------------------
const int BUZZER_PIN = 0;

int melody[] = {
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4,
  NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4,
  NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
  NOTE_A4
};

int durations[] = {
  8, 8, 4, 4,
  8, 8, 4, 4,
  8, 8, 4, 4,
  2
};

// potentiometer----------------------------------------------------

int pot;
int amount;

//humidity----------------------------------------------------------

//temperature----------------------------------------------------------

//Load cell----------------------------------------------------------
//#include "HX711.h"
#define calibration_factor 104400
#define system_weight -4.600
#define DOUT 3
#define CLK 2


HX711 scale;

//button------------------------------------------------------------
const int buttom_1 = 13;
const int buttom_2 = 12;
const int buttom_3 = 11;
const int buttom_4 = 10;

//Real Time Clock Object--------------------------------------------
virtuabotixRTC clock(6, 7, 8);

//Stepper motor-----------------------------------------------------
const int screw = 4;
const int dirPin = 5;
const int Sleepmotor = 9;

const int calibrou = 50;

//FUNCTIONS========================================================

//History-------------------------------------------------
void History(int latest, int arraySize, int old[]) {
  for (int i = 0; i < arraySize; ++i) {
    old[i] = old[i + 1];
  }
  old[16] = latest;
}

//LOAD CELL STORAGE------------------------------------------------
float storage() {  // returns how much food is in the system
  float aux = scale.get_units() - system_weight;
  return aux * 1000;
}

//------------------------------------------------------------------

void ring(int repeat) {
  for (int i = 0; i <= repeat; i++) {
    int size = sizeof(durations) / sizeof(int);

    for (int note = 0; note < size; note++) {
      //to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int duration = 1000 / durations[note];
      tone(BUZZER_PIN, melody[note], duration);

      //to distinguish the notes, set a minimum time between them.
      //the note's duration + 30% seems to work well:
      int pauseBetweenNotes = duration * 1.30;
      delay(pauseBetweenNotes);

      //stop the tone playing:
      noTone(BUZZER_PIN);
    }
  }
}


//Auxiliar function to set portion size with potentiomenter---------

int quantity(int pot) {  // outputValue = map(sensorValue, 0, 1023, 0, 255);
  int amount;            //0 to 1017

  if (pot >= 0 && pot < 100) { amount = 50; }
  if (pot >= 100 && pot < 200) { amount = 100; }
  if (pot >= 200 && pot < 300) { amount = 150; }
  if (pot >= 300 && pot < 400) { amount = 200; }
  if (pot >= 400 && pot < 500) { amount = 250; }
  if (pot >= 500 && pot < 600) { amount = 300; }
  if (pot >= 600 && pot < 700) { amount = 350; }
  if (pot >= 700 && pot < 800) { amount = 400; }
  if (pot >= 800 && pot < 900) { amount = 450; }
  if (pot >= 900 && pot < 1100) { amount = 500; }

  return amount;
}


//controls how many turns the motor will turn-----------------------
void stepper(float Screw_turns, int motorpin, bool direction) { 
  digitalWrite(Sleepmotor, HIGH);
  int steps = Screw_turns * 4000;  // 4000 = volta completa
  digitalWrite(dirPin, direction);
  for (int x = 0; x < steps; x++) {
    digitalWrite(motorpin, HIGH);
    delayMicroseconds(830);  //NEEDS TO BE CALIBRATED 830
    digitalWrite(motorpin, LOW);
    delayMicroseconds(830);
  }
  digitalWrite(Sleepmotor, LOW);
}

//Final function that feeds ---------------------------------------
void feed( int cal,int amount, bool slow) {
  float turns;
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Started");
  lcd.print("   Cal:");
  lcd.print(cal);

  turns = (0.5);  //50/cal;
  lcd.setCursor(1, 1);
  lcd.print("turns: ");
  lcd.print(turns);

    lcd.setCursor(1, 2);
  lcd.print("Amount: ");
  lcd.print(amount);

  for (int i = 0; i <= amount; i = i + 50) {
    lcd.setCursor(1, 3);
    lcd.print(i);
    /*if (slow) {
      delay(5000);
    }*/
    
    stepper(turns, screw, 1);  //1 turn = 4000 steps = 103g
    stepper(0.2, screw, 0);       //spins backwards chug control
  }
}

//Calibration---------------------------------------------------------

int Calibration(bool buttom) {

  int previous_storage = storage();
  int new_storage;
  float calibrated_value;
  int turns = 1;//------------ higher more precision
  bool buttom_state;

  lcd.clear();

  lcd.setCursor(5, 1);
  lcd.print("CALIBRATING");
  lcd.setCursor(8, 2);
  lcd.print("wait");
  lcd.setCursor(7, 3);
  lcd.print(previous_storage);
  lcd.print("g");

  for (int i = 0; i <= turns; i++) {
    stepper(1, screw, 1);  //1 turn = 4000 steps
    stepper(0.2, screw, 0);
  }
  lcd.clear();
  while (buttom_state == 1) {  
    buttom_state = digitalRead(buttom_3); 
    lcd.setCursor(3, 1);
    lcd.print("REMOVE THE FOOD");
    lcd.setCursor(7, 2);
    lcd.print("PRESS OK");
  }

  new_storage = storage();
  calibrated_value = (previous_storage - new_storage) / turns; // 1 turn = 103g

  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("CALIBRATED");
  delay(1000);
  lcd.clear();

  return calibrated_value;
}


//==================================================================
void setup() {
  Serial.begin(9600);
  //clock.setDS1302Time(30, 45, 22, 2, 2, 5, 2023);// seconds, minutes, hours, day of the week, day of the month, month, year
  pinMode(screw, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(Sleepmotor, OUTPUT);


  //Scale--------------------
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);

  //----------------------


  // Initiate the LCD

  lcd.init();

  // Sets buzzer

  pinMode(BUZZER_PIN, OUTPUT);

  // button
  pinMode(buttom_1, INPUT_PULLUP);
  pinMode(buttom_2, INPUT_PULLUP);
  pinMode(buttom_3, INPUT_PULLUP);
  pinMode(buttom_4, INPUT_PULLUP);
}


const int arraySize = 4;
int current_history[arraySize];  // = { 205, 232, 197, 201};
int old_storage;
int new_storage;
int new_meal;
int calibrated = 100; //standart value


void loop() {

  pot = analogRead(A0);
  //pot = 200;
  bool buttom1 = digitalRead(buttom_1);
  bool buttom2 = digitalRead(buttom_2);
  bool buttom3 = digitalRead(buttom_3);
  bool buttom4 = digitalRead(buttom_4);

  new_storage = storage();

  amount = quantity(pot);

  clock.updateTime();

  lcd.setBacklight(HIGH);

  lcd.setCursor(1, 0);
  lcd.print("Time");
  lcd.setCursor(0, 1);
  lcd.print(clock.hours);
  lcd.print(":");
  lcd.print(clock.minutes);
  lcd.print(":");
  lcd.print(clock.seconds);

  lcd.setCursor(8, 0);
  lcd.print("Meal");
  lcd.setCursor(8, 1);
  lcd.print(amount);
  lcd.print("g ");

  lcd.setCursor(13, 0);
  lcd.print("Storage");
  lcd.setCursor(14, 1);
  lcd.print(new_storage);
  lcd.print("g ");

  lcd.setCursor(0, 2);
  lcd.print("History");

  lcd.setCursor(1, 3);

  for (int i = 0; i < arraySize; i++) {
    lcd.print(current_history[i]);
    lcd.print("g "); 
  }

  if (buttom3 == 0) {
    calibrated = Calibration(buttom_3);
    lcd.setCursor(8, 2);
    lcd.print(calibrated);
  }


  if (clock.hours == 7 && clock.minutes == 0 && clock.seconds == 0) {
    old_storage = new_storage;
    feed(calibrated,amount, 0);
    lcd.clear();
    lcd.setCursor(2, 2);
    lcd.print("Next meal at: 16");
    ring(1);
    delay(20000);
    new_storage = storage();
    new_meal = old_storage - new_storage;
    History(new_meal, arraySize, current_history);
  }


  if (clock.hours == 16 && clock.minutes == 0 && clock.seconds == 0) {

    feed(calibrated,amount, 0);
    lcd.clear();
    lcd.setCursor(3, 2);
    lcd.print("Next meal at 7");
    ring(1);
    delay(60000); //time for the doog to finish eating
    new_storage = storage();
    new_meal = old_storage - new_storage;
    History(new_meal, arraySize, current_history);
  }

  if (buttom1 == 0) {

    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Giving a treat");
    lcd.setCursor(7, 2);
    lcd.print("Wooof!");
    digitalWrite(Sleepmotor, HIGH);
    stepper(0.1, screw, 1);
    ring(1);
    lcd.clear();
  }

  if (buttom2 == 0) {
    lcd.setCursor(8, 2);
    lcd.print("Feeding");
    old_storage = new_storage;
    feed(calibrated,amount, 0);

    //lcd.print("Next meal at: 16");
    ring(1);
    delay(2000);
    new_storage = storage();
    new_meal = old_storage - new_storage;
    History(new_meal, arraySize, current_history);
  }
}
