/* Lab 2 Debuggging problem 1*/

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
   unsigned long j;
   char   k;
   char endTime = 80 * mSecondsApx;
   
   for (i = 0; i < endTime; i++)
   {
      j = 10;
      do
      {
         j = j - 1;
         k = i / j;
      } 
      
      while ((k > 0) && (j>1));
   }
}

