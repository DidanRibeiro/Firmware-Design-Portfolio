/* TECH 3157 Lab 3 Lb 3 example
pin 8: left whisker, active LOW
pin 9: right whisker, active LOW
pin 10: piezzo buzzer
pin 11: control signal to left servo
pin 12: control signal to right servo
pin 10: tone to the piezo buzzer 
1 indicates no contact; 0 indicates contact
*/

#include <Servo.h>  // Include servo livrary
//#include <avr/io.h>

// Functions prototypes

void forward  (unsigned int time);         //full speed forward for a duration of time (ms)
void backward (unsigned int time);         // Full -speed Backward for a duration of time (ms)
void turnLeft (unsigned int time);         //Left turn for a duration of time(ms)
void turnRight(unsigned int time);         //Right turn for a duration of time(ms)
void pivotForwardLeft  (unsigned int time);
void pivotBackwardLeft (unsigned int time);
unsigned char sevenSegLED(char count);

Servo servoLeft;                            // Declare left and right servos
Servo servoRight;

void setup()                                // Built-in initialization block
{
//  DDRB &= 0b11111100;       // Set pin 8 and 9 as inputs
  DDRD &= 0b00111111;     // Set pin 7 and 6 as inputs
    
  tone (10, 3000, 1000);                      // Play tone for 1 second
  delay(500);                                // Delay to finish tone
  servoLeft.attach(11);                       // Attach left signal to pin 11
  servoRight.attach(12);                      // Attach right signal to pin 12
  Serial.begin(9600);
  Serial.flush();    
}

void loop()
{
  char message[80];
  char leftWhisker;                  // 1 indicates no contact, 0 indicates contact 
  char rightWhisker;                 // 1 indicates no contact, 0 indicates contact

 // leftWhisker  = PINB & 0x01;        // pin 8 (PINB0) is connected to the left whisker
 // rightWhisker = (PINB & 0x02)>>1;   // pin9 (PINB1) is connected to the right whisker
    leftWhisker = (PIND & 0x08)>>7; 
    rightWhisker = (PIND & 0x07)>>6;  
  sprintf(message,"LW:%x\tRW:%x\n",leftWhisker,rightWhisker);
  Serial.write(message);
  
  
 if ( (leftWhisker == 0) && (rightWhisker == 0) ) // If both whiskers are touched(contact)
    {   
      backward(1000);
      pivotBackwardLeft(1000);      
    } 
    if (leftWhisker == 0 ) // if only LW is pressed
    {      
      backward(1000); 
      turnRight(500);                               
    }   
     if (rightWhisker == 0)  // If only RW is pressed
     {     
      backward(1000);
      turnLeft(500);                  
     }    
    if ( (leftWhisker == 1) && (rightWhisker == 1) )  // If no whiskers is pressed
    {
      forward(20);
    }
    
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

