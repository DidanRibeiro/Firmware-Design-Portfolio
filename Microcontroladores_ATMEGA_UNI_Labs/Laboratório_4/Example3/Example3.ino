/*Example3: Using waveform generation mode 3 (Phase Correct 10-bit PWM) to generate a 
 * waveform with different dity ratio*/

#include "avr/io.h"

void setup() {
 
  /* non-inverting mode, WGM13:0 = 0011 phase correct 10-bit PWM */ 
  TCCR1A = 0x83; //0b10000011 = 0x83
  TCCR1B = 0x05; // 0b00000101= 0x05
  /* 0x01FF = half of the top value 0x3FF. The duty ratio can be adjusted by applying 
              different value to OCR1A. OCR1A should be less than TOP, i.e. 0x3FF */
  OCR1AH = 0x01;
  OCR1AL = 0xFF;
  
}

void loop() {
}
