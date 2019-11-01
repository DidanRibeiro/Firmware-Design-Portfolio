//TECH 3157 GPIO Example 2 
// Display a message if the input from pin 8 (PORTB.0) changes

#define DEBUG_MESSAGE_MAX_LENGTH 80
unsigned char i;
void MyDelay (unsigned long mSecondsApx);


void setup() {
//   PORTB &= ~(1<<PORTB0); // Turn off the pull-up resistor for pin 8
//    PORTB |= (1<<PORTB0) 0b00111110 ;     // turn on the pull-up resistor for pin 8
//    PORTB |= 0b00111101;    // turn on the pull-up resistor and turn on LEDs
//  DDRB &= 0b11111101;       // Set pin 0 as an input

  DDRB = 0b00111100; // Set pin 10-13 as output  and set pin 0 as an input
  
  Serial.begin(9600);

}

void loop() {

  PORTB |= 0b00111101; 
 
  char message [DEBUG_MESSAGE_MAX_LENGTH];
  static unsigned char previousSample;
  static unsigned char currentSample;


    currentSample = PINB & 0x01;      // pin 8(PINB0) is connected 
 //   i = PINB;
 //   sprintf(message,"PINB = 0x%x \n", i);
    Serial.write(message);
    sprintf(message, "previousSample = 0x%x \n", previousSample);
    Serial.write(message);
    sprintf(message, "currentSample = 0x%x \n", currentSample);
    Serial.write(message);
    
    if (currentSample == 0)     // It's off pushbutton is pressed
    {
     
      PORTB |= 0b00111100;    // turn on LEDs
      delay(1000);
      PORTB ^= 0b11111111;   // turn off LEDs
      delay(1000);  
    }
    else
      {
        if (currentSample == 1)   // Its on pushbutton is not pressed
         {
        /*  for (unsigned char x = 25; x <= 200; x+=50)
          { 
            PORTB ^= 0b11111111;    // turn off LEDs
            MyDelay(x);
        */

            PORTB^=0b11111111;    // turn off LEDs
            delay(1000);
            PORTB |= 0b00000100;
            delay(1000);
            PORTB |= 0b00001000;
            delay(1000);
            PORTB |= 0b00010000;
            delay(1000);
            PORTB |= 0b00100000;
            delay(1000);
           
          }
        }  
      
       
 /*   if (currentSample != previousSample)
    {
        // input has changed, display promot
        Serial.write("Change occurs.........................\n");
    }
  */  
    
    // store the current sample as the next previous sample
    previousSample = currentSample;
    delay(1000);
}


void MyDelay (unsigned long mSecondsApx)
{
  volatile unsigned long i;
  unsigned long endTime = 1000*mSecondsApx;
  for (i = 0; i < endTime; i++);
}

