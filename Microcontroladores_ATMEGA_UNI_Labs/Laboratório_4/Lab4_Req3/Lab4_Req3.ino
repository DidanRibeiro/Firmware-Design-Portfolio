w/*
 * In this part, you are required to generate a triangle waveform of approximately 500 Hz, as shown in 
 * Figure 4.3. You may use N different duty ratios (for example N= 10, Duty ratio should be in sequence of 0, 
 * 0.1, 0.2,...., 0.9, 1, 0.9, 0.8, ...0.1, 0 and repeats) to get the needed analog voltage levels 
 * (0V, 0.5V, 1V, 1.5V, ...4.5V, 5V) for your triangle waveform. Please reuse the functions you implemented 
 * in previous parts.
 * 
 */

#include "avr/io.h"
//Function Prototype
void My100SecDelay();
void PWMInit();
void OutputVoltage(float);



void setup() {

  DDRD = 0b00100000;    // Set pin 6 (OC0A)
  DDRB = 0b00000100;    // Set pin 10 (OC1B)


  /* Set operation Clear on up-counting; set on down counting; WGM12:0 = 101 Mode 5 phase correct PWM
    CS12:0 = 010 prescaler = 8  */

  OCR0A = 100;
  OCR0B = 50;
  TCCR0A = 0x21;          // 0b00100001
  TCCR0B = 0x0A;            // 0b00001010; 
  TCCR1A = 0x23;    // 0b00100011
  TCCR1B = 0x11;    // 0b0010001
  PWMInit();
  OutputVoltage(0.7);
  TCNT1 = 0;
  TCNT0 = 0;
}

void loop() {

    double sample;
    unsigned char currentIndex;
    static const float m_triangleWaveform[] = { 0.000, 0.100, 0.200, 0.300, 0.400, 0.500, 0.600, 0.700,
                                            0.800, 0.900, 1.000, 0.900, 0.800, 0.700, 0.600, 0.500,
                                            0.400, 0.300, 0.200, 0.100 };


    for (currentIndex = 0; currentIndex < 21; currentIndex ++)
  {
    sample = m_triangleWaveform[currentIndex];
    currentIndex = (currentIndex+1) % 20;
    OutputVoltage(sample);
    My100SecDelay();
  }
    
}

void PWMInit()
{
  OCR1A = 40;
}

void OutputVoltage(float dutyRatio)
{
  OCR1B = OCR1A * dutyRatio;  

}

void My100SecDelay()
{
  do { }
  while ((TIFR0 & (0x1 << TOV0)) == 0);   // wait till TOV0 to be set
}
