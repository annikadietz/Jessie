
// Require all the libs
#include "lib/helper.h"
#include "lib/lcd.h"
#include "engine.h"
#include "bluetooth.h"
#include "lib/pinger.h"
#include "infraRed.h"

#include <Wire.h>


#include <SoftwareSerial.h>
SoftwareSerial mySerial(A1, A0); // RX, TX
int a=0;
char c;
char d;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


int state = 0;



int mid = 0;
int mn = 0;
int mx = 0;



void setup() {

  // Enable the serial port to display log messages
  
  
  //Serial.begin(9600);
  // initialize the LCD
  lcd.begin();
  
  // Turn on the blacklight
  lcd.backlight();
  
  // Show the init message
 lcd.print("Jessie - Ready");
  delay(1000);
  lcd.clear();
  lcd.print("Jessie - ");
  lcd.print("Engine booting up");
  delay(2000);

  //Default communication rate of the Bluetooth module
  Serial.begin(9600);

  pinMode(leftIRPin, INPUT);
  pinMode(rightIRPin, INPUT);
  pinMode(left_wheel, OUTPUT);
  pinMode(right_wheel, OUTPUT);
  pinMode(left_wheel_backwards, OUTPUT);
  pinMode(right_wheel_backwards, OUTPUT);


  int val = 0;
for(int j=10; j<=11; j++)//Calibrating the sensor, finding max and 
{                        //min reflectance values.
val = analogRead(j);
if(val >= mx)
mx = val;
if(val <= mn)
mn = val;
}
delay(1);


mid = ((mx + mn)/2);
}

void loop() {
   lcd.clear();
 

  //followLine();
  //driveAroundObjects();
  //solveMazeTwo();
  //testIR();
  turnAround();
  delay(5000);
}

void driveByPC()
{
  if(Serial.available() > 0)
  {
    state = Serial.read();
    Serial.println("Dude");
  }
  if (state == '0')
  {
    lcd.clear();
    halt();
    lcd.print("Stop");
  }
  else if(state == '1')
  {
    lcd.clear();
    straight();
    lcd.print("Drive");
  }
}

void followLine()
{
  if(!(digitalRead(leftIRPin)) && digitalRead(rightIRPin))     // Turn right
  {
    turnRight();
    delay(1);
  }
  
  else if(digitalRead(leftIRPin) && !(digitalRead(rightIRPin)))     // turn left
  {
    turnLeft();
    delay(1);
  }
  
  else if((digitalRead(leftIRPin)) && (digitalRead(rightIRPin)))     // stop
  {
     halt();
  }
  else
  {
    straight();
    delay(10);
    halt();
  }
  
}


void driveAroundObjects()
{
  if(object_detected(40)){
      lcd.print("Detected");
      halt();
      turnLeft();
   } else {
      lcd.print("Not Detected");
      forwardSpeed(10);
   }
}

void solveMaze()
{
  while(!(digitalRead(leftIRPin)) && (digitalRead(rightIRPin)))
  {
    forwardSpeed(10);
    delay(10);
  }
  if(!digitalRead(rightIRPin))
  {
    moveRight(10);
    delay(10);
  }
  else if(digitalRead(leftIRPin) && digitalRead(rightIRPin))
  {
    moveRight(10);
    delay(10);
  }
}

void testIR()
{
  if(digitalRead(rightIRPin))
  {
    lcd.print("Right");
  }
  if(!digitalRead(rightIRPin))
  {
    lcd.print("!Right");
  }
  if(digitalRead(leftIRPin))
  {
    lcd.print("Left");
  }
  if(!digitalRead(leftIRPin))
  {
    lcd.print("!Left");
  }
  delay(1000);
  
}

void solveMazeTwo()
{
  boolean inLeftTurn = false;
  while(!digitalRead(rightIRPin) && !object_detected(30))
  {
    //straight
    forwardSpeed(100);
    delay(5);
  }
  if(digitalRead(leftIRPin) && !digitalRead(rightIRPin) && object_detected(30))
  {
    // turn left
    halt();
    delay(100);
    inLeftTurn = true;
    while(digitalRead(leftIRPin))
    {
      turnLeft();
    }
    inLeftTurn = false;
  }
  else if(digitalRead(rightIRPin) && !inLeftTurn)
  {
    //turn right
    halt();
    delay(100);
    while(digitalRead(rightIRPin))
    {
      turnRight();
    }
    
  }
  else if(!digitalRead(leftIRPin) && !digitalRead(rightIRPin) && object_detected(30))
  {
    //turn around
    halt();
    delay(100);
    turnAround();
  
  
  }
  
}

