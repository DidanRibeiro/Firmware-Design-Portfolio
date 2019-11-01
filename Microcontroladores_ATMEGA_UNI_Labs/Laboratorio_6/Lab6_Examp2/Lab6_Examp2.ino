/*Lab 6 Example 2
* Display IR detector output resutls
* pin 10 - Timer 1 Ch. B is used to generate 38 KHz signal * pin 13 -- left IR receiver output
 1 - no object  0 - theres object */
#include <avr/io.h>

        char irDetect(char irReceiverPin);
        char irDetect2(char irReceiverPin2);
        void carrierInit();
        void pwmEnable();
        void pwmDisable();
        char message[80];
        
void setup()
{
 // DDRD &= 0xEF;
//USE Timer1 to generate 38 KHz  carrier 
carrierInit();
Serial.begin(9600);
}

void loop() 
{
  
char irLeft;
char irRight;

pwmEnable();
delay(1);
pwmDisable();

//irRight = (PIND & 0x10) >> 4; //get the status infrared receiver at pin 4
//irLeft = (PINB & 0x20) >> 5; //get the status infrared receiver at pin 13 

irLeft = irDetect2(13);
irRight= irDetect(4);

sprintf(message, "irLeft = %d   irRight = %d \n ", irLeft, irRight);
Serial.write(message);

delay(500);
}

void carrierInit()
{
  
/*intialized timer 1 for frequency 38KHz, OC1B at PB2(pin 10)
//1 ms delay. The transmission length should <= 1.2 ms
phase-correct pwm, Ch.B, prescaler=1, 50% duty ratio*/ 
DDRB |=  0x04; // 0x08;   //0x04;
TCCR1A = 0x23;      //0x42;  // 0b0010 0010 //0x23;    //0b00100011
TCCR1B = 0x11;    //0b00010001
OCR1A = 211;      //16M/2/38K = 211
 OCR1B = OCR1A *0.5;
}

void pwmEnable()
{  
/*enable Timer1 Channel B OC1B at PB2(pin 10)
*/
TCCR1A = 0x23; //0b00100011
}
void pwmDisable()
{
TCCR1A = 0x0; //discount OC0A and OC0B.
}


char irDetect(char irReceiverPin)
{
  irReceiverPin = (PIND & 0x10) >> 4; //get the status infrared receiver at pin 4
  return irReceiverPin;
}

char irDetect2(char irReceiverPin2)
{
  irReceiverPin2 = (PINB & 0x20) >> 5; //get the status infrared receiver at pin 13
  return irReceiverPin2;
}

