/*********
  Complete project details at https://randomnerdtutorials.com
  
  This is an example for our Monochrome OLEDs based on SSD1306 drivers. Pick one up today in the adafruit shop! ------> http://www.adafruit.com/category/63_98
  This example is for a 128x32 pixel lcd using I2C to communicate 3 pins are required to interface (two I2C and one reset).
  Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community. BSD license, check license.txt for more information All text above, and the splash screen below must be included in any redistribution. 
*********/
/*
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED lcd width, in pixels
#define SCREEN_HEIGHT 64  // OLED lcd height, in pixels

// Declaration for an SSD1306 lcd connected to I2C (SDA, SCL pins)
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16


static const unsigned char PROGMEM logo_bmp[] = { B00000000, B11000000,
                                                  B00000001, B11000000,
                                                  B00000001, B11000000,
                                                  B00000011, B11100000,
                                                  B11110011, B11100000,
                                                  B11111110, B11111000,
                                                  B01111110, B11111111,
                                                  B00110011, B10011111,
                                                  B00011111, B11111100,
                                                  B00001101, B01110000,
                                                  B00011011, B10100000,
                                                  B00111111, B11100000,
                                                  B00111111, B11110000,
                                                  B01111100, B11110000,
                                                  B01110000, B01110000,
                                                  B00000000, B00110000 };
*/

// include the library code:
#include <LiquidCrystal.h>

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16,4);

 /* // SSD1306_SWITCHCAPVCC = generate lcd voltage from 3.3V internally
  if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }*/

  
  delay(1000);  // Pause for 2 seconds

  // Clear the buffer
  lcd.clear();




  // IMPLEMENTED ===============================================

  Home_screen();

  Settings_screen();

  Schedule_screen();

  Schedule_options();

  Schedule_editing();

  Schedule_time_set();

  Schedule_portion_set();

  Schedule_Slow();

  Schedule_remove();



  Calibrated_screen();

  Error_screen();

  sound_screen();

  sound_volume_screen();

  sound_settings_screen();

  Calibrate();

  Calibrate_feedback();

  Calibrate_loading();

  History();
}

void loop() {

  
}


