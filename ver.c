/************************************************************************
  T h e   O p e n   W i n d o w s   P r o j e c t
 ------------------------------------------------------------------------

        Filename   : ver.c
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

#include <stdio.h>
#include "ver.h" /* Include definitions */

int main()
{
   /* Declare variables */
   int dos_major,dos_minor,dostype,dos_sim_major,dos_sim_minor,dos_oem,desq_ma,desq_mi,_4dos_ma,_4dos_mi,ndos_ma,ndos_mi,win_ma,win_mi,win_mode;

   /* Put copyright info */
   printf("%s %s %d.%s%s",SYSTEM,PROGRAM,MAJOR_VERSION,MINOR_VERSION_STRING,SUB_VERSION_STRING);
   printf("\nCopyright (c) %s\n\n",COPYRIGHT);

   /* Get DOS version stuff */
   getdosver(&dostype, &dos_major, &dos_minor, &dos_sim_major, &dos_sim_minor, &dos_oem, &desq_ma, &desq_mi, &_4dos_ma, &_4dos_mi, &ndos_ma, &ndos_mi, &win_ma, &win_mi, &win_mode);

   /* Put version info */
   if(dostype == 0)
        {
        printf("\nUnknown DOS version %d.%d, that is simulating DOS %d.%d",dos_major,dos_minor,dos_sim_major,dos_sim_minor);
        printf("\nDOS OEM code %x",dos_oem);
	printf("\nPlease send this info and the O.S. name and version to\niosglpgc@teleline.es");
	return(1);
        }
   if(dostype == 1)
        {
        printf("\nMS-DOS version %d.%d\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf(" simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 2)
        {
        printf("\nPC-DOS version %d.%d\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 3)
        {
        printf("\nDR-DOS version %d.%d\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 4)
        {
        printf("\nFreeDOS version 1.1.%d\n",dos_major);
        printf(" simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
        }
   if(dostype == 5)
        {
        printf("\nWindows 95\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 6)
        {
        printf("\nWindows NT or Windows 2000\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 7)
        {
        printf("\nOS/2 ");
        if(dos_major == 10)
             {
             printf("1.0\n");
             }
        else if(dos_major == 20 && dos_minor < 30)
                  {
                  printf("2.0\n");
                  }
             else if(dos_major == 20 && dos_minor == 30)
                  {
                  printf("Warp 3\n");
                  }
                  else if(dos_major == 20 && dos_minor == 40)
                       {
                       printf("Warp 4\n");
                       }
                       else{printf("unknown version\n");}
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 8)
        {
	printf("\nPTS-DOS, unknown version\n");
        printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
        }
   if(dostype == 9)
        {
        printf("\nRxDOS version %d.%d\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 10)
        {
        printf("\nConcurrent DOS version %d.%d\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 11)
        {
        printf("\nNovell DOS version %d.%d\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 12)
        {
        printf("\nMS-DOS / PC-DOS version %d.%d\n",dos_major,dos_minor);
        }
   if(dostype == 13)
        {
        if(win_mi < 10)
            {
            printf("\nWindows 95 OSR 2 or OSR 3\n");
            }
        else if(win_mi >= 10)
                 {
                 printf("\nWindows 98 or 98 S.E.\n");
                 }
             else
                 {
                 printf("\nWindows 95 OSR 2 or upper\n");
                 }
        if(dos_major!=dos_sim_major || dos_minor!=dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 14)
        {
        printf("\nWindows Millenium\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("simulating DOS version %d.%d\n",dos_sim_major,dos_sim_minor);
             }
        }
   if(desq_ma >= 2)
        {
        printf("Running under DESQview %d.%d\n",desq_ma,desq_mi);
        }
   if(_4dos_ma >= 2)
        {
        if(_4dos_mi < 10)
            printf("Running under 4DOS %d.0%d\n",_4dos_ma,_4dos_mi);
        else
            printf("Running under 4DOS %d.%d\n",_4dos_ma,_4dos_mi);
        }
   if(ndos_ma > 0)
        {
        printf("Running under NDOS %d.%d\n",ndos_ma,ndos_mi);
        }
   if(win_ma == 3 && win_mi < 10 && win_mode == 3)
        {
        printf("Running under Windows %d.%d in enhanced mode\n",win_ma,win_mi);
        }
   if(win_ma == 3 && win_mi >= 10)
        {
        if(win_mode == 2)
            {
            printf("Running under Windows %d.%d in standard mode\n",win_ma,win_mi);
            }
        else if(win_mode == 3)
                 {
                 printf("Running under Windows %d.%d in enhanced mode\n",win_ma,win_mi);
                 }
                 else
                     {
                     printf("Running under Windows %d.%d\n",win_ma,win_mi);
                     }
        }
   if(win_ma == 2 && win_mode == 3)
        {
        printf("Running under Windows/386 %d.%d\n",win_ma,win_mi);
        }
return(0);
}
