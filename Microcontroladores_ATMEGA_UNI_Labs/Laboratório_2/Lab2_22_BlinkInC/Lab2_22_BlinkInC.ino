/* Lab 2 Debuggging problem 2*/

void NewDelay(unsigned long mSecondsApx);

void setup()   
{
   unsigned char *portDDRB;

   portDDRB = (unsigned char *) 0x24;

   *portDDRB |= 0x20;
}

void loop()                     
{
   unsigned char *portB;

   portB = (unsigned char *) 0x25;

   *portB |= 0x20;
   NewDelay(100);
   *portB &= 0xDF;
   NewDelay(100);
}

void NewDelay(unsigned long mSecondsApx)
{
   volatile unsigned long i;
   unsigned char j = 0;
   unsigned long endTime = 1000 * mSecondsApx;

   i = 0;
   while (j = 0)
   {
      i++;
      if (i = endTime)
      {
         j = 1;
      }
   }
}

