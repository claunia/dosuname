/************************************************************************
  T h e   O p e n   W i n d o w s   P r o j e c t
 ------------------------------------------------------------------------

        Filename   : int21h.c
        Version    : 0.04
        Author(s)  : Natalia Portillo
            
        Component : OWP DOS subsystem - VER command

 --[ Description ]-------------------------------------------------------
  
        Says the DOS type and version.

 --[ History ] ----------------------------------------------------------
	
        0.00: Original file by Natalia Portillo. No DOS type.
        0.01: Tested with following DOSes obtaining:
              DOS             DOS Version     DOS OEM Code
              DR-DOS 7.03     6.0             0x00
              FreeDOS Beta 4  6.22            0xFD
              MS-DOS 3.20     3.20            0x00
              MS-DOS 3.30     3.30            0x00
              MS-DOS 4.01     4.0             0xFF
              MS-DOS 5.00     5.0             0xFF
              PC-DOS 3.30     3.30            0x00
              Windows 98 S.E. 7.10            0xFF
              Windows 2000    5.0             0xFF
        0.02: Tested with the following DOSes obtaining:
              DOS             DOS Version     DOS OEM Code
              PTS-DOS 2000    6.22            0x66
              RxDOS 7.1.5     7.0             0x5E
        0.03: Almost remade from zero.
              Now uses four functions of INT-21h to get almost all
              DOS version information.
              All detect stuff moved to int21h.c.
              All defines moved to ver.h
        0.04: Implemented detection of DESQview, 4DOS and NDOS.
              Implemented detection of the Windows version.
              Implemented detection of OS/2.
              Implemented detection of Windows Millenium (tested with beta 3).

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

#include <dos.h>

void getdosver (int *DOS_FLAVOR, int *major, int *minor, int *sim_major, int *sim_minor, int *dos_oem, int *desq_ma, int *desq_mi, int *_4dos_ma, int *_4dos_mi, int *ndos_ma, int *ndos_mi, int *win_ma, int *win_mi, int *win_mode)
{
   union REGS regs;
   int dos_temp, nt_flag;
   nt_flag=0;
   *DOS_FLAVOR=0;

   regs.x.ax = 0x3306; /* Set function 3306h */
   int86 (0x21,&regs,&regs); /* Call INT 21h */
   if(regs.h.al!=255) /* If DOS >= 5.0 */
        {
        *major = regs.h.bl; /* Major True version */
        *minor = regs.h.bh; /* Minor True version */
        if(regs.h.bh==50)
             {
             *minor = 0;
             nt_flag = 1;
             }

        regs.h.ah = 0x30;
        regs.h.al = 0x00;
        int86 (0x21,&regs,&regs);
        dos_temp = regs.h.bh; /* Set DOS type */
        if(dos_temp == 253) /* Checks for FreeDOS */
             {
             *major = regs.h.bl; /* Get FreeDOS kernel version */
             *minor = 0; /* Put minor version to zero */
             }
        *sim_major = regs.h.al; /* Set the simulated major version */
        *sim_minor = regs.h.ah; /* Set the simulated minor version */
        }
   else {
        regs.h.ah = 0x30;
        regs.h.al = 0x00;
        int86 (0x21,&regs,&regs);
        dos_temp = regs.h.bh; /* Set DOS type */
        *major = regs.h.al; /* Set the simulated major version */
        *minor = regs.h.ah; /* Set the simulated minor version */
        *sim_major = 0;
        *sim_minor = 0;
        }

/* Set DOS to DOS type */
   if(dos_temp == 0 && *major <= 3)
        {
        *DOS_FLAVOR=12;
        }
   if(dos_temp == 0 && *major >= 4)
        {
        *DOS_FLAVOR=2;
        }
   if(dos_temp == 0 && *major >= 10)
        {
        *DOS_FLAVOR=7;
        }
   if(dos_temp == 0xff && *major <= 6)
        {
        *DOS_FLAVOR=1;
        }
   if(dos_temp == 0xff && *major == 7)
        {
        if(*minor == 0)
             {
             *DOS_FLAVOR=5;
             }
        if(*minor == 10)
             {
             *DOS_FLAVOR=13;
             }
        }
   if(dos_temp == 0xff && *major == 8)
        {
        *DOS_FLAVOR=14;
        }
   if(dos_temp == 253)
        {
        *DOS_FLAVOR=4;
        }
   if(dos_temp == 0xff && nt_flag == 1)
        {
        *DOS_FLAVOR=6;
        }
   if(dos_temp == 0x66)
        {
        *DOS_FLAVOR=8;
        }
   if(dos_temp == 0x5E)
        {
        *DOS_FLAVOR=9;
        }

