/*###########################################################################
################### INCLUDES AND DEFINES ####################################*/
  
  #include <Wire.h>
  #define TIMEOUT_COUNT 1000  // timeout to return to main screen

  // SCREEN
  #include <LiquidCrystal_I2C.h>

  //RTC
  #include <uRTCLib.h>  // RTC lib

  // SOM
  #include <SoftwareSerial.h>
  #include "RedMP3.h"   //MP3 maroto
  #define ARDUINO_RX 7  //mp3
  #define ARDUINO_TX 8  //mp3

  // TEMPHUMIDITY
  #include <dht.h>
  #define dataPin 9



/*################# END INCLUDES AND DEFINES ################################
#############################################################################*/

/*###########################################################################
################### VARIABLES OR FIXED ######################################*/
  // RTC 
  uRTCLib rtc(0x68);  //a4 e a5 pinos do rtc
  char auxtime[6][3];
  
  // LCD 
  LiquidCrystal_I2C lcd(0x27, 16, 4);

  // ENCODER 
  int switchPin = 13;  // button pin KEY
  int click = HIGH;    // button value

  int pinA = 12;                         // Rotary encoder Pin S1
  int pinB = 11;                         // Rotary encoder Pin S2
  int pinAstateCurrent = LOW;            // Current state of Pin S1
  int pinAStateLast = pinAstateCurrent;  // Last read value of Pin S2

  // SOM
  MP3 mp3(ARDUINO_RX, ARDUINO_TX);  //MP3
  int8_t musica1 = 0x01;            //primeira música do cartão SD
  int8_t musica2 = 0x02;            //segunda música do cartão SD
  int8_t musica3 = 0x03;            //terceira música do cartão SD
  int8_t folderName = 0x01;         //pasta do cartão
  int8_t lastVolume = 20;           //volume atual
  int ss = musica1;                 // sond selected default option musica1

  // MOTOR
  const int Enable = 2;
  const int step = 3;
  const int dirPin = 4;
  int calibratedaux = 100;     // only for calibration
  int calibrated_value = 100;  // this one for feed
  const int buttom_1 = 13;
  int amount = 200;

  //TEMPHUMIDITY
  dht DHT;
  float temperature, humidity;

  //AUX CHAR
  byte Ossinho[8] = {
    0b00000,
    0b01010,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b01010,
    0b00000
  };

  byte garfo[8] = {
    0b00000,
    0b01010,
    0b01110,
    0b01110,
    0b00100,
    0b00100,
    0b00100,
    0b00000
  };

  byte faca[8] = {
    0b00000,
    0b00100,
    0b01100,
    0b01100,
    0b01100,
    0b00100,
    0b00100,
    0b00000
  };


  // AUX 
  int st = 0;  //setting state 0 - main screen state

  bool refresh_screen = true;  // impede q fique printando a tela 900x até ir pra proxima (NÃO FICA PISCANDO)

  int encoder = 0;

  int line = 0;

  int timer = 0;  // pra contar o num de ciclos até voltar pra tela inicial

  int meal[2][4] = { { 8, 30, 50, 0 }, { 9, 40, 0, 0 } }; // meals settings
  int x = 0; //aux to meals settings

  char slowmode[2][4] = { "off", " on" }; //slow mode


/*################# END VARIABLES OR FIXED ##################################
#############################################################################*/