void Home_screen(void) {

  lcd.clear();
  

 // DATE ---------------------------------------
  lcd.setCursor(0, 0);
  lcd.print("20/04/2023");

  //lcd.print(clock.day);
  //lcd.print("/");
  //lcd.print(clock.month);
  //lcd.print("/");
  //lcd.print(clock.year);

// CURENT TIME -------------------------------
  lcd.setCursor(65, 0);

  lcd.print("14:00");

  //lcd.print(clock.hours);
  //lcd.print(":");
  //lcd.print(clock.minutes);


 // NEXT MEAL TIME --------------------------
  lcd.setCursor(0, 32);
  lcd.print("Next meal: ");

  lcd.setCursor(65, 25);
  lcd.print("16:30");

  //lcd.print(next_meal(hour));
  //lcd.print(":");
  //lcd.print(next_meal(minute));

  lcd.setCursor(6, 55);
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



void Settings_screen(void) {
  lcd.clear();
  


  lcd.setCursor(5, 15);  // CURSOR ----------------------------------
  lcd.write(0x10);

  lcd.setCursor(35, 0);  // HEADER ----------------------------------
  lcd.print("Settings: ");

 
  lcd.setCursor(15, 15);  // SCHEDULE --------------------------------
  lcd.print("Schedule");


  lcd.setCursor(15, 25);  // CALIBRATE------------------------------
  lcd.print("Calibrate");

  lcd.setCursor(15, 35);  // INFORMATION ---------------------------
  lcd.print("Information");

  lcd.setCursor(15, 45);  // SOUND ---------------------------------
  lcd.print("Sound");

  lcd.setCursor(15, 55);  // HISTORY -------------------------------
  lcd.print("History");

  delay(50);
}



void Schedule_screen(void) {
  lcd.clear();
 

  lcd.setCursor(5, 15);  // CURSOR -----------------------------------
  lcd.write(0x10);

  lcd.setCursor(35, 0);  // HEADER ---------------------------------
  lcd.print("Schedule: ");

 
  lcd.setCursor(15, 15);  // MEAL 1 --------------------------------
  lcd.print("08:00");

 
  lcd.setCursor(15, 25);  // MEAL 2 --------------------------------
  lcd.print("12:00");

  lcd.setCursor(15, 35);  // MEAL 3 --------------------------------
  lcd.print("16:30");

  lcd.setCursor(110, 55);  // RETURN -----------------------------------
  lcd.write(0x1B);



  delay(50);
}



void Schedule_options(void) {

  lcd.clear();


  lcd.setCursor(5, 15);  // CURSOR -----------------------------------
  lcd.write(0x10);

  lcd.setCursor(50, 0);  // HEADER ---------------------------------
  lcd.print("08:00");


  lcd.setCursor(15, 15);  // REMOVE --------------------------------
  lcd.print("Remove");


  lcd.setCursor(15, 25);  // EDIT --------------------------------
  lcd.print("Edid");

  lcd.setCursor(15, 35);  // NEW --------------------------------
  lcd.print("New");

  lcd.setCursor(110, 55);  // RETURN -----------------------------------
  lcd.write(0x1B);



  delay(50);
}



void Schedule_editing(void) {

  lcd.clear();


  lcd.setCursor(5, 15);  // CURSOR -----------------------------------
  lcd.write(0x10);

  lcd.setCursor(50, 0);  // HEADER ---------------------------------
  lcd.print("Edit:");


  lcd.setCursor(15, 15);  // TIME OF THE MEAL ---------------------
  lcd.print("Time         ");
  lcd.print("08:00");


  lcd.setCursor(15, 25);  // PORTION SIZE --------------------------
  lcd.print("Portion       ");
  lcd.print("200g");

  lcd.setCursor(15, 35);  // SLOW FEEDING --------------------------
  lcd.print("Slow           ");
  lcd.print("on");

  lcd.setCursor(110, 55);  // RETURN ---------------------------------
  lcd.write(0x1B);


  delay(50);
}



void Schedule_time_set(void) {

  lcd.clear();



  lcd.setCursor(50, 0);  // HEADER ----------------------------------
  lcd.print("Time:");



  lcd.setCursor(32, 25);  // HOUR -----------------------------------
  lcd.print("08");


  lcd.print(":");

  lcd.print("00");  // MINUTE ---------------------------------


  lcd.setCursor(110, 55);  // RETURN ----------------------------------
  lcd.write(0x1B);



  delay(50);
}



void Schedule_portion_set(void) {

  lcd.clear();



  lcd.setCursor(44, 0);  // HEADER ----------------------------------
  lcd.print("Portion:");

  lcd.setCursor(45, 25);  // Portion size -----------------------------------
  lcd.print("100");
  lcd.print("g");


  lcd.setCursor(110, 55);  // RETURN ----------------------------------
  lcd.write(0x1B);



  delay(50);
}



void Schedule_Slow(void) {

  lcd.clear();


  lcd.setCursor(5, 15);  // CURSOR -----------------------------------
  lcd.write(0x10);

  lcd.setCursor(35, 0);  // HEADER ---------------------------------
  lcd.print("Slow mode:");


  lcd.setCursor(15, 15);  // SLOW FEEDING ON ---------------------
  lcd.print("On");


  lcd.setCursor(15, 25);  // SLOW FEEDING OFF --------------------------
  lcd.print("Off");

  lcd.setCursor(110, 55);  // RETURN ---------------------------------
  lcd.write(0x1B);


  delay(50);
}



void Schedule_remove(void) {

  lcd.clear();


  lcd.setCursor(5, 15);  // CURSOR -----------------------------------
  lcd.write(0x10);

  lcd.setCursor(20, 0);  // HEADER ---------------------------------
  lcd.print("Remove ");
  lcd.print("08:00");
  lcd.print(" ?");



  lcd.setCursor(15, 15);  // SLOW FEEDING ON ---------------------
  lcd.print("Yes");


  lcd.setCursor(15, 25);  // SLOW FEEDING OFF --------------------------
  lcd.print("no");


  lcd.setCursor(110, 35);  // RETURN ---------------------------------
  lcd.write(0x1B);


  delay(50);
}



void Calibrated_screen(void) {
  lcd.clear();

  lcd.setCursor(5, 25);  // NOT FOUND -----------------------------------
  lcd.write("CALIBRATED");
  



  delay(50);
}



void Error_screen(void) {
  lcd.clear();

  lcd.setCursor(5, 25);  // NOT FOUND -----------------------------------
  lcd.write("NOT FOUND!");


  lcd.setCursor(110, 55);  // RETURN -----------------------------------
  lcd.write(0x1B);


  delay(50);
}



void sound_screen(void) {

  lcd.clear();


  lcd.setCursor(5, 15);  // CURSOR -----------------------------------
  lcd.write(0x10);

  lcd.setCursor(35, 0);  // HEADER ---------------------------------
  lcd.print("Sound:");

  lcd.setCursor(15, 15);  // CHOOSE THE SOUND---------------------
  lcd.print("Choose sound");


  lcd.setCursor(15, 25);  // Volume --------------------------
  lcd.print("Volume");

  lcd.setCursor(110, 35);  // RETURN ---------------------------------
  lcd.write(0x1B);
  lcd.setCursor(15, 35);  // Volume --------------------------
  lcd.print("Return");


  delay(50);
}



void sound_volume_screen(void) {

  lcd.clear();


  lcd.setCursor(45, 0);  // HEADER ---------------------------------
  lcd.print("Volume:");



  lcd.setCursor(52, 25);  // VOLUME -----------------------------------
  lcd.write("10");



  lcd.setCursor(110, 55);  // RETURN -----------------------------------
  lcd.write(0x1B);

  delay(50);
}




void sound_settings_screen(void) {

  lcd.clear();


  lcd.setCursor(5, 15);  // CURSOR -----------------------------------
  lcd.write(0x10);

  lcd.setCursor(15, 0);  // HEADER ---------------------------------
  lcd.print("Choose sound:");

  lcd.setCursor(15, 15);  // SOUND 1---------------------
  lcd.print("Sound 1");

  lcd.setCursor(15, 25);  // SOUND 2 --------------------------
  lcd.print("Sound 2");

  lcd.setCursor(15, 35);  // SOUND 3 --------------------------
  lcd.print("Sound 3");

  lcd.setCursor(110, 45);  // RETURN ---------------------------------
  lcd.write(0x1B);
  lcd.setCursor(15, 45);  // Volume --------------------------
  lcd.print("Return");


  delay(50);
}




void Calibrate(void) {
  lcd.clear();


  lcd.setCursor(5, 25);  // CURSOR -----------------------------------
  lcd.write(0x10);

  
  lcd.setCursor(35, 0);
  lcd.print("Callibrate");


  lcd.setCursor(15, 25);
  lcd.print("Start Calibration");

  lcd.setCursor(15, 35);
  lcd.print("Return");


  delay(50);
}



void Calibrate_loading(void) {
  lcd.clear();


  lcd.setCursor(8, 5);
  lcd.write("Dropping");

  lcd.setCursor(13, 25);
  lcd.write("food...");

 
  lcd.setCursor(50, 50);
  lcd.write("Wait");


  delay(50);
}



void Calibrate_feedback(void) {
  lcd.clear();

  
  lcd.setCursor(25, 5);
  lcd.write("Remove");

  lcd.setCursor(35, 25);
  lcd.write("food");


  lcd.setCursor(5, 50);
  lcd.write("Press when finished");


  delay(50);
}




void History(void) {
  lcd.clear();



  lcd.setCursor(40, 5);
  lcd.write("History");
  lcd.setCursor(0, 15);
  lcd.write("20/04   08:00   107g");
  lcd.setCursor(0, 25);
  lcd.write("19/04   16:30   196g");
  lcd.setCursor(0, 35);
  lcd.write("19/04   12:00   102g");
  lcd.setCursor(0, 45);
  lcd.write("18/04   12:00   134g");
  lcd.setCursor(0, 55);
  lcd.write("18/04   08:00   100g");

  delay(50);
}