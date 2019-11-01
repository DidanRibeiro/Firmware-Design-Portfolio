// TECH 3157 GPIO example 3 blinks the LEDs via pins 10-13

void setup() {
  DDRB = 0x3c;  // set pin 10-13 as output

}

void loop() {
//  PORTB |= 0x3c;  // turn on LEDs
  PORTB |= 0b00111100;
  delay(1000);
//  PORTB ^= 0xFF;  // turn off LEDs
  PORTB ^= 0b11111111;  
  delay(1000);

}