/*###########################################################################
#################### SETUP ##################################################*/


  void setup() {

    Serial.begin(9600);  // Initialise the serial monitor

    // ENCODER
    pinMode(switchPin, INPUT_PULLUP);  // Enable the switchPin as input with a PULLUP resistor
    pinMode(pinA, INPUT);              // Set PinA as input
    pinMode(pinB, INPUT);              // Set PinB as input

    // LCD
    lcd.init();              // Initialize the LCD
    lcd.setBacklight(HIGH);  // Turn on the backlight

    // SOM 
    mp3.setVolume(lastVolume);  //selecionar o volume
    

    //RTC
    URTCLIB_WIRE.begin();

    // Comment out below line once you set the date & time.
    // Following line sets the RTC with an explicit date & time
    // for example to set January 13 2022 at 12:56 you would call:
    //rtc.set(0, 29, 8, 1, 28, 5, 23);
    // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
    // set day of week (1=Sunday, 7=Saturday)

    // MOTOR
    pinMode(step, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(Enable, OUTPUT);

    //AUX CHAR
    lcd.createChar(0, garfo);
    lcd.createChar(1, faca);
  }


/*################## END SETUP ##############################################
 ############################################################################*/

/*###########################################################################
##################### AUX FUNCTIONS #########################################*/
  // ENCODER 
    int read_encoder() { // Read and interpret rotary encoder inputs because it wans't working on the other thing
      int movement = 0;                          //
      int pinAstateCurrent = digitalRead(pinA);  // Read the current state of pinA

      // If the encoder knob was turned
      if ((pinAStateLast == LOW) && (pinAstateCurrent == HIGH)) {  // Check the direction of the turn
        if (digitalRead(pinB) == HIGH) {
          movement = 1;  // direção do relogiooo
        } else {
          movement = -1;  //oposto do relogiooo
        }
      }

      pinAStateLast = pinAstateCurrent;  //guarda o ultimo estado do pinA pra comparar depois
      return movement;                   //retorna o movimento binito
    }

  
    int Cursor_nav() { //nova função de navegação do encoder
      static int aux = 0;        //onde o encoder tá
      static int aux_last = -1;  // will store the last position of aux, I should write everything in one language

      click = digitalRead(switchPin);  // Read the digital value of the switch (LOW/HIGH)
      // If the switch is pressed (LOW), return current line
      if (click == LOW) {
        return aux;
      }

      // Read encoder
      int encoder_move = read_encoder();  //determines if the rotary encoder has moved

      if (encoder_move == 1) {
        aux++;
        if (aux > 3) aux = 0;
      } else if (encoder_move == -1) {
        aux--;
        if (aux < 0) aux = 3;  //volta pra primeira linha se atingir o 3
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

    int encoderChangehour(int hour) {     //ajustar volume
      int encoder_move = read_encoder();  //determines if the rotary encoder has moved
      if (encoder_move == 1) {
        hour++;
      } else if (encoder_move == -1) {
        hour--;
      }

      hour = constrain(hour, 0, 23);

      // Only print cursor if it moved
      if (hour != meal[x][0]) {
        meal[x][0] = hour;
      }
      return hour;
    }

    int encoderChangeminute(int minute) {  //ajustar volume
      int encoder_move = read_encoder();   //determines if the rotary encoder has moved
      if (encoder_move == 1) {
        minute++;
      } else if (encoder_move == -1) {
        minute--;
      }

      minute = constrain(minute, 0, 59);

      // Only print cursor if it moved
      if (minute != meal[x][1]) {
        meal[x][1] = minute;
      }
      return minute;
    }

    int encoderChangeportion(int portion) {  //ajustar volume
      int encoder_move = read_encoder();     //determines if the rotary encoder has moved
      if (encoder_move == 1) {
        portion= portion+10;
      } else if (encoder_move == -1) {
        portion= portion-10;
      }

      portion = constrain(portion, 0, 1000);

      // Only print cursor if it moved
      if (portion != meal[x][2]) {
        meal[x][2] = portion;
      }
      return portion;
    }

    int encoderCalibratePortion(int CP) {  //ajustar volume
      int encoder_move = read_encoder();   //determines if the rotary encoder has moved
      if (encoder_move == 1) {
        CP= CP+10;
      } else if (encoder_move == -1) {
        CP= CP-10;
      }

      CP = constrain(CP, 0, 1000);

      // Only print cursor if it moved
      if (CP != calibratedaux) {
        calibratedaux = CP;
      }
      return CP;
    }

  // END ENCODER

  // SOM
    int encoderChangeVolume(int volume) {  //ajustar volume
      int encoder_move = read_encoder();   //determines if the rotary encoder has moved
      if (encoder_move == 1) {
        volume++;
      } else if (encoder_move == -1) {
        volume--;
      }

      volume = constrain(volume, 0, 30);

      // Only print cursor if it moved
      if (volume != lastVolume) {
        mp3.setVolume(volume);
        lastVolume = volume;
      }
      return volume;
    }
  // END SOM

  //MOTOR
    void stepper(float Screw_turns, int motorpin, bool direction) {

      int speed = 830;  //NEEDS TO BE CALIBRATED !!!
      int full_turn = 4000;

      int steps = Screw_turns * full_turn;  // get how many steps

      digitalWrite(Enable, LOW);
      digitalWrite(dirPin, direction);

      for (int x = 0; x < steps; x++) {
        digitalWrite(motorpin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(motorpin, LOW);
        delayMicroseconds(speed);
      }
      digitalWrite(Enable, HIGH);
    }


    void feed(int cal, int amount, bool slow) {
      float turns;
      turns = 50 / cal;  //  to get how many turns to get 50g

      for (int i = 0; i <= amount; i = i + 50) {
        stepper(turns, step, 1);  //1 turn = 4000 steps = 103g
        stepper(0.2, step, 0);    //spins backwards chug control
        if (slow) {
          delay(5000);
        }
      }
    }

  //END MOTOR

  //TEMPHUMIDITY
    void readDHTData(float& temperature, float& humidity) {
      int readData = DHT.read22(dataPin);
      temperature = DHT.temperature;
      humidity = DHT.humidity;
    }

  //END TEMPHUMIDITY
/*################### END AUX FUNCTIONS #####################################
#############################################################################*/

/*###########################################################################
###################### LOOP #################################################*/
  void loop() {

    // ENCODER
    static int click_last = HIGH;
    click = digitalRead(switchPin);


    // RTC
    rtc.refresh();

    itoa(rtc.second(), auxtime[2], 10);
    itoa(rtc.minute(), auxtime[1], 10);
    itoa(rtc.hour(), auxtime[0], 10);

    itoa(rtc.day(), auxtime[3], 10);
    itoa(rtc.month(), auxtime[4], 10);
    itoa(rtc.year(), auxtime[5], 10);

    // TEMPHUMIDITY
    readDHTData(temperature, humidity);

    // SWITCH SCREENS
    switch (st) {
      case 0:  // main screen
        if (refresh_screen) {
          Home_screen();
          refresh_screen = false;  // Only refresh the screen once per state change
          timer = 0;
          if (meal[0][0] == auxtime[0] && meal[0][1] == auxtime[1]) {
            feed(calibrated_value, meal[0][2], meal[0][3]);
            mp3.playWithVolume(ss, lastVolume);
          }
          if (meal[1][0] == auxtime[0] && meal[1][1] == auxtime[1]) {
            feed(calibratedaux, meal[1][2], meal[1][3]);
            mp3.playWithVolume(ss, lastVolume);
          }
        }
        
        if (click == LOW) {  // If button was pressed, transition to the settings screen
          st = 1;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 1:  // settings screen
        if (refresh_screen) {
          Settings_screen();
          refresh_screen = false;
          timer = 0;
        }
        line = Cursor_nav();

        if (click == LOW && line == 0) {  // If button was pressed while 'Treat' was selected, transition to the treat screen
          st = 18;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 1) {  // schedule
          st = 2;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 2) {  //calibration
          st = 11;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 3) {  // Sound
          st = 15;
          refresh_screen = true;
          delay(200);
        }

        else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
          // delay(200);
        }

        break;

      case 2:  // schedule screen
        if (refresh_screen) {
          Schedule_screen();
          refresh_screen = false;
          timer = 0;
        }
        line = Cursor_nav();

        if (click == LOW && line == 3) {
          st = 1;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 1) {
          st = 3;
          x = 0;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 2) {
          st = 3;
          x = 1;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 3:  // schedule options (edit/remove?)
        if (refresh_screen) {
          Schedule_options();
          refresh_screen = false;
          timer = 0;
        }
        line = Cursor_nav();

        if (click == LOW && line == 1) {  // edit
          st = 4;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 2) {  //back
          st = 2;
          refresh_screen = true;
          delay(200);
        }

        if (click == LOW && line == 0) {  //Remove
          st = 9;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 4:  // EDIT
        if (refresh_screen) {
          Schedule_time_set();
          refresh_screen = false;
          timer = 0;
        }
        line = Cursor_nav();

        if (click == LOW && line == 0) {
          st = 5;
          refresh_screen = true;
          delay(200);
        }

        if (click == LOW && line == 1) {
          st = 7;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 2) {
          st = 8;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 3) {  // back
          st = 2;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 5:  //  time set hour
        static int lastPrintedHour = -1;
        if (refresh_screen) {
          Time_set();
          refresh_screen = false;
          timer = 0;
        }
        meal[x][0] = encoderChangehour(meal[x][0]);


        if (meal[x][0] != lastPrintedHour) {
          lcd.setCursor(2, 2);
          lcd.print("     ");  // To clear previous value
          lcd.setCursor(2, 2);
          lcd.print(meal[x][0]);
          lastPrintedHour = meal[x][0];
        }

        if (click == LOW) {
          st = 6;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 6:  // time set min
        static int lastPrintedMinute = -1;
        if (refresh_screen) {
          Time_set_min();
          refresh_screen = false;
          timer = 0;
        }
        meal[x][1] = encoderChangeminute(meal[x][1]);

        if (meal[x][1] != lastPrintedMinute) {
          lcd.setCursor(2, 2);
          lcd.print("     ");  // To clear previous value
          lcd.setCursor(2, 2);
          lcd.print(meal[x][1]);
          lastPrintedMinute = meal[x][1];
        }

        if (click == LOW) {
          st = 4;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 7:  // portion set
        static int lastPrintedPortion = -1;
        if (refresh_screen) {
          Portion_set();
          refresh_screen = false;
          timer = 0;
        }
        meal[x][2] = encoderChangeportion(meal[x][2]);

        if (meal[x][2] != lastPrintedPortion) {
          lcd.setCursor(2, 2);
          lcd.print("     ");  // To clear previous value
          lcd.setCursor(2, 2);
          lcd.print(meal[x][2]);
          lastPrintedPortion = meal[x][2];
        }

        if (click == LOW) {
          st = 4;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 8:  // slow mode
        if (refresh_screen) {
          Slow_Mode();
          refresh_screen = false;
          timer = 0;
        }
        line = Cursor_nav();
        if (click == LOW && line == 1) {
          meal[x][3] = 1;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 2) {
          meal[x][3] = 0;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 3) {
          st = 4;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;
      case 9:  // schedule remove
        if (refresh_screen) {
          Schedule_remove();
          refresh_screen = false;
          timer = 0;
        }
        line = Cursor_nav();

        if (click == LOW && line == 3) {
          st = 3;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 1 || click == LOW && line == 2) {
          st = 10;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 10:  // Not found
        if (refresh_screen) {
          Not_found();
          refresh_screen = false;
          timer = 0;
        }

        if (click == LOW) {
          st = 9;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 11:  // CALIBRATE
        if (refresh_screen) {
          Calibrate();
          refresh_screen = false;
          timer = 0;
        }
        line = Cursor_nav();

        if (click == LOW && line == 3) {
          st = 1;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 2) {
          st = 12;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 12:  // Calibrate_Droppingfood
        if (refresh_screen) {
          Calibrate_DF();
          refresh_screen = false;
        }
        for (int i = 0; i <= 1; i++) {
          stepper(1, 3, 1);  //1 turn = 4000 steps
          stepper(0.2, 3, 0);
        }
        st = 13;
        refresh_screen = true;
        delay(200);

        break;

      case 13:  // Calibrate_ INSERT CALIBRATED PORTION
        static int lastPrintedCP = -1;
        if (refresh_screen) {
          Calibrate_TFO();
          refresh_screen = false;
          timer = 0;
        }
        calibratedaux = encoderCalibratePortion(calibratedaux);

        if (calibratedaux != lastPrintedCP) {
          lcd.setCursor(2, 2);
          lcd.print("     ");  // To clear previous value
          lcd.setCursor(2, 2);
          lcd.print(calibratedaux);
          lastPrintedCP = calibratedaux;
        }
        calibrated_value = (calibratedaux) / 10;  // 1 turn = 103g

        if (click == LOW) {
          st = 14;
          refresh_screen = true;
          delay(200);
        } 

        break;

      case 14:  // CalibrateD
        if (refresh_screen) {
          CalibrateD();
          refresh_screen = false;
          timer = 0;
        }

        if (click == LOW) {
          st = 0;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 15:  // Sound
        if (refresh_screen) {
          Sound();
          refresh_screen = false;
          timer = 0;
        }
        line = Cursor_nav();

        if (click == LOW && line == 1) {
          st = 16;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 2) {
          st = 17;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 3) {
          st = 1;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 16:  // Sound_choose
        if (refresh_screen) {
          Sound_choose();
          refresh_screen = false;
          timer = 0;
        }
        line = Cursor_nav();
        if (click == LOW && line == 1) {
          mp3.playWithVolume(musica1, lastVolume);
          ss = musica1;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 2) {
          mp3.playWithVolume(musica2, lastVolume);
          ss = musica2;
          refresh_screen = true;
          delay(200);
        }
        if (click == LOW && line == 3) {
          st = 15;
          refresh_screen = true;
          mp3.stopPlay();
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 17:  // Sound_volume
        static int lastPrintedVolume = -1;
        if (refresh_screen) {
          Sound_volume();
          refresh_screen = false;
          timer = 0;
          //  delay(10);
        }
        lastVolume = encoderChangeVolume(lastVolume);

        if (lastVolume != lastPrintedVolume) {
          lcd.setCursor(7, 2);
          lcd.print("     ");  // To clear previous value
          lcd.setCursor(7, 2);
          lcd.print(lastVolume);
          lastPrintedVolume = lastVolume;
        }

        if (click == LOW) {
          st = 15;
          refresh_screen = true;
          delay(200);
        } else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;

      case 18:  // Treat
        if (refresh_screen) {
          Treat();
          refresh_screen = false;
          stepper(1, 3, 1);
          for (int i = 0; i <=4; i++) {
          mp3.playWithVolume(ss, lastVolume);
          delay(3000);
        }
          timer = 0;
        }
        

        if (click == LOW) {
          st = 0;
          refresh_screen = true;
          delay(200);
        }

        else {
          if (timer >= TIMEOUT_COUNT) {
            st = 0;
            refresh_screen = true;
          }
        }
        break;
    }

    delay(15);
    timer++;
  }
/*#################### END LOOP #############################################
#############################################################################*/


/*###########################################################################
###################### TELAS ################################################*/

  void Home_screen() {

    lcd.clear();
    lcd.setCursor(0, 0); lcd.print(auxtime[3]); lcd.print("/"); lcd.print(auxtime[4]); lcd.print("/"); lcd.print(auxtime[5]);
    // lcd.setCursor(17, 0);
    // lcd.print(rtc.dayOfWeek()-1);
    lcd.setCursor(1, 1);
    lcd.print(auxtime[0]);lcd.print(":"); lcd.print(auxtime[1]);
    lcd.setCursor(11, 0);
    lcd.print("Next meal");
    lcd.setCursor(13, 1);
    lcd.print("16:30");

    lcd.setCursor(2, 3);
    lcd.print(int(temperature));
    lcd.print("C");
    lcd.setCursor(8, 3);
    lcd.print(int(humidity));
    lcd.print("%");
    lcd.setCursor(14, 3);
    lcd.print("10");
    lcd.write(byte(0));
    lcd.write(byte(1));
  }

  void Settings_screen() {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Treat");
    lcd.setCursor(2, 1);
    lcd.print("Schedule");
    lcd.setCursor(2, 2);
    lcd.print("Calibrate");
    lcd.setCursor(2, 3);
    lcd.print("Sound");
  }

  void Schedule_screen() {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Schedule: ");

    lcd.setCursor(2, 1);
    lcd.print(meal[0][0]);
    lcd.print(":");
    lcd.print(meal[0][1]);

    lcd.setCursor(2, 2);
    lcd.print(meal[1][0]);
    lcd.print(":");
    lcd.print(meal[1][1]);

    lcd.setCursor(2, 3);
    lcd.print("Back");
  }

  void Schedule_options() {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Remove");

    lcd.setCursor(2, 1);
    lcd.print("Edit");

    lcd.setCursor(2, 2);
    lcd.print("Back");
  }

  void Schedule_time_set() {
    lcd.clear();

    lcd.setCursor(2, 0);
    lcd.print("Time:");

    lcd.setCursor(12, 0);
    lcd.print(meal[x][0]);
    lcd.print(":");
    lcd.print(meal[x][1]);

    lcd.setCursor(2, 1);
    lcd.print("Portion");

    lcd.setCursor(12, 1);
    lcd.print(meal[x][2]);

    lcd.setCursor(2, 2);
    lcd.print("Slow");

    lcd.setCursor(12, 2);
    lcd.print(slowmode[meal[x][3]]);
    lcd.setCursor(2, 3);
    lcd.print("Back");
  }


  void Time_set() {
    lcd.clear();

    lcd.setCursor(7, 0);
    lcd.print("Hour");

    lcd.setCursor(2, 2);
    lcd.print(meal[x][0]);

    lcd.setCursor(2, 3);
    lcd.print("Minutes");
  }

  void Time_set_min() {
    lcd.clear();

    lcd.setCursor(7, 0);
    lcd.print("Minutes");

    lcd.setCursor(2, 2);
    lcd.print(meal[x][1]);

    lcd.setCursor(2, 3);
    lcd.print("Back");
  }

  void Portion_set() {
    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print("Portion");

    lcd.setCursor(2, 2);
    lcd.print(meal[x][2]);

    lcd.setCursor(2, 3);
    lcd.print("Back");
  }

  void Slow_Mode() {
    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print("Slow Mode");

    lcd.setCursor(2, 1);
    lcd.print("On");

    lcd.setCursor(2, 2);
    lcd.print("Off");

    lcd.setCursor(2, 3);
    lcd.print("Back");
  }

  void Schedule_remove(void) {
    lcd.clear();
    lcd.setCursor(4, 0);  // HEADER ---------------------------------
    lcd.print("Remove ");
    lcd.print("08:00");  //aqui vai a variavel
    lcd.print(" ?");
    lcd.setCursor(2, 1);  //yes
    lcd.print("Yes");
    lcd.setCursor(2, 2);  // No
    lcd.print("No");
    lcd.setCursor(2, 3);  // RETURN ---------------------------------
    lcd.print("Back");
  }

  void Not_found(void) {

    lcd.clear();
    lcd.setCursor(8, 1);  // HEADER ---------------------------------
    lcd.print("o_o");
    lcd.setCursor(5, 2);  //yes
    lcd.print("Not Found");
  }

  void Calibrate(void) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Callibrate:");
    lcd.setCursor(2, 2);
    lcd.print("Start");
    lcd.setCursor(2, 3);
    lcd.print("Back");
  }

  void Calibrate_DF(void) {
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Dropping food...");
    lcd.setCursor(7, 3);
    lcd.print("wait");
  }

  void Calibrate_TFO(void) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Measure the food");
    lcd.setCursor(2, 2);
    lcd.print(calibratedaux);
  }

  void CalibrateD(void) {
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print("CALIBRATED!");
    lcd.setCursor(7, 2);
    lcd.print(";)");
  }

  void Sound(void) {
    lcd.clear();
    lcd.setCursor(7, 0);  // HEADER ---------------------------------
    lcd.print("Sound ");
    lcd.setCursor(2, 1);
    lcd.print("Choose sound");
    lcd.setCursor(2, 2);
    lcd.print("Volume");
    lcd.setCursor(2, 3);  // RETURN ---------------------------------
    lcd.print("Back");
  }

  void Sound_choose(void) {
    lcd.clear();
    lcd.setCursor(5, 0);  // HEADER ---------------------------------
    lcd.print("Choose Sound ");
    lcd.setCursor(2, 1);
    lcd.print("Bird");
    lcd.setCursor(2, 2);
    lcd.print("Bell");
    lcd.setCursor(2, 3);  // RETURN ---------------------------------
    lcd.print("Back");
  }

  void Sound_volume() {
    lcd.clear();
    lcd.setCursor(5, 0);  // HEADER ---------------------------------
    lcd.print("Volume");
    // lastVolume = encoderChangeVolume(lastVolume);
    lcd.setCursor(7, 2);  // HEADER ---------------------------------
    lcd.print(lastVolume);
    lcd.setCursor(2, 3);  // RETURN ---------------------------------
    lcd.print("Back");
  }

  void Treat() {
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("D   D");
    lcd.setCursor(5, 1);
    lcd.print("  o.o ");
    lcd.setCursor(6, 2);
    lcd.print("  w ");
  }

/*#################### END TELAS ############################################
#############################################################################*/
