/************************************************************************
  T h e   O p e n   W i n d o w s   P r o j e c t
 ------------------------------------------------------------------------

        Filename   : bios.c
        Version    : 0.01
        Author(s)  : Natalia Portillo
            
        Component : OWP DOS subsystem - VER command
                    OWP DOS subsystem - System information command

 --[ Description ]-------------------------------------------------------
  
        Detect some BIOS stuff.

 --[ History ] ----------------------------------------------------------
	
        0.01: Original file by Natalia Portillo. Only BIOS model.

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
#include "swapbyte.h"

main(){
   long i;

   struct SREGS sregs;
   union REGS regs;
   regs.h.ah = 0xC0; /* Set function C0h */
   int86x(0x15, &regs, &regs, &sregs); /* Call INT 15h */

   if(regs.h.ah==0x00)
      {
      unsigned char far *bios_data = MK_FP (sregs.es, regs.x.bx); //Get address of the BIOS data
      unsigned short data_size; //For the BIOS data size
      unsigned short temp=0; //For temporary numbers

      printf("\nBIOS data location  : %04Xh:%04Xh",sregs.es,regs.x.bx); //Print the location of the BIOS data

      data_size=*bios_data<<8; //Read the first byte of the BIOS data size, and put it in the first byte of the word
      bios_data=MK_FP (sregs.es, regs.x.bx+1); //Go to second byte of the BIOS data size
      data_size=data_size^*bios_data; //Put the second byte in its correct place
      temp=swap_two_bytes(data_size); //Swap the BIOS data size
      data_size=temp; //Put the BIOS data size in the correct place
      temp=0; //Clears temp
      printf("\nBIOS data size      : %d bytes",data_size); //Print the BIOS data size

      bios_data=MK_FP (sregs.es, regs.x.bx+2); //Go to the model byte
      printf("\nBIOS model          : %02x",*bios_data); //Print the BIOS model
      bios_data=MK_FP (sregs.es, regs.x.bx+3); //Go to the submodel byte
      printf("\nBIOS submodel       : %02x",*bios_data); //Print the BIOS submodel
      bios_data=MK_FP (sregs.es, regs.x.bx+4); //Go to the revision byte
      printf("\nBIOS revision       : %02x",*bios_data); //Print the BIOS revision
      bios_data=MK_FP (sregs.es, regs.x.bx+5); //Go to the revision byte
      printf("\nFeature byte 1      : %02x",*bios_data); //Print the Feature byte 1
      bios_data=MK_FP (sregs.es, regs.x.bx+6); //Go to the revision byte
      printf("\nFeature byte 2      : %02x",*bios_data); //Print the Feature byte 2
      bios_data=MK_FP (sregs.es, regs.x.bx+7); //Go to the revision byte
      printf("\nFeature byte 3      : %02x",*bios_data); //Print the Feature byte 3
      bios_data=MK_FP (sregs.es, regs.x.bx+8); //Go to the revision byte
      printf("\nFeature byte 4      : %02x",*bios_data); //Print the Feature byte 4
      bios_data=MK_FP (sregs.es, regs.x.bx+9); //Go to the revision byte
      printf("\nFeature byte 5      : %02x",*bios_data); //Print the Feature byte 5
      printf("\nBIOS version string : ");
      for(i=0x0E061;i<=0x0E07b;i++)
      {
       bios_data=MK_FP(0xF000,i);
       printf("%c",*bios_data);
      }
      printf("\nBIOS copyright      : ");
      for(i=0x0E091;i<=0x0E0BC;i++)
      {
       bios_data=MK_FP(0xF000,i);
       printf("%c",*bios_data);
      }
      printf("\nBIOS dated          : ");
      for(i=0x0FFF5;i<=0x0FFFC;i++)
      {
       bios_data=MK_FP(0xF000,i);
       printf("%c",*bios_data);
      }
      }
   else
      {
      unsigned char far *bios_model = MK_FP (0xF000,0xFFFE);
      unsigned char far *bios_data = MK_FP (0xF000,0xFFF5); //Go to the BIOS date 1st byte

      printf("BIOS model: 0x%x",*bios_model);
      printf("\nBIOS version string: ");
      for(i=0x0E061;i<=0x0E07b;i++)
      {
       bios_data=MK_FP(0xF000,i);
       printf("%c",*bios_data);
      }
      printf("\nBIOS copyright    : ");
      for(i=0x0E091;i<=0x0E0BC;i++)
      {
       bios_data=MK_FP(0xF000,i);
       printf("%c",*bios_data);
      }
      printf("\nBIOS dated        : ");
      for(i=0x0FFF5;i<=0x0FFFC;i++)
      {
       bios_data=MK_FP(0xF000,i);
       printf("%c",*bios_data);
      }
      }
}

