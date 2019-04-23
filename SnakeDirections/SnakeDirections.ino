//Created by Stephen Lambert
//arduino code to display the snake direction (up,down,left,right)
//using buttons and the serial port
//declare buttons variables
const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;
//declares button state variables
int bs1;
int bs2;
int bs3;
int bs4;
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
    Serial.print("This direction is up");
  }
  if(bs2 == HIGH){
    Serial.print("This direction is down");
  }
  if(bs3 == HIGH){
    Serial.print("This direction is Left");
  }
  if(bs4 == HIGH){
    Serial.print("This direction is Right");
  }
  delay(10);
}
