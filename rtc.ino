#include "Arduino.h"
#include "uRTCLib.h"
uRTCLib rtc(0x68);  // uRTCLib rtc;


void setup() {
  Serial.begin(9600);
   URTCLIB_WIRE.begin();

  //rtc.set(0, 26, 17, 5, 19, 5, 23); // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
}


void loop() {

  rtc.refresh();

  char cu[6][3];

  itoa(rtc.second(), cu[2], 10);
  itoa(rtc.minute(), cu[1], 10);
  itoa(rtc.hour(), cu[0], 10);
  S
  itoa(rtc.day(), cu[3], 10);
  itoa(rtc.month(), cu[4], 10);
  itoa(rtc.year(), cu[5], 10);

  for (byte i = 0; i < 6; i = i + 1) {
    Serial.print(cu[i]);
    Serial.print("/");
  }
  delay(1000);
  Serial.println(" ");
}