/* Check for Concurrent DOS versions */
   regs.x.ax = 0x4451; /* Set function 4451h */
   int86 (0x21,&regs,&regs); /* Call INT 21h */
   if(regs.h.al==0x32)
        {
        *major=3;
        *minor=2;
        *DOS_FLAVOR=10;
        }
   if(regs.h.al==0x41)
        {
        *major=4;
        *minor=1;
        *DOS_FLAVOR=10;
        }
   if(regs.h.al==0x50)
        {
        *major=5;
        *minor=0;
        *DOS_FLAVOR=10;
        }
   if(regs.h.al==0x60)
        {
        *major=6;
        *minor=0;
        *DOS_FLAVOR=10;
        }
   if(regs.h.al==0x62)
        {
        *major=6;
        *minor=2;
        *DOS_FLAVOR=10;
        }
   if(regs.h.al==0x66)
        {
        *major=5;
        *minor=1;
        *DOS_FLAVOR=6;
        }
   if(regs.h.al==0x67)
        {
        *major=5;
        *minor=1;
        *DOS_FLAVOR=10;
        }
/* End of check for Concurrent DOS versions */

/* Check for DR-DOS versions */
   regs.x.ax = 0x4452; /* Set function 4452h */
   int86 (0x21,&regs,&regs); /* Call INT 21h */
   if(regs.h.al==0x41)
        {
        *major=1;
        *minor=2;
        *DOS_FLAVOR=3;
        }
   if(regs.h.al==0x60)
        {
        *major=2;
        *minor=0;
        *DOS_FLAVOR=3;
        }
   if(regs.h.al==0x63)
        {
        *major=3;
        *minor=41;
        *DOS_FLAVOR=3;
        }
   if(regs.h.al==0x64)
        {
        *major=3;
        *minor=42;
        *DOS_FLAVOR=3;
        }
   if(regs.h.al==0x65)
        {
        *major=5;
        *minor=0;
        *DOS_FLAVOR=3;
        }
   if(regs.h.al==0x67)
        {
        *major=6;
        *minor=0;
        *DOS_FLAVOR=3;
        }
   if(regs.h.al==0x71)
        {
        *major=6;
        *minor=0;
        *DOS_FLAVOR=3;
        }
   if(regs.h.al==0x72)
        {
        *major=7;
        *minor=0;
        *DOS_FLAVOR=11;
        }
   if(regs.h.al==0x73)
        {
        *major=7;
        *minor=0;
        *DOS_FLAVOR=3;
        }
/* End of check for DR-DOS_FLAVOR versions */
*dos_oem=dos_temp;
*desq_ma=0;
*desq_mi=0;
   regs.h.ah = 0x2b; /* Set function */
   regs.x.cx = 0x4445; /* Set function */
   regs.x.dx = 0x5351; /* Set function */
   regs.h.al = 0x01; /* Set function */
   int86 (0x21,&regs,&regs); /* Call INT 21h */
   if(regs.h.al!=0xFF)
        {
        *desq_ma=regs.h.bh;
        *desq_mi=regs.h.bl;
        }
*_4dos_ma=0;
*_4dos_mi=0;
   regs.h.bh = 0x00; /* Set function */
   regs.x.ax = 0xD44D; /* Set 4DOS API */
   int86 (0x2F,&regs,&regs); /* Call INT 2Fh */
   if(regs.x.ax==0x44DD)
        {
        *_4dos_ma=regs.h.bl;
        *_4dos_mi=regs.h.bh;
        }
*ndos_ma=0;
*ndos_mi=0;
   regs.h.bh = 0x00; /* Set function */
   regs.x.ax = 0xE44D; /* Set 4DOS API (Well, NDOS is the Norton version of 4DOS */
   int86 (0x2F,&regs,&regs); /* Call INT 2Fh */
   if(regs.x.ax==0x44EE)
        {
        *ndos_ma=regs.h.bl;
        *ndos_mi=regs.h.bh;
        }
*win_ma=0;
*win_mi=0;
*win_mode=0;
   regs.x.ax = 0x160A; /* Set function (Windows 3.1 or upper) */
   int86 (0x2F,&regs,&regs); /* Call INT 2Fh */
   if(regs.x.ax==0x0000)
        {
        *win_ma=regs.h.bh;
        *win_mi=regs.h.bl;
        *win_mode=regs.x.cx;
        }
   else
       {
       regs.x.ax = 0x1600; /* Set function (Windows/386 or upper in enhanced mode)*/
       int86 (0x2F,&regs,&regs); /* Call INT 2Fh */
       if(regs.h.al==0x01 || regs.h.al==0xFF)
	   {
	   *win_ma=2;
	   *win_mi=regs.h.ah;
	   *win_mode=3;
	   }
       else if(regs.h.al >= 3)
           {
           *win_ma=regs.h.al;
           *win_mi=regs.h.ah;
           *win_mode=3;
           }
	   else
	       *win_ma=*win_mi=0;
       }
}
