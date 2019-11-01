/*TECH 3157 Lab 1 example 4
Robotbasicnavigation: Move forward full-speed,turnleft,turnright,and 
full-speedbackward
pin 11: control signal to Left servo
pin 12: control signal to right servo
pin 10: tone to the piezo buzzer
*/

#include<Servo.h>   // Include servo library

void forward  (unsigned int time);  //full speed forward for a duration of time (ms)
void turnLeft (unsigned int time);  //Leftturnfor adurationoftime(ms)
void turnRight(unsigned int time);  //Rightturnfor adurationoftime(ms)
void backward (unsigned int time);  // Full -speed Backward for a duration of time (ms)
void disableServos();               // Halt servo signals

Servo servoLeft;                     // Declare left and right servos
Servo servoRight;

void setup() {

  tone(10,3000,1000);     // Play tone for 1 second on pin2
  delay(1000);            // Delay to finish tone

  servoLeft.attach(11);   // Attach left signal to pin 11
  servoRight.attach(12);  // Attach right signal to pin 12
 
  forward(10000);          // Go forward for 2.5 seconds
  turnLeft(0);          // Turn left for 0.8 seconds
  turnRight(0);         // Turn right for 0.8 seconds
  backward(10000);         // go backward for 2.5 seconds

  disableServos();        // Stay still indefinitely

}

void loop() 
{
}

void forward (unsigned int time)   // Full-speed Forward function

{
servoLeft.writeMicroseconds(1625);
servoRight.writeMicroseconds(1300);
delay(time);    // Maneuver for time ms
}

void turnLeft(unsigned int time)  // Left turn function

{
servoLeft.writeMicroseconds(1300);
servoRight.writeMicroseconds(1300);
delay(time);  // Maneuver for time ms
}

void turnRight(unsigned int time)   // Right turn function

{
servoLeft.writeMicroseconds(1700);
servoRight.writeMicroseconds(1700);
delay(time);     // Maneuver for time ms
}

void backward(unsigned int time) 

{
servoLeft.writeMicroseconds(1300);
servoRight.writeMicroseconds(1613);
delay(time);
}

void disableServos() 

{
servoLeft.detach();
servoRight.detach(); 
} 

// End of lab 1 Exampl4

