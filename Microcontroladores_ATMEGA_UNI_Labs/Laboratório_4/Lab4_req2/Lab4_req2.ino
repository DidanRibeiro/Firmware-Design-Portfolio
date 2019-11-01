/* In this part, we will use PWM to get analog signal that we need. First, 
 *  use Timer/Counter 1 to generate a 200 KHz square waveform similar 
 *  to part 1. Then Use a RC as the LPF to observe the output analog voltage. 
 *  Modify the duty ratio by adjusting the OCR1B for 20% and 80% and observe 
 *  the analog output. Remember in order for the pwm to work, we need 
 *  fanalog << fc << fpwm. */


// Function Prototype
void PWMInit();
void OutputVoltage(float);


#include "avr/io.h"

void setup() {
char message[80];
  
 DDRB = 0b00000100; // Set pin 10 (OC1B) 

    Serial.begin(9600);
  
  /* Set operation Clear on up-counting; set on down counting; WGM13:0 = 1011 Mode 1 phase correct PWM
    CS12:0 = 001 prescaler = No prescaling  */
    TCCR1A = 0x23;    // 0b00100011    
    TCCR1B = 0x11;    // 0b00010001
    PWMInit();        // OCR1A = 40     
    sprintf(message,"OCR1A: %d \n",  OCR1A);
    Serial.write(message);
  //  OCR1B = 28;
    OutputVoltage(0.5);
    sprintf(message,"OutputVoltage: %d \n \t", OCR1B );
    Serial.write(message);
//    Serial.println(OutputVoltage(0.5));
    
 //   OCR1A = 40;      // Set TOP value 5us sec / (2*(1.16Mhz/1024))) = 40
 //   OCR1B = 32;      // Duty Cicle: 0.1 sec / (2*(1/(16MHz/1024)))= 781.25 * 0.5(D) = 390
    TCNT1 = 0;        // Clear counter and update 0CR1A

}

void loop() {
 
}

void PWMInit()
{

  OCR1A = 40;
 // int OCR1A;
 // return OCR1A = 40;
 
}

void OutputVoltage(float dutyRatio)

{
/*  
  int result;
  int duty[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10};


  for (dutyRatio = 0; dutyRatio <= 10 ; dutyRatio++)
  {
      result = (duty[dutyRatio] * PWMInit())/10;
  
      
      //return result;
  }
  return result;

  OCR1B = PWMInit() * dutyRatio;
*/
//  if (dutyRatio == 0.1)
  OCR1B = OCR1A * dutyRatio;
 /* 
   if (dutyRatio == 0.2)
  OCR1B = OCR1A * dutyRatio;
  
   if (dutyRatio == 0.3)
  OCR1B = OCR1A * dutyRatio;
  
   if (dutyRatio == 0.4)
  OCR1B = OCR1A * dutyRatio;
  
   if (dutyRatio == 0.5)
  OCR1B = OCR1A * dutyRatio;
  
   if (dutyRatio == 0.6)
  OCR1B = OCR1A * dutyRatio;
  
   if (dutyRatio == 0.7)
  OCR1B = OCR1A * dutyRatio;
  
   if (dutyRatio == 0.8)
  OCR1B = OCR1A * dutyRatio;
  
   if (dutyRatio == 0.9)
  OCR1B = OCR1A * dutyRatio;
  
   if (dutyRatio == 1.0 )
  OCR1B = OCR1A * dutyRatio;
 */
}


