/*Lab 4 Example 1 code. lease determine the value of TCCR1A, TCCR1B, and OCR1A to generate a 
 10 Hz square waveform according to the following specific:
 use channel B for the output waveform,
 use phase-correct PWM mode,
 use OCR1A as the top.
 use clear on up-counting, set on down counting,
Select proper prescaler. Set duty ratio as 50%. Modify the above program and observe the output.
Note: You need to connect to OC1B to the LED instead. You should observe the LED blinks quickly.
Please show the demo to the instructor. Please include the fully commented code for your report.
If is 10Hz, so f = 10Hz and T = 1 / 10 = 0.1 sec. In 0.1 sec will be 0.05 sec for led should be on 
0.05 be off.
*/
  
#include "avr/io.h"

void setup() {
  
 DDRB = 0b00000100; // Set pin 10 (OC1B) 

  /* Set operation Clear on up-counting; set on down counting; WGM13:0 = 1011 Mode 1 phase correct PWM
    CS12:0 = 101 prescaler = 1024  */
    TCCR1A = 0x23;    // 0b00100011   Set timer/counter 1 channel A to 0x23 
    TCCR1B = 0x15;    // 0b00010101   Set timer/counter 1 channel B to 0x15 
    OCR1A = 781;      // Set TOP value 0.1 sec / (2*(1.16Mhz/1024))) = 781.25
    OCR1B = 390;      // Duty Cicle: 0.1 sec / (2*(1/(16MHz/1024)))= 781.25 * 0.5(D) = 390
    TCNT1 = 0;        // Clear counter and update 0CR1A

}

void loop() {
 
}
