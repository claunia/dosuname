#include <stdio.h>

void main()
{
unsigned char Result;
outportb (0x80, 0xFF);
Result = inportb (0xE9);
if (Result == 0xE9)
   {
   printf("Bochs detected.\n");
   }
else
   {
   printf("Bochs not detected.\n");
   }
}
