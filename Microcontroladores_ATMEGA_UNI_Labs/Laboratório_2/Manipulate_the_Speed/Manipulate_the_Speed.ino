/*TECH 3157 Lab 2 example 2 Ramping up to full speed forward pin 11: control signal
to Left servo pin 12: control signal to right servo pin 10: tone to the piezo buzzer 
*/

#define FORWARD  0x0  // ramp up forward
#define BACKWARD 0x2  // ramp up backward
#define UP 0x0        // ramp up forward
#define DOWN 0x1      // ramp down forward


#include <Servo.h>      // Include servo library

void forward  (unsigned int time);    //full speed forward for a duration of time (ms)
void backward (unsigned int time);    // Full -speed Backward for a duration of time (ms)
void rampMove (unsigned char control, unsigned char speedStep);
void rampingUpForward    (unsigned char speedStep =1 ); // Ramp up to full speed (speedStep between 1 to 20, default 1)
void rampingUpBackward   (unsigned char speedStep =1); 
void rampingDownForward  (unsigned char speedStep =1);
void rampingDownBackward (unsigned char speedStep =1);
void disableServos();   // Halt servo signals

Servo servoLeft;        // Declare left and right servos
Servo servoRight;

void setup() 
{
  
   tone(10, 3000, 1000);     // Play tone for 1 second
   delay(1000);              // Delay to finish the tone
   servoLeft.attach(11);     // Attach left signal to pin 11
   servoRight.attach(12);    // Attach right signal to pin 12
   
   
   //rampingUpBackward();
   //rampingUpForward();
   rampMove(FORWARD+UP,1);       // ramping up to full speed in 1 seconds 
   forward(3000);                // continue forward for 3 seconds
   rampMove(DOWN+FORWARD,1);    // ramping down to stop 
   rampMove(BACKWARD+UP,1);     // Full speed backward
   //rampMove3(DOWN+BACKWARD,2);
   //rampingDownForward();
   backward(3000);
   rampMove(DOWN+BACKWARD,1);
   //rampingDownBackward();
   //rampingUpForward(1);
   disableServos();          // Stay still indefinititely

}

void loop()
{
  }

void disableServos() 
{
  servoLeft.detach();
  servoRight.detach(); 
  }

void forward (unsigned int time)   // Full-speed Forward function

{
  servoLeft.writeMicroseconds(1625);
  servoRight.writeMicroseconds(1300);
  delay(time);    // Maneuver for time ms
  }

void backward(unsigned int time) 

{
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1613);
  delay(time);
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
  servoLeft.writeMicroseconds (1500+speed);  // us = 1500,1502,...1598,1600 
  servoRight.writeMicroseconds(1500-speed);  // us = 1500,1498,...1402,1400 
  delay(20);                                 // 20 ms at each speed
  } 
}

void rampingUpBackward (unsigned char speedStep)
{
  if (speedStep == 0 or speedStep > 20)
  speedStep = 20; // if the speedStep is out of range [1..20], set to 20
  for(int speed = 0; speed <=100 ; speed += speedStep) // 
{
  servoLeft.writeMicroseconds (1600-speed);  // us = 1500,1502,...1598,1600 
  servoRight.writeMicroseconds(1500+speed);  // us = 1500,1498,...1402,1400 
  delay(20);                                 // 20 ms at each speed
  }  
}

void rampingDownForward(unsigned char speedStep)
{

    if (speedStep == 0 or speedStep > 20)
        speedStep = 20; // if the speedStep is out of range [1..20], set to 20
        for (int speed = 100; speed >= 0; speed -= speedStep)
        {
          servoLeft.writeMicroseconds(1500+speed);  // t_pulse = 1600,1598,...1502,1500 us
          servoRight.writeMicroseconds(1600-speed); // t_pulse = 1400,1402,...1498,1500 us 
          delay(20);            // 20 ms at each speed
          }
}

void rampingDownBackward (unsigned char speedStep)
{
  if (speedStep == 0 or speedStep > 20)
  speedStep = 20; // if the speedStep is out of range [1..20], set to 20
  for (int speed = 100; speed >= 0; speed -= speedStep)
   {
   servoLeft.writeMicroseconds(1500-speed);  // t_pulse = 1600,1598,...1502,1500 us
   servoRight.writeMicroseconds(1600+speed); // t_pulse = 1400,1402,...1498,1500 us 
   delay(20);            // 20 ms at each speed
   }

}

void rampMove (unsigned char control, unsigned char speedStep)

{
//  #define FORWARD  0x0  // ramp up forward
//  #define BACKWARD 0x2  // ramp up backward
//  #define UP 0x0        // ramp up forward
//  #define DOWN 0x1      // ramp down forward

//   control = 0x0; //ramp up forward   FORWARD+UP
//   control = 0x1; //ramp down forward   DOWN+FORWARD
//   control = 0x2; // ramp up backward   BACKWARD+UP
//   control = 0x3; // ramp down backward     DOWN+BACKWARD

  if (control == 0x0) rampingUpForward(speedStep); 
  /*{
  control = 0x0; //ramp up forward   FORWARD+UP
 // if (speedStep == 0 or speedStep > 20)
   // speedStep = 20; // if the speedStep is out of range [1..20], set to 20
  for(int speed = 0; speed <= 100; speed += speedStep) // 
  {
    servoLeft.writeMicroseconds (1500+speed);  // us = 1500,1502,...1598,1600 
    servoRight.writeMicroseconds(1500-speed);  // us = 1500,1498,...1402,1400 
    delay(20);                                 // 20 ms at each speed
  }   
  }*/
  if (control == 0x1) rampingDownForward(speedStep); 
  if (control == 0x2) rampingUpBackward(speedStep);
  if (control == 0x3) rampingDownBackward(speedStep);
 
}
// others: do not move and output warning in the serial output
// rampMove (FORWARD+UP,2) make the robot to ramp up from stop to full speed forward in 1s
 
/* end of example 3 */

