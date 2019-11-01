#include "avr/io.h"
   /* Lab 5 Example 2
* Robotics with the BOE Shield - Phototransistor
* Display voltage of phototransistor circuit output connected to A3 * in the serial monitor.
*/

#include <AVR/io.h>
#define ADC_PreScaler_128  0x7
void setup()
{
  Serial.begin(9600);
// Built-in initialization block
// Set data rate to 9600 bps
/*REFS = 01 Internal 5V reference; ADLAR = 0 right adjusted; MUX3:0 = 0011 single-ended ADC3 (pin A3 in Arduino board) */
ADMUX = 0x40 | 0x03;
/*ADCSRA: ADEN = 1 ADC enabled
          ADATE = 1 ADC Auto TRigger enable
ADPS2:0 = 111 prescaler = 128 */
ADCSRA |= ((1<<ADEN) | (1<<ADATE) | ADC_PreScaler_128);
//ADCSRB: fADC auto Trigger Scoursce: free running mode ADCSRB = 0;
//disable Digital input at ADC3
DIDR0 |= (1<<ADC3D);
}
void loop() {
         char message[80];
         float volts;
         unsigned int adcread;
         ADCSRA |= (1<<ADSC);
         while ((ADCSRA&(1<<ADIF)) == 0);
         adcread = ADCL;
         adcread = (((unsigned int) ADCH) << 8) + adcread; //read high byte 
         volts= (float(adcread))*5/1024.0; //convert to voltage, Vref = 5V
         sprintf(message, "\n A3 = %d, i.e. analog input voltage = %d.%.3d V ",
         adcread, int(volts), int(volts*1000)%1000); //in one line %.3d: display 3
         Serial.write(message);
         delay(1000);                         // update every 1 second
          }
