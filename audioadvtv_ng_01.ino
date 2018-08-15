// Audio Advent Calendar
// (c) by Mischka 2011-2018 (mischka@mailbox.org)
// Licensed under CC0

// feel free to optimize and modify the code, please share your
// mods on the internet and send me a mail with the link

// V 0.2: code is basically working
// V 0.3: code works like expected
  

/* Todo:
  - add more comments for make readers
  */ 

#include <JQ6500_Serial.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "RTClib.h"

JQ6500_Serial mp3(2,3); //create an mp3 object
RTC_DS1307 rtc;         //create an rtc object

void setup() {
  Serial.begin(57600);
  Serial.println("Audio Advent Calendar by Mischka");
  Serial.println("----");
  
  pinMode(4, INPUT);
  pinMode(13, OUTPUT);

// setup the mp3 module 
  mp3.begin(9600);
  mp3.reset();
  delay(500);
  mp3.setVolume(22);
  mp3.setLoopMode(MP3_LOOP_NONE);

// setup rtc
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  
  DateTime now = rtc.now();
  
  if(mp3.getStatus() != MP3_STATUS_PLAYING) {
    if (now.day() < 25){
      if (now.month() == 12) {

        Serial.print("playing track Number: ");
        Serial.println(now.day());

        mp3.playFileNumberInFolderNumber(0, now.day());      
      }
      else{
        Serial.println("not an advent day");
        delay(100);
        exit(0);
      }
    }
  }
exit(0);  
}



