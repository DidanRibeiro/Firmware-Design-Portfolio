#include<Sparki.h>

void MyDelay (unsigned long mSecondsApx); // User defined delay

// void MyDelay1(unsigned long Blink);     // Use to blink faster and different pattern

void setup() {

 unsigned char *portDDRB;
 portDDRB = (unsigned char *) 0x24; // Address of port B Data Direction Register

 *portDDRB |= 0x20;    // set pin 13 as an output

}

void loop() {

  unsigned char *portB;

  portB = (unsigned char *) 0x25; // Address of port B Data Register

//  for (unsigned char x = 25; x <= 200; x+=50)
{  

  *portB |= 0x20;  // Turn on LED
  MyDelay(1000);
  *portB &= 0xDF; // Turn off LED
  MyDelay(1000);
}
  
}

void MyDelay (unsigned long mSecondsApx)
{
    volatile unsigned long i;
 
  unsigned long endTime = 500 * mSecondsApx;
  for (i = 0; i < endTime ; i++); // Loops for Delay
  
}


