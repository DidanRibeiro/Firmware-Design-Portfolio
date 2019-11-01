// Lab 3 Example L3-2
// Display message if the input from pin 8 (i.e PORTB.0) changes

#define DEBUG_MESSAGE_MAX_LENGTH 80


void setup() {
  PORTB |= (1<<PORTB0); // Turn on the pull-up resister for pin 8
  DDRB &= 0b11111110;   // Set pin 8 as an input
  Serial.begin(9600);

}

void loop() {
  char message[DEBUG_MESSAGE_MAX_LENGTH];
  static unsigned char previousSample;
  static unsigned char currentSample;

  currentSample = PINB & 0x01;  // Obtain the status of input from pin 8 
  sprintf(message, "previousSample - 0x%x \n", previousSample);
  Serial.write(message);
  sprintf(message, "currentSample = 0x%x \n", currentSample);
  Serial.write(message);
  if (currentSample != previousSample)
  {
      // Input has changed, display promot
      Serial.write("change occrus...................\n");
      
  }

    // Store the current sample as the next previous sample
    previousSample = currentSample;
    delay(1000);
  }


// end of Lab 3 Example L3-2
