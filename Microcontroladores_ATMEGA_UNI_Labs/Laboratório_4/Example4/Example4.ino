/*Example4: Use Timer0 as an event counter. Assume T0 (PD4/pin4) is connected to an external
            clock or debounced switch. Display the number of pulses counted on Serial 
            monitor window. */

            
unsigned int count; //the count of events

void setup() {
  
  PORTD |= 0x10; //activate pull-up of PD4
  DDRD &= 0xEF; //set pin 4 (PD4) as input
  TCCR0A = 0x00; //normal mode
  TCCR0B = 0x06; //output clock source, falling edge TCNT0 = 0;
  Serial.begin(9600); 
  }

void loop() {
  
  char message[80];
  count = TCNT0;
  sprintf(message, "\nThe number of events: %d", count); Serial.write(message);
  }

