/* Robotics with the BOE Shield - Servos Stay Still Lab1 - Example 2
 *  Transmit the center or stay still signal on pin 12 for center adjustment.
 */

#include <Servo.h>    // Include Servo Library

Servo myServo;         // Declare the servo for test

void setup() 

{

  myServo.attach(11);               // ttach right signal to pin 12
  myServo.writeMicroseconds(1500);  // 1.5 ms stay still signal

}

void loop() {
  

}
