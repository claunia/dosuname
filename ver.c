/************************************************************************
  T h e   O p e n   W i n d o w s   P r o j e c t
 ------------------------------------------------------------------------

        Filename   : ver.c
        Version    : 0.01
        Author(s)  : Natalia Portillo
            
        Component : OWP DOS subsystem

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

#ifndef OWP_DOS_SUBSYSTEM
#define OWP_DOS_SUBSYSTEM
#endif

#define SYSTEM "OWP"
#define PROGRAM "VER"
#define MAJOR_VERSION 0
#define MINOR_VERSION_STRING "02"
#define SUB_VERSION_STRING ""
#define COPYRIGHT "2000 Open Windows Project"

#include <stdio.h>
#include <dos.h>

void getdosver (int *major,int *minor,int *oem_code)
{
   union REGS regs;
   regs.x.ax = 0x3000;
   int86 (0x21,&regs,&regs);
   *major = regs.h.al;
   *minor = regs.h.ah;
   *oem_code = regs.h.bh;
}

main()
{
   int dos_major,dos_minor,dos_oem_code;

   printf("%s %s %d.%s%s",SYSTEM,PROGRAM,MAJOR_VERSION,MINOR_VERSION_STRING,SUB_VERSION_STRING);
   printf("\nCopyright (c) %s\n\n",COPYRIGHT);
   getdosver (&dos_major,&dos_minor,&dos_oem_code);

   if(dos_oem_code==0xFD)
       {
       printf("FreeDOS simulating DOS %d.%d",dos_major,dos_minor);
       }
   else if(dos_oem_code==0x00)
        {
        if(dos_major<=3)
            {
            printf("MS-DOS / PC-DOS %d.%d",dos_major,dos_minor);
            }
        else if(dos_major>=4)
             {
             printf("DR-DOS simulating DOS %d.%d",dos_major,dos_minor);
             }
        }
        else if(dos_oem_code==0xFF && dos_major>=4 && dos_major <=6)
             {
             printf("MS-DOS / PC-DOS %d.%d",dos_major,dos_minor);
             if(dos_major==5)
                 {
                 printf("\nNOTE: May be OS/2 / Windows NT simulating DOS 5.0");
                 }
             }
             else if(dos_oem_code==0xFF && dos_major>=7)
                  {
                  if(dos_minor==0)
                      {
                      printf("Windows 95 simulating DOS 7.00");
                      printf("\nNOTE: May be PC-DOS 7.0");
                      }
                  else if(dos_minor==10)
                       {
                       printf("Windows 95 OSR 2 or upper simulating DOS 7.10");
                       printf("\nNOTE: May be PC-DOS 7.1");
                       }
                       else
                           {
                           printf("PC-DOS %d.%d",dos_major,dos_minor);
                           }
                  }
                  else if(dos_oem_code==0xFF && dos_major==3)
                       {
                       printf("MS-DOS %d.%d",dos_major,dos_minor);
                       }
                       else if(dos_oem_code==0x5E)
                            {
                            printf("RxDOS %d.%d",dos_major,dos_minor);
                            }
                            else if(dos_oem_code==0x66)
                                 {
                                 printf("PTS-DOS simulating DOS %d.%d",dos_major,dos_minor);
                                 }
                                 else
                                     {
                                     printf("Unknown DOS version %d.%d,OEM code %x",dos_major,dos_minor,dos_oem_code);
                                     printf("\nPlease send this info and the DOS name and version to iosglpgc@teleline.es");
                                     }
}

