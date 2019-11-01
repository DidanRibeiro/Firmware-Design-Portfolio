/* TECH 3157 Lab 3 Lb 4 example

PORTD
pin 0: read segment a of seven-segment
pin 1: read segment b of seven-segment
pin 2: read segment c of seven-segment
pin 3: read segment d of seven-segment
pin 4: read segment e of seven-segment
pin 5: read segment f of seven-segment
pin 6: read segment g of seven-segment

PORTB 
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

//  DDRB = 0b11111100;     // set pin 8 and 9  as input
  DDRB &= 0b11111100;       // Set pin 8 and 9 as inputs
  DDRD |= 0b01111111;       // Set pin 0 to 6 as output

//  DDRD &= 0b00111111;     // Set pin 7 and 6 as inputs
  
  tone (10, 3000, 1000);                      // Play tone for 1 second
  delay(500);                                // Delay to finish tone
  servoLeft.attach(11);                       // Attach left signal to pin 11
  servoRight.attach(12);                      // Attach right signal to pin 12
 // Serial.begin(9600);
 // Serial.flush();
    
  PORTD = sevenSegLED(0);   //Initialize Displaying 0 on seven-segments when start
 
}

  char pcount = 0;
  char count;
  

void loop()
{
  char message[80];
  char leftWhisker;                  // 1 indicates no contact, 0 indicates contact 
  char rightWhisker;                 // 1 indicates no contact, 0 indicates contact

  leftWhisker  = PINB & 0x01;        // pin 8 (PINB0) is connected to the left whisker
  rightWhisker = (PINB & 0x02)>>1;   // pin9 (PINB1) is connected to the right whisker
//    leftWhisker = (PIND & 0x08)>>7; 
//    rightWhisker = (PIND & 0x07)>>6;  
//  sprintf(message,"LW:%x\tRW:%x\n",leftWhisker,rightWhisker);
//  Serial.write(message);
  
  
 if ( (leftWhisker == 0) && (rightWhisker == 0) ) // If both whiskers are touched(contact)
    {
      PORTD = sevenSegLED (++pcount);
      tone(10, 3000, 100);
      backward(1000);
      pivotBackwardLeft(1000);
      //PORTD = sevenSegLED (++presscounter);
    } 
    if (leftWhisker == 0 ) // if only LW is pressed
    {
      PORTD = sevenSegLED (++pcount);
      tone(10, 3000, 100);
      backward(1000); 
      turnRight(500);                         
      //PORTD = sevenSegLED (++presscounter);
    }   
    if (rightWhisker == 0)  // If only RW is pressed
    {
      PORTD = sevenSegLED(++pcount);
      tone(10, 3000, 100);
      backward(1000);
      turnLeft(500);                  
    }    
    if ( (leftWhisker == 1) && (rightWhisker == 1) )  // If no whiskers is pressed
    {
      forward(20);
    }
    if (pcount > 9)
    {
    pcount = 0;
    tone(10,1850,500);
    delay(300);
    tone(10,700,1000);
    delay(300);
    }
       
 //   sprintf(message,"Pcounter:%d\t", pcount);
 //   Serial.write(message); 
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

// Return the seven segment LED output (commom cathode) for decimal number count(0-9)
unsigned char sevenSegLED (char count)
{
  // For common cathode 7-seg LEDs 
  unsigned char ledDisplay[] = {63,6,91,79,102,109,125,7,127,111}; // display number 0 to 9     
  if ( (0 <= count) && (count < 10) ) // If count is between the range 0 to 9 
    return ledDisplay[count];         // display corresponding LEDs for values 0-9
  else
    return 0;                         // reset back to 0 if value exceeds 9

}
  
 
