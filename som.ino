#include <SoftwareSerial.h>
#include "RedMP3.h"

#define volume_Pot A0//SIG pin of Rotary Angle Sensor module connect to A0 of IO Shield, that is pin A0 of Arduino
#define playpause 3
#define ARDUINO_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define ARDUINO_TX 8//TX to D8, note that D8 can not be used as RX on Mega2560, you should modify this if you donot use Arduino UNO
MP3 mp3(ARDUINO_RX, ARDUINO_TX);

int8_t musica1 = 0x01;
int8_t musica2 = 0x02;
int8_t musica3 = 0x03;
int8_t folderName = 0x01;
int8_t lastVolume;


void setup() {
Serial.begin(9600);
  delay(500);
  mp3.setVolume(lastVolume);
 // mp3.playWithVolume(musica2, lastVolume);
}

String str;
void loop() { 
   int volume = map(analogRead(volume_Pot),0,1024,0,30);
  
  if (volume != lastVolume) {
    mp3.setVolume(volume);
    Serial.print("pot set to: ");Serial.println (volume_Pot);
   Serial.print("volume set to: "); Serial.println (volume);
    lastVolume = volume;
 }
 delay(50);
if(Serial.available())
{
str = Serial.readStringUntil('\n');
if(str == "1")
{
mp3.playWithVolume(musica1, lastVolume);//play the second track with volume 30 class
Serial.println("First sound track.");
}
if(str == "2")
{
mp3.playWithVolume(musica2, lastVolume);//play the second track with volume 30 class
Serial.println("Second sound track.");
}
if(str == "3")
{
mp3.playWithVolume(musica3, lastVolume);//play the third track with volume 30 class
Serial.println("Third sound track.");
}
}
}
