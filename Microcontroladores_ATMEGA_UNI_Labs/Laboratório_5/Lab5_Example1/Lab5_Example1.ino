/* Lab 5 ADC Example 1 Ver. 0
* Display temperature in serial monitor * temperature sensor is connected to A0 */
#include <AVR/io.h>
#define ADC_PreScaler_128  0x7

void setup()
{
  Serial.begin(9600);
// Built-in initialization block
// Set data rate to 9600 bps
/*REFS = 01 Internal 5V reference; ADLAR = 0 right adjusted; MUX3:0 = 0000 single-ended ADC0 */
ADMUX = 0x40;    // 0b1100 0000
/*ADCSRA: ADEN = 1 ADC enabled
          ADATE = 1 ADC Auto TRigger enable
ADPS2:0 = 111 prescaler = 128 */
ADCSRA |= ((1<<ADEN) | (1<<ADATE) | ADC_PreScaler_128);     // 0b10100111
//ADCSRB: fADC auto Trigger Scoursce: free running mode ADCSRB = 0;
//disable Digital input at ADC0 (i.e. A0)
DIDR0 |= (1<<ADC0D);
}

void loop() {
  char message[80];
// Main loop auto-repeats
  float volts;
  unsigned int adcread, temp;
  ADCSRA |= (1<<ADSC);
  while ((ADCSRA&(1<<ADIF)) == 0);
  //start conversion
  //wait till conversion is finished
  adcread = ADCL; //read low byte first
  adcread = (((unsigned int) ADCH) << 8) + adcread; //read high byte 
  volts = (float(adcread))*5.0/1024.0; //Vref = 5V
  temp = int (volts*1000); //temperature in unit of 10 Celsius degree for
        sprintf(message, "\n A0 = %d, i.e. Temperature = %d.%d Celsius degree", adcread, temp/10, temp%10);
        Serial.write(message); // Display voltage at A3 delay(1000); // Delay for 1 second
}
