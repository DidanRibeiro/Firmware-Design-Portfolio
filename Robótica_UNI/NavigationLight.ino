/* Final project Author: Didan Junqueira Ribeiro */

#include <Servo.h> // Include servo library
#include <avr/io.h>

#define ADC1 1
#define ADC0 3
#define ADC_PreScaler_128 0x7

void forward(unsigned int time); //full speed forward for a duration of time (ms)
void turnLeft(unsigned int time); // Left turn for a duration of time (ms)
void turnRight(unsigned int time); // Right turn for a duration of time (ms)
void backward(unsigned int time); // Full-speed Backward for a duration of time (ms)
void CurvaD();
void CurvaE();

char irDetect(char irReceiverPin);    
char irDetect2(char irReceiverPin2);
unsigned int voltsLevel(char);
unsigned long rcTime(char, int);
unsigned char sevenSegLED(char counter);

void carrierInit();
void pwmEnable();
void pwmDisable();

void disableServos(); // Halt servo signals

Servo servoLeft; // Declare left and right servos
Servo servoRight;

int Begin = 0;

void setup() // Built-in initialization block
{

 // tone(10, 3000, 1000); // Play tone for 1 second on pin 2
 // delay(1000); // Delay to finish tone

  DDRB &= 0xFC; // Set pin 8 and 9 as input

  servoLeft.attach(11); // Attach left signal to pin 11
  servoRight.attach(12); // Attach right signal to pin 12

  carrierInit();
  Serial.begin(9600);
}

void loop() // Main loop auto-repeats
{
  char irLeft;
  char irRight;
  char leftWhisker;
  char rightWhisker;
  char message[80];
  unsigned long light;

  leftWhisker = PINB & 0x01;        // Set leftWhisker to pin 8
  rightWhisker = (PINB & 0x02)>>1;  // Set rightWhiker to pin 9

  light = rcTime(ADC0, 10);

  pwmEnable();
  delay(1); //1 ms delay. The transmission length should <= 1.2 ms
  pwmDisable();
  
  irRight= irDetect(5);   // Set IR Detect Right to pin 5
  irLeft = irDetect2(13); // Set IR Detect Left to pin 13

  sprintf(message, "\n irRight = %d light = %lu s= %d", irRight, light, Begin);
  Serial.write(message);

    if(light < 600)
    
    {  
      Begin = 0;
      tone(10,1500,1000);
      disableServos();
    }        
    if(irRight)
    {
      turnLeft(280);
    }
    else if(irLeft)
    {
      turnLeft(280);
    }
    else if(irLeft && irRight)
    {
      backward(350);
      turnRight(280);
    }
    else if (!leftWhisker || !rightWhisker)
    {
      backward(280);
      turnRight(280);
    }        
    else    
      CurvaD();    
}
    
void forward(unsigned int time) // Full-speed Forward function
{
  servoLeft.writeMicroseconds(1700); // Left wheel counerclockwise
  servoRight.writeMicroseconds(1300); // Right wheel clockwise
  delay(time); // Maneuver for time ms
}

void turnLeft(unsigned int time) // Left turn function
{
  servoLeft.writeMicroseconds(1300); // Left wheel clockwise
  servoRight.writeMicroseconds(1300); // Right wheel clockwise
  delay(time); // Maneuver for time ms
}

void turnRight(unsigned int time) // Right turn function
{
  servoLeft.writeMicroseconds(1700); // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700); // Right wheel counterclockwise
  delay(time); // Maneuver for time ms
}

void backward(unsigned int time) // Full-speed Backward function
{
  servoLeft.writeMicroseconds(1300); // Left wheel clockwise
  servoRight.writeMicroseconds(1700); // Right wheel counterclockwise
  delay(time); // Maneuver for time ms
}

void CurvaE() {
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1300);
}

// Robot follows left wall by turning to the left all the time
void CurvaD() {
  servoLeft.writeMicroseconds(1670);
  servoRight.writeMicroseconds(1460);
}

void disableServos() // Halt servo signals
{
  servoLeft.detach(); // Stop sending servo signals
  servoRight.detach();
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

void carrierInit()
{
  /*intialized timer 2 for frequency 38KHz, OC2B at PB2(pin 3)
    TECH 3157/5157 Micrphase-correct pwm, Ch.B, prescaler=1, 50% duty ratio*/
  DDRD |= 0x08;
  TCCR2A = 0b00100001; //0b00100011
  TCCR2B = 0b00001001; //0b00010001
  OCR2A = 211; //16M/2/38K = 211
  OCR2B = OCR2A * 0.5;
}

void pwmEnable()
{
  /*enable Timer2 Channel B OC2B at PB2(pin 3)
  */
  TCCR2A = 0b00100001; //0b00100011
}
void pwmDisable()
{
  TCCR2A = 0x00; //discount OC0A and OC0B.
}   // End of Final Project Code
