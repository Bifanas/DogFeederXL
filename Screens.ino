/*********
  Complete project details at https://randomnerdtutorials.com
  
  This is an example for our Monochrome OLEDs based on SSD1306 drivers. Pick one up today in the adafruit shop! ------> http://www.adafruit.com/category/63_98
  This example is for a 128x32 pixel display using I2C to communicate 3 pins are required to interface (two I2C and one reset).
  Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community. BSD license, check license.txt for more information All text above, and the splash screen below must be included in any redistribution. 
*********/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
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

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(1000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

 // testdrawchar();      // Draw characters of the default font


// IMPLEMENTED ===============================================

 // Home_screen();

 // Settings_screen();

 // Schedule_screen();

 // Schedule_options();

 // Schedule_editing();

 // Schedule_time_set();

 // Schedule_portion_set();

 // Schedule_Slow();

 // Schedule_remove();

}

void loop() {
}

/*
void Home_screen(void) {

  display.clearDisplay();
  display.setTextColor(WHITE);  

  display.setTextSize(1);  // DATE ---------------------------------------
  display.setCursor(0,0);             
  display.print("20/04/2023");
  
  //display.print(clock.day);
  //display.print("/");
  //display.print(clock.month);
  //display.print("/");
  //display.print(clock.year);
  
  display.setTextSize(2);   // CURENT TIME -------------------------------
  display.setCursor(65 , 0);   
  display.print("14:00");
  
  //display.print(clock.hours);
  //display.print(":");
  //display.print(clock.minutes);
  

  display.setTextSize(1);    // NEXT MEAL TIME --------------------------
  display.setCursor(0,32);   
  display.print("Next meal: ");  
  display.setTextSize(2);  
  display.setCursor(65,25); 
  display.print("16:30");
  
  //display.print(next_meal(hour));
  //display.print(":");
  //display.print(next_meal(minute));
  
  display.setTextSize(1);     // NUMBER OF MEALS LEFT -------------------
  display.setCursor(6,55);   
  display.print("20");// storage()/Mealsize()
  display.print(" []");

  display.setCursor(52,55);   // HUMIDITY INSIDE THE RESIVOIR -----------
  display.print("20"); // Humidity()
  display.print(" %");

  display.setCursor(95,55);   // TEMPERATURE INSIDE THE RESIVOIR --------
  display.print("20");
  display.print(" ");
  display.write(0xF7);
  display.print("C");

  display.display();
  delay(50);
}
*/

/*
void Settings_screen(void){  
  display.clearDisplay();
  display.setTextColor(WHITE); 


   
  display.setCursor(5,15); // CURSOR ----------------------------------
  display.write(0x10);
    
  display.setCursor(35,0);  // HEADER ----------------------------------
  display.print("Settings: "); 

  display.setTextColor(BLACK, WHITE); 
  display.setCursor(15,15); // SCHEDULE --------------------------------   
  display.print("Schedule"); 

  display.setTextColor(WHITE); 
  display.setCursor(15,25);   // CALIBRATE------------------------------
  display.print("Calibrate");  

  display.setCursor(15,35);   // TREAT ---------------------------------
  display.print("Treat"); 

  display.setCursor(15,45);   // SOUND ---------------------------------
  display.print("Sound"); 

  display.setCursor(15,55);   // HISTORY -------------------------------
  display.print("History"); 
    
  display.display();
  delay(50);

}
*/

/*
void Schedule_screen(void){
  display.clearDisplay();
  display.setTextColor(WHITE); 

  display.setCursor(5,15); // CURSOR -----------------------------------
  display.write(0x10);
     
  display.setCursor(35,0);   // HEADER ---------------------------------
  display.print("Schedule: "); 

  display.setTextColor(BLACK, WHITE); 
  display.setCursor(15,15);   // MEAL 1 -------------------------------- 
  display.print("08:00"); 

  display.setTextColor(WHITE); 
  display.setCursor(15,25);   // MEAL 2 --------------------------------
  display.print("12:00"); 

  display.setCursor(15,35);   // MEAL 3 --------------------------------
  display.print("16:30"); 

  display.setCursor(110,55); // RETURN -----------------------------------
  display.write(0x1B);
 


  display.display();
  delay(50);

}
*/

