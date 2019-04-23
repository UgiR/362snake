//Created by Stephen Lambert
//arduino code to display the snake direction (up,down,left,right)
//using buttons and the serial port
//declare buttons variables
#include "buzzer.h"
const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;
//declares button state variables
int bs1;
int bs2;
int bs3;
int bs4;
//sets variable for melody
int melody[] = { NOTE_C4};
int noteDuration[] = {4};
//set up function that takes in button input
void setup() {
  Serial.begin(9600);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
}
//loop function that reads the button state and prints the direction of the button pressed
void loop() {
  bs1 = digitalRead(button1);
  bs2 = digitalRead(button2);
  bs3 = digitalRead(button3);
  bs4 = digitalRead(button4);
  if(bs1 == HIGH){
    Serial.print(1);
    //iterate through notes
    for(int note = 0; note < 8; note++){
      //calculate duration
      int noteDurations = 1000 / noteDuration[note];
      tone(8,melody[note],noteDurations);
      //stop tone
      noTone(8);
    }
  }
  if(bs2 == HIGH){
    Serial.print(2);
    //iterate through notes
    for(int note = 0; note < 8; note++){
      //calculate duration
      int noteDurations = 1000 / noteDuration[note];
      tone(8,melody[note],noteDurations);
      //stop tone
      noTone(8);
    }
  }
  if(bs3 == HIGH){
    Serial.print(3);
    //iterate through notes
    for(int note = 0; note < 8; note++){
      //calculate duration
      int noteDurations = 1000 / noteDuration[note];
      tone(8,melody[note],noteDurations);
      //stop tone
      noTone(8);
    }
  }
  if(bs4 == HIGH){
    Serial.print(4);
    //iterate through notes
    for(int note = 0; note < 8; note++){
      //calculate duration
      int noteDurations = 1000 / noteDuration[note];
      tone(8,melody[note],noteDurations);
      //stop tone
      noTone(8);
    }
  }
  delay(10);
}
