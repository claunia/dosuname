/************************************************************************
  T h e   O p e n   W i n d o w s   P r o j e c t
 ------------------------------------------------------------------------

        Filename   : dump.c
        Version    : 0.01
        Author(s)  : Natalia Portillo
            
        Component  : OWP DOS subsystem - System information command

 --[ Description ]-------------------------------------------------------
  
        Dump a 128Kb PC BIOS to file.

 --[ History ] ----------------------------------------------------------
	
        0.01: Original file by Natalia Portillo.

 --[ How to compile ]----------------------------------------------------

	Recommended compiler Borland Turbo C++ 1.01
		http://community.borland.com/museum

 --[ Where to get help/information ]-------------------------------------

	This archaic and abandoned software is opensource with no warranty
    or help of any kind.
    For inquiries contact claunia@claunia.com.

 --[ License ] ----------------------------------------------------------

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
        of the License,or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
        along with this program; if not,write to the Free Software
        Foundation,Inc.,59 Temple Place - Suite 330,Boston,MA  02111-1307,USA.

 ------------------------------------------------------------------------
 Copyright (c) 2000 The Open Windows Project
*************************************************************************/
#include <stdio.h>
#include <dos.h>

main(){
      unsigned char far *bios_data = MK_FP (0x0000, 0x0000); //Get address of the BIOS data
      unsigned short data_size; //For the BIOS data size
      unsigned short temp=0; //For temporary numbers
      FILE *feo;
      long i,j;

      feo=fopen("bios.bin","w+");
      for(j=0x0F000;j<=0x0F000;j++)
      {
       for(i=0x0E000;i<=0x0FFFF;i++)
       {
        bios_data=MK_FP(j,i);
        fputc(*bios_data,feo);
       }
      }
       for(i=0x00000;i<=0x0FFFF;i++)
       {
        bios_data=MK_FP(0x0F001,i);
        fputc(*bios_data,feo);
       }
       for(i=0x00000;i<=0x0DC43;i++)
       {
        bios_data=MK_FP(0x0F002,i);
        fputc(*bios_data,feo);
       }
}

/*
0000E_00000h - 0000F_0FFFFh 128KB System ROM BIOS
00010_00000h - 0FEBF_0FFFFh Main memory (Maximum address depends on total memory installed in the system.)
0FEC0_00000h - 0FECF_0FFFFh APIC I/O unit
0FED0_00000h - 0FEDF_0FFFFh Reserved for memory-mapped I/O devices
0FEE0_00000h - 0FEEF_0FFFFh APIC Local Unit
0FEF0_00000h - 0FFFD_0FFFFh Reserved for memory-mapped I/O devices
0FFFE_00000h - 0FFFF_0FFFFh 128KB Initialization ROM
*/
