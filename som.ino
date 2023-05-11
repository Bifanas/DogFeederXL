#include <SoftwareSerial.h>
#include "RedMP3.h" //MP3 maroto

#define volume_Pot A0
#define ARDUINO_RX 7 //mp3
#define ARDUINO_TX 8 //mp3
MP3 mp3(ARDUINO_RX, ARDUINO_TX); //MP3

int8_t musica1 = 0x01; //primeira música do cartão SD
int8_t musica2 = 0x02; //segunda música do cartão SD
int8_t musica3 = 0x03; //terceira música do cartão SD
int8_t folderName = 0x01; //pasta do cartão
int8_t lastVolume; //volume atual

void setup() {
  Serial.begin(9600);
  delay(500); //delay de 500ml pra iniciar o mp3
  mp3.setVolume(lastVolume); //selecionar o volume
}

void playTrack(String str, int8_t lastVolume){ //função das músicas
  if(str == "1"){ //primeira música
    mp3.playWithVolume(musica1, lastVolume);
    Serial.println("First sound track.");
  }
  else if(str == "2"){ //segunda música
    mp3.playWithVolume(musica2, lastVolume);
    Serial.println("Second sound track.");
  }
  else if(str == "3"){ //terceira música
    mp3.playWithVolume(musica3, lastVolume);
    Serial.println("Third sound track.");
  }
}

void adjustVolume(int8_t lastVolume){ //ajustar volume
  int volume = map(analogRead(volume_Pot),0,1024,0,30); //mapeamento do volume de 1 a 30
  
  if (volume != lastVolume) {
    mp3.setVolume(volume);
    Serial.print("pot set to: ");Serial.println (volume_Pot);
    Serial.print("volume set to: "); Serial.println (volume);
    lastVolume = volume;
  }
}

void loop() { 
  adjustVolume(lastVolume); //função do volume
  
  delay(50); //delay pra ajustar 
  
  if(Serial.available()){ //aqui ele le o serialbegin, mas na telinha seria o menu
    String str = Serial.readStringUntil('\n');
    playTrack(str, lastVolume);
  }
}
