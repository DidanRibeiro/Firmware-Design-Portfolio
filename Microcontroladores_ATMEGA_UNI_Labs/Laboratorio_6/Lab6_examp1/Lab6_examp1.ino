#include <avr/io.h>
       #include <avr/interrupt.h>
       int pos;
       void setup()
       {
EICRA = 0x0F; //set rising edge triggered

EIMSK = (1<<INT0)|(1<<INT1); //set external interrupt mask sei(); //enable global interrupt bit
          Serial.begin(9600);
       }
void loop() {
          char message[80];
sprintf(message, "pos = %d\n", pos); Serial.write(message);
delay(500);
}
       ISR (INT0_vect)
       {
pos ++; //increment pos when SW1 is pressed }
       }
       
       ISR (INT1_vect)
       {
pos --; //decrement pos when SW2 is pressed }
       }
