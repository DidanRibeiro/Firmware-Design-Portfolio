/*Example2: Output a PWM waveform with 50% duty ratio and 0.5 Hz frequenc. The system clock 
  frequency of Arduino boards is 16 Mhz. We use Timer/Counter1 phase correct PWM to generate
  it. Use waveform generation mode 11 and toggle mode (i.e. Toggle )C1A on Compare Match).*/

#include "avr/io.h"

void setup() {
 
  DDRB = 0x02; //set pin 9 as output; pin 9 (OC1A) is connected to an LED
  /*set operation Toggle mode; WGM13:0 = 1011 phase correct PWM*/ 
  TCCR1A = 0x43;
  TCCR1B = 0x15;
  OCR1AH = 0x1E; // 0x1E84 = 7812 -> 1s
  OCR1AL = 0x84;
}

void loop() {
  

}
