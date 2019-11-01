/*
Robotics with the BOE Shield – ServoTest Lab 1 – Exa mple 3
Test the center or stay still signal on pin 12 for center adjustment. 
*/


#include <Servo.h>    // Include Servo Library

Servo myServo;         // Declare the servo for test


void setup() {

  myServo.attach(11);                // Servo is connected to digitalpin  (right servo)
  myServo.writeMicroseconds(1550);   //Counterclockwise
  delay(10000);                      //Wait3seconds
  myServo.writeMicroseconds(1500);   //Stop
  delay(1000);                       //Wait1seconds
//  myServo.writeMicroseconds(1300);   //Clockwise 
//  delay(3000);                       //Wait3seconds
//  myServo.writeMicroseconds(1500);   // staystill

}

void loop() {

}
