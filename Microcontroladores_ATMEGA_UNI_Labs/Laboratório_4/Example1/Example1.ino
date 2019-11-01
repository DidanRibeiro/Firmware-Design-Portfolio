/*Example1: User Timer 0 to toggle pin6 (PD6/OC0A) continuosly every 1 ms. Notice the 
  Arduino has a system clock of 16MHz.
  Since the output waveform toggles every 1ms, i.e 1kHz, Timer0 is a 8-bit and the 
  t_clk = 1/16 MHz, we have to use the pre-scaler. Choose pre-scaler = 64, i.e CS02-0=011.
  Now we need to use either phase correct PWM or Fast PWM. If Fast PWM is adopted and we 
  choose OC0A toggle mode( toggle on compare match), the configuration should be as follow*/

#include "avr/io.h"

void setup() {

  DDRB = 0x02;    // Set pin 9 as output; pin9 (OC1A) is connected to an LED
  /* toggle mode, fast PWM. WGM02:0 = 111, COM0A1:0= 01 (use OC0A) */
  TCCR0A = 0x43; // 0b01000011; 
  TCCR0B = 0x0B; // 0b00001011; //0x0B
  OCR0A =  0xF9;  //0x7F; // 127; // 1 kHz = 16MHz/(2*64*(OCR0A+1))
  TCNT0 = 0;

}

void loop() {
  

}
