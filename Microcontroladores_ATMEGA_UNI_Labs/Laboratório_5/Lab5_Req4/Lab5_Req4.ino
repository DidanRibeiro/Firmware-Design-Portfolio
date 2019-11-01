/* Lab 5 Example 3
* Robotics with the BOE Shield - Phototransistor connection using RC circuit 
* * Display the discharge time in microseconds
* in the serial monitor.
*/
#include <AVR/io.h>
#define ADC_PreScaler_128  0x7
#define ADC3 3
#define ADC4 4
#define FORWARD  0x0  // ramp up forward
#define BACKWARD 0x2  // ramp up backward
#define UP 0x0        // ramp up forward
#define DOWN 0x1      // ramp down forward


unsigned long rcTime(char ADCpin, int  threshold);
unsigned int voltsLevel(char ADCpin);
#include <Servo.h>      // Include servo library

void forward  (unsigned int time);    //full speed forward for a duration of time (ms)
void backward (unsigned int time);    // Full -speed Backward for a duration of time (ms)
void rampMove (unsigned char control, unsigned char speedStep);
void turnRight(unsigned int time);
void turnLeft(unsigned int time);
void disableServos();   // Halt servo signals

Servo servoLeft;        // Declare left and right servos
Servo servoRight;


void setup()
{
   tone(10, 3000, 1000);     // Play tone for 1 second
   delay(1000);              // Delay to finish the tone
   servoLeft.attach(11);     // Attach left signal to pin 11
   servoRight.attach(12);    // Attach right signal to pin 12
  Serial.begin(9600);
// Built-in initialization block
// Set data rate to 9600 bps
/*REFS = 01 Internal 5V reference; ADLAR = 0 right adjusted;  
MUX3:0 = 0011 single-ended ADC3 (pin A3 in Ariduino board) */
//ADMUX = 0x40 | 0x03;
            /*ADCSRA: ADEN = 1 ADC enabled
            ADATE = 1 ADC Auto TRigger enable
            ADPS2:0 = 111 prescaler = 128 */            
    ADCSRA |= ((1<<ADEN) | (1<<ADATE) | ADC_PreScaler_128);
    //ADCSRB: fADC auto Trigger Scoursce: free running mode
    ADCSRB = 0;
    //disable Digital input at ADC3
    //DIDR0 |= (1<<ADC3D);
}

void loop() 
{

 char message[80];
 unsigned long tLeft;
 unsigned long tRight;
 char ndShade;            // Zeroed Normalized differential shade
 
tLeft = rcTime(ADC3, 5) ;    //wait till the read from ADC3 
tRight = rcTime(ADC4, 5);   //wait till the read from ADC4 
ndShade = (tRight*100) / (tLeft + tRight) - 50;
/*
sprintf(message, "\n   tLeft = %lu \n", tLeft);
Serial.write(message);
sprintf(message, "\n   tRight = %lu ", tRight);
Serial.write(message);
*/
sprintf(message, "\n   ndShade = %d ", ndShade);
Serial.write(message);

if (ndShade > 0)
{
  servoLeft.writeMicroseconds(1625 - (ndShade*5));
  servoRight.writeMicroseconds(1300);
}
else if (ndShade < 0)
{
  servoLeft.writeMicroseconds (1625);
  servoRight.writeMicroseconds(1300 - (ndShade*5));
}
else
{
  forward(300);
}

}


unsigned int voltsLevel(char ADCpin)
{
  unsigned int adcread;
  //disable Digital input at ADCpin
  DIDR0 |= (1<<ADCpin);                  
  ADCSRA |= (1<<ADSC);
  while ((ADCSRA&(1<<ADIF)) == 0);
  adcread = ADCL;
  adcread = (((int) ADCH) << 8) + adcread; //read high byte 
  return adcread;
}

unsigned long rcTime(char ADCpin, int  threshold)
{
  char message[80];
  ADMUX = 0x40 | ADCpin;
  DDRC |= (1<<ADCpin);       //0x08; //set pin A3 (portC.3) as an output
  PORTC |= (1<<ADCpin);     //0x08; //output HIGH at pin A3
  delay(1); //hold 5V for 1 ms to allow charging the capacitor 
  DDRC &= ~(1<<ADCpin);     // 0x08 set pin A3 as an input
  PORTC &= ~(1<<ADCpin);    //0x08 disconnect the pullup-resistor to allow discharge
  unsigned long time = micros();
  while (voltsLevel(ADCpin>threshold)); //wait till the read from ADC3 
  time = micros() - time;
  return time;

//  sprintf(message, "\n rctime = %lu", time);
//  Serial.write(message);
//    sprintf(message, "\n threshold = %lu", threshold);
//Serial.write(message);
}

void forward (unsigned int time)   // Full-speed Forward function

{
  servoLeft.writeMicroseconds(1625);
  servoRight.writeMicroseconds(1300);
  delay(time);    // Maneuver for time ms
  }


void turnRight(unsigned int time)   // Right turn function
{
servoLeft.writeMicroseconds(1700);
servoRight.writeMicroseconds(1700);
delay(time);     // Maneuver for time ms
}

void turnLeft(unsigned int time)  // Left turn function
{
servoLeft.writeMicroseconds(1300);
servoRight.writeMicroseconds(1300);
delay(time);  // Maneuver for time ms
}