/*
void Schedule_options(void){

  display.clearDisplay();
  display.setTextColor(WHITE); 

  display.setCursor(5,15); // CURSOR -----------------------------------
  display.write(0x10);
     
  display.setCursor(50,0);   // HEADER ---------------------------------
  display.print("08:00"); 

  display.setTextColor(BLACK, WHITE); 
  display.setCursor(15,15);   // REMOVE -------------------------------- 
  display.print("Remove"); 

  display.setTextColor(WHITE); 
  display.setCursor(15,25);   // EDIT --------------------------------
  display.print("Edid"); 

  display.setCursor(15,35);   // NEW --------------------------------
  display.print("New"); 

  display.setCursor(110,55); // RETURN -----------------------------------
  display.write(0x1B);
 

  display.display();
  delay(50);
}
*/

/*
void Schedule_editing(void){

  display.clearDisplay();
  display.setTextColor(WHITE); 

  display.setCursor(5,15); // CURSOR -----------------------------------
  display.write(0x10);
     
  display.setCursor(50,0);   // HEADER ---------------------------------
  display.print("Edit:"); 

  display.setTextColor(BLACK, WHITE); 
  display.setCursor(15,15);   // TIME OF THE MEAL --------------------- 
  display.print("Time         "); 
  display.print("08:00"); 

  display.setTextColor(WHITE); 
  display.setCursor(15,25);   // PORTION SIZE --------------------------
  display.print("Portion       "); 
  display.print("200g"); 

  display.setCursor(15,35);   // SLOW FEEDING --------------------------
  display.print("Slow           "); 
  display.print("on"); 

  display.setCursor(110,55); // RETURN ---------------------------------
  display.write(0x1B);
 
  display.display();
  delay(50);
}
*/

/*
void Schedule_time_set(void){

  display.clearDisplay();
  display.setTextColor(WHITE); 

     
  display.setCursor(50,0);   // HEADER ----------------------------------
  display.print("Time:"); 

  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE); 
  display.setCursor(32,25);   // HOUR ----------------------------------- 
  display.print("08"); 

  display.setTextColor(WHITE); 
  display.print(":"); 
 
  display.print("00");        // MINUTE ---------------------------------
  
  display.setTextSize(1);
  display.setCursor(110,55); // RETURN ----------------------------------
  display.write(0x1B);
 

  display.display();
  delay(50);
}
*/

/*
void Schedule_portion_set(void){

  display.clearDisplay();
  display.setTextColor(WHITE); 

     
  display.setCursor(44,0);   // HEADER ----------------------------------
  display.print("Portion:"); 

  display.setTextSize(2);
  display.setCursor(45,25);   // Portion size ----------------------------------- 
  display.print("100"); 
  display.print("g"); 
  
  display.setTextSize(1);
  display.setCursor(110,55); // RETURN ----------------------------------
  display.write(0x1B);
 

  display.display();
  delay(50);
}
*/

/*
void Schedule_Slow(void){

  display.clearDisplay();
  display.setTextColor(WHITE); 

  display.setCursor(5,15); // CURSOR -----------------------------------
  display.write(0x10);
     
  display.setCursor(35,0);   // HEADER ---------------------------------
  display.print("Slow mode:"); 

  display.setTextColor(BLACK, WHITE); 
  display.setCursor(15,15);   // SLOW FEEDING ON --------------------- 
  display.print("On");  

  display.setTextColor(WHITE); 
  display.setCursor(15,25);   // SLOW FEEDING OFF --------------------------
  display.print("Off"); 

  display.setCursor(110,55); // RETURN ---------------------------------
  display.write(0x1B);
 
  display.display();
  delay(50);
}
*/

/*
void Schedule_remove(void){

  display.clearDisplay();
  display.setTextColor(WHITE); 

  display.setCursor(5,15); // CURSOR -----------------------------------
  display.write(0x10);
     
  display.setCursor(20,0);   // HEADER ---------------------------------
  display.print("Remove "); 
  display.print("08:00"); 
  display.print(" ?"); 


  display.setTextColor(BLACK, WHITE); 
  display.setCursor(15,15);   // SLOW FEEDING ON --------------------- 
  display.print("Yes");  

  display.setTextColor(WHITE); 
  display.setCursor(15,25);   // SLOW FEEDING OFF --------------------------
  display.print("no"); 


  display.setCursor(110,35); // RETURN ---------------------------------
  display.write(0x1B);
 
  display.display();
  delay(50);
}
*/


// FROM THE LIBRARIE EXAMPLE ===================================================

/*
void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }

  display.display();
  delay(2000);
}
*/
