/* Lab 5 Example 3
* Robotics with the BOE Shield - Phototransistor connection using RC circuit 
* * Display the discharge time in microseconds
* in the serial monitor.
*/
#include <AVR/io.h>
#define ADC_PreScaler_128  0x7
#define ADC3 3
#define ADC4 4
unsigned int voltsLevel(char ADCpin);
unsigned long rcTime(char ADCpin, int  threshold);

void setup()
{
  Serial.begin(9600);
// Built-in initialization block
// Set data rate to 9600 bps
/*REFS = 01 Internal 5V reference; ADLAR = 0 right adjusted;  
MUX3:0 = 0011 single-ended ADC3 (pin A3 in Ariduino board) */
  ADMUX = 0x40 | 0x03;
  /*ADCSRA: ADEN = 1 ADC enabled
            ADATE = 1 ADC Auto TRigger enable
ADPS2:0 = 111 prescaler = 128 */
ADCSRA |= ((1<<ADEN) | (1<<ADATE) | ADC_PreScaler_128);
//ADCSRB: fADC auto Trigger Scoursce: free running mode
ADCSRB = 0;
//disable Digital input at ADC3
//DIDR0 |= (1<<ADC3D);


 char message[80];
  float volts;
  unsigned int adcread[100];
  int threshold;
  
for (threshold = 2; threshold < 1023; threshold +=2)
  {
// Main loop auto-repeats
DDRC |= 0x08; //set pin A3 (portC.3) as an output
PORTC |= 0x08; //output HIGH at pin A3
delay(1); //hold 5V for 1 ms to allow charging the capacitor 
DDRC &= ~0x08; //set pin A3 as an input
PORTC &= ~0x08; //disconnect the pullup-resistor to allow discharge

unsigned long time = micros();
while (voltsLevel(ADC3)>threshold); //wait till the read from ADC3 is less than 10
time = micros() - time;
sprintf(message, "\n rctime = %lu", time);
Serial.write(message);

sprintf(message, "\n threshold = %d", threshold);
Serial.write(message); 
 
  }
  
/*
for (threshold = 2; threshold < 1023; threshold +=2)
  {
  // Main loop auto-repeats
  DDRC |=  0x10; //set pin A3 (portC.3) as an output  0b0000 1000
  PORTC |= 0x10; //output HIGH at pin A3
  delay(1); //hold 5V for 1 ms to allow charging the capacitor 
  DDRC &= ~0x10; //set pin A3 as an input
  PORTC &= ~0x10; //disconnect the pullup-resistor to allow discharge

  unsigned long time = micros();
  while (voltsLevel(ADC3)>threshold); //wait till the read from ADC3 is less than 10
  time = micros() - time;
  sprintf(message, "\n rctime = %lu", time);
  Serial.write(message);
  }

 */ 

}

void loop() 
{
  char message[80];
  float volts;
  unsigned int adcread[100];
  int threshold;
/*
  for (threshold = 2; threshold < 1023; threshold +=2)
  {
// Main loop auto-repeats
DDRC |= 0x08; //set pin A3 (portC.3) as an output
PORTC |= 0x08; //output HIGH at pin A3
delay(1); //hold 5V for 1 ms to allow charging the capacitor 
DDRC &= ~0x08; //set pin A3 as an input
PORTC &= ~0x08; //disconnect the pullup-resistor to allow discharge

unsigned long time = micros();
while (voltsLevel(ADC3)>threshold); //wait till the read from ADC3 is less than 10
time = micros() - time;
sprintf(message, "\n rctime = %lu", time);
Serial.write(message);
  }
 */ 
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
