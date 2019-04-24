//Created by Stephen Lambert
//arduino code to display the snake direction (up,down,left,right)
//using buttons and the serial port
//declare buttons variables
#include "buzzer.h"
#include <LiquidCrystal.h>
#include <String.h>
const int button1 = 6;
const int button2 = 7;
const int button3 = 8;
const int button4 = 9;
//declares button state variables
int bs1;
int bs2;
int bs3;
int bs4;
//lcd display variables
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//sets variable for melody
int melody[] = { NOTE_C4};
int noteDuration[] = {4};
//set up function that takes in button input
void setup() {
  Serial.begin(9600);
  lcd.begin(2, 2);
  lcd.setCursor(0, 0);
  lcd.print("The Snake Game");
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
  digitalWrite(button1,HIGH);
  digitalWrite(button2,HIGH);
  digitalWrite(button3,HIGH);
  digitalWrite(button4,HIGH);
}
//loop function that reads the button state and prints the direction of the button pressed
void loop() {
  lcd.setCursor(0, 1);
  bs1 = digitalRead(button1);
  bs2 = digitalRead(button2);
  bs3 = digitalRead(button3);
  bs4 = digitalRead(button4);
  //check if pin is pressed
  if(bs1 == LOW){
    Serial.print(2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("The Snake Game");
    lcd.setCursor(0, 1);
    lcd.print("Going right");
    //iterate through notes
    for(int note = 0; note < 1; note++){
      //calculate duration
      int noteDurations = 1000 / noteDuration[note];
      tone(10,melody[note],noteDurations);
      //stop tone
      noTone(10);
    }
    digitalWrite(button1,HIGH);
  }
  if(bs2 == LOW){
    Serial.print(4);
     lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The Snake Game");
      lcd.setCursor(0, 1);
      lcd.print("Going down");
    //iterate through notes
    for(int note = 0; note < 1; note++){
      //calculate duration
      int noteDurations = 1000 / noteDuration[note];
      tone(10,melody[note],noteDurations);
      //stop tone
      noTone(10);
    }
    digitalWrite(button2,HIGH);
  }
  if(bs3 == LOW){
    Serial.print(3);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("The Snake Game");
     lcd.setCursor(0, 1);
     lcd.print("Going up");
    //iterate through notes
    for(int note = 0; note < 1; note++){
      //calculate duration
      int noteDurations = 1000 / noteDuration[note];
      tone(10,melody[note],noteDurations);
      //stop tone
      noTone(10);
    }
    digitalWrite(button3,HIGH);
  }
  if(bs4 == LOW){
    Serial.print(1);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("The Snake Game");
      lcd.setCursor(0, 1);
     lcd.print("Going left");
    //iterate through notes
    for(int note = 0; note < 1; note++){
      //calculate duration
      int noteDurations = 1000 / noteDuration[note];
      tone(10,melody[note],noteDurations);
      //stop tone
      noTone(10);
    }
    digitalWrite(button4,HIGH);
  }
  //write all pins to high, so the program knows the buttons arent pressed
  digitalWrite(button1,HIGH);
  digitalWrite(button2,HIGH);
  digitalWrite(button3,HIGH);
  digitalWrite(button4,HIGH);
}
