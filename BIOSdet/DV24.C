#include <stdio.h>
#include <dos.h>

main(){
      unsigned char far *bios_data = MK_FP (0x0000, 0x0000); //Get address of the BIOS data
      unsigned short data_size; //For the BIOS data size
      unsigned short temp=0; //For temporary numbers
      FILE *feo;
      long i,j;

      feo=fopen("video24.rom","w+");
       for(i=0x0000;i<=0x5FFF;i++)
       {
        bios_data=MK_FP(0xC000,i);
        fputc(*bios_data,feo);
       }
}
