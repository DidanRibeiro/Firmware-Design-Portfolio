/*TECH 3157 Lab 2 example 2 Ramping up to full speed forward pin 11: control signal
to Left servo pin 12: control signal to right servo pin 10: tone to the piezo buzzer 
*/

#include <Servo.h>      // Include servo library

void rampMove (unsigned char control, unsigned char speedStep);
void forward  (unsigned int time);  //full speed forward for a duration of time (ms)
void turnLeft (unsigned int time);  //Leftturnfor adurationoftime(ms)
void turnRight(unsigned int time);  //Rightturnfor adurationoftime(ms)
void backward (unsigned int time);  // Full -speed Backward for a duration of time (ms)
void pivotForwardLeft  (unsigned int time);
void pivotBackwardLeft (unsigned int time);
void pivotForwardRight (unsigned int time);
void pivotBackwardRight(unsigned int time); 
void rampingUpForward(unsigned char speedStep =1 ); // Ramp up to full speed (speedStep  between 1 to 20, default 1) 
void disableServos();   // Halt servo signals

Servo servoLeft;        // Declare left and right servos
Servo servoRight;

void setup() 
{
  
tone(10, 3000, 1000);     // Play tone for 1 second
delay(1000);              // Delay to finish the tone

servoLeft.attach(11);     // Attach left signal to pin 11
servoRight.attach(12);    // Attach right signal to pin 12


forward(2000);
pivotForwardLeft(4000);
pivotBackwardLeft(4000);
forward(2000);
pivotBackwardRight(1000);
pivotForwardRight(2000);
pivotBackwardRight(1000);
backward(3000);


//rampingUpForward();       // ramping up to full speed in 2 seconds 
//forward(2000);            // continue forward for 2 seconds
disableServos();          // Stay still indefinititely

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

void backward(unsigned int time)  // Full-speed Backward funtion

{
servoLeft.writeMicroseconds(1300);
servoRight.writeMicroseconds(1613);
delay(time);
}

void pivotForwardLeft  (unsigned int time)
{
  servoLeft.writeMicroseconds(1500);  // Left wheel stay still
  servoRight.writeMicroseconds(1300); // Right wheel clockwise
  delay(time);
}

void pivotBackwardLeft (unsigned int time)
{
  servoLeft.writeMicroseconds(1500);  // Left wheel clockwise
  servoRight.writeMicroseconds(1700); // Right wheel stay still
  delay(time);
}

void pivotForwardRight (unsigned int time)
{
  servoLeft.writeMicroseconds(1300);  // Left wheel counterclockwise
  servoRight.writeMicroseconds(1500);  // Right wheel stay still
  delay(time);
}

void pivotBackwardRight (unsigned int time)
{
  servoLeft.writeMicroseconds(1700);  
  servoRight.writeMicroseconds(1500); 
  delay(time);
}

void disableServos() 

{
servoLeft.detach();
servoRight.detach(); 
} 


/* Ramp up to full speed. Allowed speed step is between 1 to 20. 
 *  Time to ramp up to full speed from stop = (2/speedStep) seconds For example, 
 *  speedStep is 1: ramp up to full speed in 2 seconds
    2: ramp up to full speed in 1 seconds
    4: ramp up to full speed in 0.5 seconds
    20: ramp up to full speed in 0.1 seconds */
    
void rampingUpForward(unsigned char speedStep) 
{
if (speedStep == 0 or speedStep > 20)
  speedStep = 20; // if the speedStep is out of range [1..20], set to 20
for(int speed = 0; speed <= 100; speed += speedStep) // 
{
  servoLeft.writeMicroseconds(1500+speed); // us = 1500,1502,...1598,1600 servoRight.writeMicroseconds(1500-speed); // us = 1500,1498,...1402,1400 delay(20); // 20 ms at each speed
} 

}

/* 
   for (int speed = 100; speed >= 0; speed -= speedStep)
   {
   servoLeft.writeMicroseconds(1500+speed);  // t_pulse = 1600,1598,...1502,1500 us
   servoRight.writeMicroseconds(1500-speed); // t_pulse = 1400,1402,...1498,1500 us 
   delay(20);            // 20 ms at each speed
 */


/* end of example 3 */


