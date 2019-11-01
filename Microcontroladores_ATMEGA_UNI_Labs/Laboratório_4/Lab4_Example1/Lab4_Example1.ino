/*Lab 4 Example 1 code. Timer 1 Channel A output as 0.5 Hz square waveform */

#include "avr/io.h"

void setup() {
  DDRB = 0x02;    // Set pin 9 as output; pin9 (OC1A) is connected to an LED

  /* Set operation Toggle mode; WGM13:0 = 1011 phase correct PWM
    CS12:0 = 101 prescaler = 1024 */
    TCCR1A = 0x43;
    TCCR1B = 0x15;
    OCR1A = 0x1E84; // Set the TOP value 1 sec / (2*(1/(16MHz/1024))) = 7812 = 0x1E84
    TCNT1 = 0;      // Clear counter and update 0CR1A

}

void loop() {
  

}
