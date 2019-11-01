// TECH 3157 GPIO example1: check the status of portB

unsigned char i;
#define DEBUG_MESSAGE_MAX_LENGTH 80

void setup() {

  char message[DEBUG_MESSAGE_MAX_LENGTH];
  Serial.begin(9600);

 /* Define pull-ups and set outputs high */
 /* Define directions for port pins */

 PORTB = (1<<PORTB7 | (1<<PORTB6) | (1<<PORTB1) | (1<<PORTB0));
 DDRB = (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);

 // Red port pins

 i = PINB;
 sprintf (message, " PINB = 0x%x \n", i);
 Serial.write(message);
 i = DDRB ;
 sprintf (message, " DDRB = 0x%x \n", i);
 Serial.write(message);
 i = PORTB;
 sprintf (message, " portB = 0x%x \n", i);
 Serial.write(message);
 

}

void loop() {
  // put your main code here, to run repeatedly:

}
