/*Final Code
 * pin 8: left whisker, active LOW
  pin 9: right whisker, active LOW
  pin 10: piezzo buzzer
  pin 11: control signal to left servo
  pin 12: control signal to right servo
  Display IR detector output resutls
  pin 3 - Timer 2 Ch. B is used to generate 38 KHz signal * pin 3 -- left IR receiver output

  1 indicates no object  and 0 indicates theres object 
 
*/

#include <AVR/io.h>
#define ADC_PreScaler_128  0x7
#define ADC3 3
#define FORWARD  0x0  // ramp up forward
#define BACKWARD 0x2  // ramp up backward
#define UP 0x0        // ramp up forward
#define DOWN 0x1      // ramp down forward

#include <Servo.h>      // Include servo library
#include <avr/io.h>

void forward  (unsigned int time);         //full speed forward for a duration of time (ms)
void backward (unsigned int time);         // Full -speed Backward for a duration of time (ms)
void turnLeft (unsigned int time);         //Left turn for a duration of time(ms)
void turnRight(unsigned int time);         //Right turn for a duration of time(ms)
void pivotForwardLeft  (unsigned int time);
void pivotBackwardLeft (unsigned int time);
void pivotFowardRight(unsigned int time);
void pivotBackwardRight(unsigned int time);

char irDetect(char irReceiverPin);
char irDetect2(char irReceiverPin2);
unsigned long rcTime(char ADCpin, int  threshold);
unsigned int voltsLevel(char ADCpin);

void carrierInit();
void pwmEnable();
void pwmDisable();
void disableServos(); // Halt servo signals

Servo servoLeft;        // Declare left and right servos
Servo servoRight;

char message[80];

int Begin = 0;


void setup()
{


  servoLeft.attach(11);     // Attach left signal to pin 11
  servoRight.attach(12);    // Attach right signal to pin 12

  DDRB &= 0b11111100;       // Set pin 8 and 9 as inputs
  /*REFS = 01 Internal 5V reference; ADLAR = 0 right adjusted; MUX3:0 = 0011 single-ended ADC3
   (pin A3 in Arduino board) 
  */
//  ADMUX = 0x40 | 0x03;      // Set Analog pin output 3
  /*ADCSRA: ADEN = 1 ADC enabled
            ADATE = 1 ADC Auto TRigger enable
    ADPS2:0 = 111 prescaler = 128 
   */
  ADCSRA |= ((1<<ADEN) | (1<<ADATE) | ADC_PreScaler_128);
  
  //ADCSRB: fADC auto Trigger Scoursce: free running mode
  ADCSRB = 0;
  
//  tone (10, 3000, 1000);    // Play tone for 1 second
//  delay(1000);              // Delay to finish the tone

// DDRD &= 0xEF;
//USE Timer1 to generate 38 KHz  carrier 
  carrierInit();
  Serial.begin(9600);
  
}


void loop()  {
  
char irLeft;
char irRight;
char leftWhisker;                  // 1 indicates no contact, 0 indicates contact 
char rightWhisker;                 // 1 indicates no contact, 0 indicates contact
unsigned long light;


leftWhisker  = PINB & 0x01;        // pin 8 (PINB0) is connected to the left whisker
rightWhisker = (PINB & 0x02)>>1;   // pin9 (PINB1) is connected to the right whisker

//light = rcTime(ADC3, 10);

pwmEnable();
delay(1);
pwmDisable();

  
irRight= irDetect(5);
irLeft = irDetect2(13);

sprintf(message, "irLeft = %d   irRight = %d \n ", irLeft, irRight);
Serial.write(message);

delay(400);



  if (Begin)
  {

   if(irRight)
    {
      turnLeft(200);
    }
    else 
    if(irLeft)
    {
      turnLeft(200);
    }
    else 
    if(irLeft || irRight)
    {
      backward(300);
      turnRight(200);
    }
    else 
    if (!leftWhisker || !rightWhisker)
    {
      backward(200);
      turnRight(200);
    }
    else 
    if(light < 400)
    {
      Begin = 0;
      //tone(10,1500,1000);
    }
  }
  /*
  else
  {
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
  }
  delay(100);
  }
  */
}


  /*
  if ( (irRight == 1) && (irLeft == 1) )
  {
    backward(1000);
    pivotBackwardLeft(1000);
  }

  if ( (irRight == 1) && (irLeft == 0) )
  {
    backward(300);
    turnLeft(300);
  }

  if ( (irRight == 0) && (irLeft == 1) )
  {
    backward(300);
    turnRight(300);
  }

  if ( (irRight == 0) && (irLeft == 0) )
  {
    forward(25);
  } 

  if (light < 400)
  {
    Begin = 0;
  }
*/

void disableServos() // Halt servo signals
{
  servoLeft.detach(); // Stop sending servo signals
  servoRight.detach();
}

void forward (unsigned int time)   // Full-speed Forward function
{
servoLeft.writeMicroseconds(1700);
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
servoRight.writeMicroseconds(1700);
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

void carrierInit()
{
/*intialized timer 1 for frequency 38KHz, OC1B at PB2(pin 10)
//1 ms delay. The transmission length should <= 1.2 ms
phase-correct pwm, Ch.B, prescaler=1, 50% duty ratio*/ 
/*  */
DDRD |=  0x08;   // 0x04;     // Pino 3
TCCR2A = 0x21;   // 0b0100 0010     0x32        0b0010 0010 //0x23;    //0b00100011
TCCR2B = 0x09;   // 0x09                      //0b00010001
OCR2A = 211;     // 16M/2/38K = 211
OCR2B = OCR2A *0.5;
}

void pwmEnable()
{  
/*enable Timer1 Channel B OC1B at PB2(pin 10)
*/
TCCR2A = 0x21;  // 0x21 //0b00100011
}
void pwmDisable()
{
TCCR2A = 0x00; //discount OC0A and OC0B.
}

char irDetect(char irReceiverPin)
{
  irReceiverPin = (PIND & 0x20) >> 5; //get the status infrared receiver at pin 5
  return irReceiverPin;
}

char irDetect2(char irReceiverPin2)
{
  irReceiverPin2 = (PINB & 0x20) >> 5; //get the status infrared receiver at pin 13
  return irReceiverPin2;
}

unsigned int voltsLevel(char ADCpin)
{
  unsigned int adcread;
  //disable Digital input at ADCpin
  DIDR0 |= (1 << ADCpin);
  ADCSRA |= (1 << ADSC); //start conversion
  while ((ADCSRA & (1 << ADIF)) == 0); //wait till conversion is finished
  adcread = ADCL; //read low byte first
  adcread = (((int) ADCH) << 8) + adcread; //read high byte
  return adcread;
}

unsigned long rcTime(char ADCPin, int threshold)
{
  ADMUX = 0x40 | ADCPin;
  DDRC |= (1 << ADCPin);
  PORTC |= (1 << ADCPin);
  delay(1);
  DDRC &= (0 << ADCPin);
  PORTC &= (0 << ADCPin);
  unsigned long time = micros();
  while (voltsLevel(ADCPin) > threshold);
  time = micros() - time;
  return time;
}


