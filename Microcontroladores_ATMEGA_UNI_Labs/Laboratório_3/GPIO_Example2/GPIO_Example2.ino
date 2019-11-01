//TECH 3157 GPIO Example 2 
// Display a message if the input from pin 8 (PORTB.0) changes

#define DEBUG_MESSAGE_MAX_LENGTH 80
unsigned char i;
void MyDelay (unsigned long mSecondsApx);


void setup() {
//   PORTB &= ~(1<<PORTB0); // Turn off the pull-up resistor for pin 8
//    PORTB |= (1<<PORTB0) 0b00111110 ;     // turn on the pull-up resistor for pin 8
    PORTB |= 0b00000001;    // turn on the pull-up resistor for pin 8
  DDRB &= 0b11111110;       // Set pin 0 as an input
  
  Serial.begin(9600);

}

void loop() {
 
 
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
    
    if (currentSample != previousSample)     // It's off
    {
     
      // Input has changed, display promot
      Serial.write("Change occurs.....................\n");
    }


  
    // store the current sample as the next previous sample
    previousSample = currentSample;
    delay(1000);
}




