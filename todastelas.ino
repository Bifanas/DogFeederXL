#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
{
  Serial.begin(9600);
  
  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

    // Clear the buffer.
  display.clearDisplay();
  float oi = 1.5;

  // MENU INICIAL
  display.setCursor(6,3);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("hora e dia");
  display.setCursor(12,32);
  display.println("Next Meal: ");
  display.println("hora");
  display.setCursor(62,40);
  display.write(1);
  display.setCursor(0,56);
  display.println("10   43   38");
  display.display();
  display.startscrollright(0x00, 0x00);

  // SETTINGS
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Settings");
  display.setCursor(12,13);
  display.println("Schedule");
  display.println("Calibrate");
  display.println("Info/Status");
  display.println("Sound");
  display.println("History"); 
  //display.write(1B);   
  display.display();
    
  //Schedule-MAIN
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Schedule:");
  display.setCursor(12,13);
  display.println("New");
  display.println("horas");
  //display.write(1B);   
  display.display();
  
  //Schedule-TIME
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("hora");
  display.setCursor(12,13);
  display.println("Remove");
  display.println("Edit");
  display.println("New");
 //display.write(1B);   
  display.display();
  
  //Schedule-Edit/new
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Edit");
  display.setCursor(12,13);
  display.println("Time");
  display.println("Portion");
  display.println("Slow");
  //display.write(1B);   
  display.display();

  //Schedule-Edit/New-Time
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Time:");
  display.setCursor(12,13);
  display.setTextSize(2);
  display.println("HORA");
  display.println("MIN");
  //display.write(1B);   
  display.display();

  //Schedule-Edit/New-Portion
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Portion:");
  display.setCursor(12,13);
  display.setTextSize(2);
  display.println("QT");
  display.println("g");
  //display.write(1B);   
  display.display();

//Schedule-Edit/New-Time
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Slow mode:");
  display.setCursor(12,13);
  display.setTextSize(1);
  display.println("on");
  display.println("off");
  //display.write(1B);   
  display.display();  

  //Schedule-Remove
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Remove 'time' ?");
  display.setCursor(12,13);
  display.setTextSize(1);
  display.println("Yes");
  display.println("No");
  //display.write(1B);   
  display.display();  
  
  //Calibrate-MAIN
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Calibrate:");
  display.setCursor(12,13);
  display.setTextSize(1);
  display.println("Start calibration");
  //display.write(1B);   
  display.display();

  //Calibrate-2
  display.setCursor(12,13);
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.println("Dropping food...");
  display.setTextColor(WHITE);
  display.setCursor(54,48);
  display.setTextSize(1);
  display.println("Wait");  
  display.display();  
  

  //Calibrate-3
  display.setCursor(12,13);
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.println("Take the food out");
  display.display();


  //CALIBRATED
  display.setCursor(12,13);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Calibrated!");
  display.display();

  //Sound
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Sound");
  display.setCursor(12,13);
  display.println("Choose sound");
  display.println("Volume");
  //display.write(1B);   
  display.display();  

  //Sound-choose
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Choose Sound:");
  display.setCursor(12,13);
  display.println("Sound 1");
  display.println("Sound 2");
  display.println("Sound 3");
  //display.write(1B);   
  display.display();

  //Sound-volume
  display.setCursor(41,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Volume");
  display.setCursor(12,13);
  display.setTextSize(2);
  display.println("vol");
  //display.write(1B);   
  display.display();
  
  


  
  

}

void loop() {
}