//--------B-15C0-------------------------------
//INT 15 - SYSTEM - GET CONFIGURATION (XT >1986/1/10,AT mdl 3x9,CONV,XT286,PS)
//        AH = C0h
//Return: CF set if BIOS doesn't support call
//        CF clear on success
//            ES:BX -> ROM table (see #00509)
//        AH = status
//            00h successful
//                The PC XT (since 1986/01/10), PC AT (since 1985/06/10), the
//                  PC XT Model 286, the PC Convertible and most PS/2 machines
//                  will clear the CF flag and return the table in ES:BX.
//            80h unsupported function
//                The PC and PCjr return AH=80h/CF set
//            86h unsupported function
//                The PC XT (1982/11/08), PC Portable, PC AT (1984/01/10),
//                or PS/2 prior to Model 30 return AH=86h/CF set
//Notes:  the 1986/1/10 XT BIOS returns an incorrect value for the feature byte
//        the configuration table is at F000h:E6F5h in 100% compatible BIOSes
//        Dell machines contain the signature "DELL" or "Dell" at absolute FE076h
//          and a model byte at absolute address FE845h (see #00516)
//        Hewlett-Packard machines contain the signature "HP" at F000h:00F8h and
//          a product identifier at F000h:00FAh (see #00519)
//        Compaq machines can be identified by the signature string "COMPAQ" at
//          F000h:FFEAh, and is preceded by additional information (see #00517)
//        Tandy 1000 machines contain 21h in the byte at F000h:C000h and FFh in
//          the byte at FFFFh:000Eh; Tandy 1000SL/TL machines only provide the
//          first three data bytes (model/submodel/revision) in the returned
//          table
//        the ID at F000h:C000h is used by some Microsoft software before
//          trusting the floppy flags bits 1 and 0 at 0040h:00B5h.
//        the Wang PC contains the signature "WANG" at FC00h:0000h. This is used
//          by Peter Reilley's portable binary editor and viewer BEAV to detect
//          a Wang PC.
//        Toshiba laptops contain the signature "TOSHIBA" at FE010h as part of
//          a laptop information record at F000h:E000h (see #00520)
//        some AST machines contain the string "COPYRIGHT AST RESEARCH" one byte
//          past the end of the configuration table
//        the Phoenix 386 BIOS contains a second version and date string
//          (presumably the last modification for that OEM version) beginning at
//          F000h:FFD8h, with each byte doubled (so that both ROM chips contain
//          the complete information)
//SeeAlso: AH=C7h,AH=C9h,AX=D100h,AX=D103h
//
//Format of ROM configuration table:
//Offset  Size    Description     (Table 00509)
//@ 00h    WORD    number of bytes following
//@ 02h    BYTE    model (see #00515)
//@ 03h    BYTE    submodel (see #00515)
//@ 04h    BYTE    BIOS revision: 0 for first release, 1 for 2nd, etc.
// 05h    BYTE    feature byte 1 (see #00510)
// 06h    BYTE    feature byte 2 (see #00511)
// 07h    BYTE    feature byte 3 (see #00512)
// 08h    BYTE    feature byte 4 (see #00513)
// 09h    BYTE    feature byte 5 (see #00514)
//                ??? (08h) (Phoenix 386 v1.10)
//                ??? (0Fh) (Phoenix 486 v1.03 PCI)
//---AWARD BIOS---
// 0Ah  N BYTEs   AWARD copyright notice
//---Phoenix BIOS---
// 0Ah    BYTE    ??? (00h)
// 0Bh    BYTE    major version
// 0Ch    BYTE    minor version (BCD)
// 0Dh  4 BYTEs   ASCIZ string "PTL" (Phoenix Technologies Ltd)
//                also on Phoenix Cascade BIOS
//---Quadram Quad386---
// 0Ah 17 BYTEs   ASCII signature string "Quadram Quad386XT"
//---Toshiba (Satellite Pro 435CDS at least)---
// 0Ah  7 BYTEs   signature "TOSHIBA"
// 11h    BYTE    ??? (8h)
// 12h    BYTE    ??? (E7h) product ID??? (guess)
// 13h  3 BYTEs   "JPN"
//
//Bitfields for feature byte 1:
//Bit(s)  Description     (Table 00510)
// 7      DMA channel 3 used by hard disk BIOS
// 6      2nd interrupt controller (8259) installed
// 5      Real-Time Clock installed
// 4      INT 15/AH=4Fh called upon INT 09h
// 3      wait for external event (INT 15/AH=41h) supported
// 2      extended BIOS area allocated (usually at top of RAM)
// 1      bus is Micro Channel instead of ISA
// 0      system has dual bus (Micro Channel + ISA)
//SeeAlso: #00509,#00511
//
//Bitfields for feature byte 2:
//Bit(s)  Description     (Table 00511)
// 7      32-bit DMA supported
// 6      INT 16/AH=09h (keyboard functionality) supported (see #00585)
// 5      INT 15/AH=C6h (get POS data) supported
// 4      INT 15/AH=C7h (return memory map info) supported
// 3      INT 15/AH=C8h (en/disable CPU functions) supported
// 2      non-8042 keyboard controller
// 1      data streaming supported
// 0      reserved
//SeeAlso: #00509,#00512,AH=C6h,AH=C7h,AH=C8h,INT 16/AH=09h
//
//Bitfields for feature byte 3:
//Bit(s)  Description     (Table 00512)
// 7      not used
// 6-5    reserved
// 4      POST supports ROM-to-RAM enable/disable
// 3      SCSI subsystem supported on system board
// 2      information panel installed
// 1      IML (Initial Machine Load) system (BIOS loaded from disk)
// 0      SCSI supported in IML
//SeeAlso: #00509,#00511,#00512
//
//Bitfields for feature byte 4:
//Bit(s)  Description     (Table 00513)
// 7      IBM "private" (set on N51SX, CL57SX)
// 6      system has EEPROM
// 5-3    ABIOS presence
//        001 not supported
//        010 supported in ROM
//        011 supported in RAM (must be loaded)
// 2      "private"
// 1      system supports memory split at/above 16M
// 0      POSTEXT directly supported by POST
//SeeAlso: #00509,#00512,#00514
//
//Bitfields for feature byte 5 (IBM):
//Bit(s)  Description     (Table 00514)
// 7-5    IBM "private"
// 4-2    reserved
// 1      system has enhanced mouse mode
// 0      flash EPROM
//SeeAlso: #00509,#00513
//

/* Intel Official AT Memory Map
0000_0000h - 0009_FFFFh 640KB Main memory
000A_0000h - 000B_FFFFh 128KB Display buffer for video adapters
000C_0000h - 000D_FFFFh 128KB ROM BIOS for add-on cards
000E_0000h - 000F_FFFFh 128KB System ROM BIOS
0010_0000h - FEBF_FFFFh Main memory (Maximum address depends on total memory installed in the system.)
FEC0_0000h - FECF_FFFFh APIC I/O unit
FED0_0000h - FEDF_FFFFh Reserved for memory-mapped I/O devices
FEE0_0000h - FEEF_FFFFh APIC Local Unit
FEF0_0000h - FFFD_FFFFh Reserved for memory-mapped I/O devices
FFFE_0000h - FFFF_FFFFh 128KB Initialization ROM
*/
