/* 4. Event counter using Timer/Counter0
Use Timer0 as an event counter. Connect T0 (PD4/pin4) to a pushbutton. The number of
pulses counted will be displayed on the Serial Monitor window.
*/
       
#include "avr/io.h"
unsigned int count; //the count of events
void setup()
{
  PORTD |= 0x10; //activate pull-up of PD4
  DDRD &= 0xEF; //set pin 4 (PD4) as input
  TCCR0A = 0x00; //normal mode
  TCCR0B = 0x07; //output clock source, falling edge TCNT0 = 0;
  Serial.begin(9600);
}

void loop() {
  char message[80];
  count = TCNT0;
  sprintf(message, "\nThe number of events: %d", count); Serial.write(message);
}
