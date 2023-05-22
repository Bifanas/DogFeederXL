#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TIMEOUT_COUNT 3000 // aumentei pra 3000 pq tava dando ruim

LiquidCrystal_I2C lcd(0x27, 16, 4);

int switchPin = 13;  // button pin KEY
int click = HIGH; // button value

int pinA = 12;    // Rotary encoder Pin S1
int pinB = 11;    // Rotary encoder Pin S2
int pinAstateCurrent = LOW;   // Current state of Pin S1
int pinAStateLast = pinAstateCurrent;   // Last read value of Pin S2

int st=0; //setting state 0 - main screen state

bool refresh_screen=true; // impede q fique printando a tela 900x até ir pra proxima (NÃO FICA PISCANDO)

//int aux = 0; // linha em q o encoder está

int encoder = 0;

int line=0;

int timer = 0; // pra contar o num de ciclos até voltar pra tela inicial

void setup() {
  Serial.begin(9600);   // Initialise the serial monitor
  pinMode(switchPin, INPUT_PULLUP);   // Enable the switchPin as input with a PULLUP resistor
  pinMode(pinA, INPUT);   // Set PinA as input
  pinMode(pinB, INPUT);   // Set PinB as input
  lcd.init();       // Initialize the LCD
  lcd.setBacklight(HIGH); // Turn on the backlight
}


// Read and interpret rotary encoder inputs because it wans't working on the other thing
int read_encoder() {
  int movement = 0; //
  int pinAstateCurrent = digitalRead(pinA);   // Read the current state of pinA

   // If the encoder knob was turned
  if ((pinAStateLast == LOW) && (pinAstateCurrent == HIGH)) {   // Check the direction of the turn
    if (digitalRead(pinB) == HIGH) {
      movement = 1; // direção do relogiooo
    } else {
      movement = -1; //oposto do relogiooo
    }
  }

  pinAStateLast = pinAstateCurrent; //guarda o ultimo estado do pinA pra comparar depois
  return movement; //retorna o movimento binito 
}

//nova função de navegação do encoder
int Cursor_nav() {
  static int aux = 0;   //onde o encoder tá 
  static int aux_last = -1; // will store the last position of aux, I should write everything in one language

  click = digitalRead(switchPin); // Read the digital value of the switch (LOW/HIGH)
  // If the switch is pressed (LOW), return current line
  if (click == LOW) {
    return aux;
  }

  // Read encoder
  int encoder_move = read_encoder(); //determines if the rotary encoder has moved

  if (encoder_move == 1) {
    aux++;
    if (aux > 3) aux = 0;
  } 
  else if (encoder_move == -1) {
    aux--;
    if (aux < 0) aux = 3; //volta pra primeira linha se atingir o 3
  }

  // Only print cursor if it moved
  if (aux != aux_last) {
    lcd.setCursor(0, 0);  // Clear all possible cursor positions
    lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print("  ");
    lcd.setCursor(0, 2);
    lcd.print("  ");
    lcd.setCursor(0, 3);
    lcd.print("  ");

    lcd.setCursor(0, aux);
    lcd.print("->");

    // Save the current cursor position as the last position
    aux_last = aux;
  }

  return aux;
}



void Home_screen() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("20/04/2023");
  lcd.setCursor(1, 1);
  lcd.print("clock.hours");
  lcd.setCursor(1, 2);
  lcd.print("Next meal: 16:30");
}

int Settings_screen() {
  lcd.clear();
  lcd.setCursor(12,0);
  lcd.print("Settings");
  lcd.setCursor(2,0);
  lcd.print("Treat");
  lcd.setCursor(2,1);
  lcd.print("Schedule");
  lcd.setCursor(2, 2);
  lcd.print("Calibrate");
  lcd.setCursor(2, 3);
  lcd.print("Sound");
}

void Schedule_screen() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Schedule: ");
 
  lcd.setCursor(2, 1);
  lcd.print("08:00");
 
  lcd.setCursor(2, 2);
    lcd.print("12:00");

  lcd.setCursor(2, 3);
  lcd.print("16:30");
}

void loop() {
  static int click_last = HIGH;
  click = digitalRead(switchPin);

  
  switch(st){
    case 0: // main screen 
      if (refresh_screen) {
        Home_screen();
        refresh_screen=false;   // Only refresh the screen once per state change
      }
      if (click==LOW){    // If button was pressed, transition to the settings screen
        st=1;   
        refresh_screen=true;
       // line = 0;
      }
      timer = 0;      
      break;

    case 1: // settings screen
      if (refresh_screen) {
        Settings_screen();        
        refresh_screen=false;
        timer = 0;
      }
      line = Cursor_nav();
      
      if(click==LOW && line==1){    // If button was pressed while 'Schedule' was selected, transition to the schedule screen
        st=2;
        refresh_screen=true;
        delay(200);
      } 
      
      else{
        if(timer>=TIMEOUT_COUNT){
          st = 0;
          refresh_screen=true;
        }
       // delay(200);
      }
      
      break;

    case 2: // schedule screen 
      if (refresh_screen) {
        Schedule_screen();
        refresh_screen=false;
        timer = 0;
      }
      //line = Cursor_nav();
      
      if(click==LOW){
        st=1;
        refresh_screen=true;
        delay(200);
      }
      else{
        if(timer>=TIMEOUT_COUNT){
          st = 0;
          refresh_screen=true;
        }
      }
      break;
  }

  delay(15);
  timer++;
}

