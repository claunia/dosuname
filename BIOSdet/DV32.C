#include <stdio.h>
#include <dos.h>

main(){
      unsigned char far *bios_data = MK_FP (0x0000, 0xC0000); //Get address of the BIOS data
      FILE *feo;
      long i,j;

      feo=fopen("video32.rom","w+");
      for(i=0; i<0x8000; i++)
       fputc(*bios_data, feo);
}
