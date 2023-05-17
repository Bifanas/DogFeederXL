#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




// Rotary Encoder Inputs
#define CLK 11
#define DT 12
#define SW 13



int Cursor_nav(int number_poses) {

  int btnState = digitalRead(SW);
  
  int counter = 0;
  int currentStateCLK;
  int lastStateCLK = digitalRead(CLK);
  
  //int cu[number_poses] = {15,25,35,45,55};
  int aux = 15; // first pose

  display.setTextColor(WHITE);  


  while (1) { 
    lastStateCLK = currentStateCLK;
    currentStateCLK = digitalRead(CLK);    

    if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
      if (digitalRead(DT) != currentStateCLK) {
       // counter--;
        aux = aux - 10;
      } else {
        //counter++;
        aux = aux + 10;
      } 
      //Serial.println(counter);      
    }
  
    display.fillRect(5,8, 5, 55, BLACK);  
    display.setCursor(5,aux); // CURSOR poses( 15, 25, 35, 45, 55)-----------------------------------
    display.write(0x10);
    display.display();


    // Read the button state
    int btnState = digitalRead(SW);
    //lastButtonPress = millis();
    if (btnState == LOW) {
      break;    }
  }
  return counter;
}

void setup() {

  // Set encoder pins as inputs
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);


  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  display.clearDisplay();
  display.drawPixel(10, 10, WHITE);
  display.display();



 // Cursor_nav();


}

void loop() {

  int cu = Cursor_nav(4);
  Serial.print("the cu selected is: ");
  Serial.println(cu);

  delay(1000);
}

