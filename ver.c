/************************************************************************
  Claunia.com
 ------------------------------------------------------------------------

        Filename   : ver.c
        Version    : 0.07
        Author(s)  : Natalia Portillo
            
        Component : UNAME for DOS

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
        0.05: Corrected an error with minor versions of OS/2 2.x and 1.x
              Implemented SoftICE debugger detection. But not tested.
              All text strings moved to language.h
              Translated to spanish and french.
              Corrected an error with DOS versions prior to 5.x when testing
              the true DOS version
        0.06: Implemented detection of Windows XP.
              Corrected an error with OS/2 2.x versions.
        0.07: Implemented a workaround so OS/2 3.x and upper versions can be
              easily detected, without exact knowledge of the versions by
              this program.

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
 Copyright (c) 2001 Claunia.com
*************************************************************************/

#include <stdio.h>
#include "ver.h" /* Include definitions */
#include "language.h" /* Language definitions */

int main()
{
   /* Declare variables */
   int dos_major,dos_minor,dostype,dos_sim_major,dos_sim_minor,dos_oem,desq_ma,desq_mi,_4dos_ma,_4dos_mi,ndos_ma,ndos_mi,win_ma,win_mi,win_mode,softice_ma,softice_mi;

   /* Put copyright info */
   printf("%s %s %d.%s%s",SYSTEM,PROGRAM,MAJOR_VERSION,MINOR_VERSION_STRING,SUB_VERSION_STRING);
   printf("\nCopyright (c) %s\n\n",COPYRIGHT);

   /* Get DOS version stuff */
   getdosver(&dostype, &dos_major, &dos_minor, &dos_sim_major, &dos_sim_minor, &dos_oem, &desq_ma, &desq_mi, &_4dos_ma, &_4dos_mi, &ndos_ma, &ndos_mi, &win_ma, &win_mi, &win_mode, &softice_ma, &softice_mi);

   /* Put version info */
   if(dostype == 1)
        {
        printf("\nMS-DOS %s %d.%d\n",szVersion,dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 2)
        {
        printf("\nPC-DOS %s %d.%d\n",szVersion,dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 3)
        {
        printf("\nDR-DOS %s %d.%d\n",szVersion,dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 4)
        {
        printf("\nFreeDOS %s 1.1.%d\n",szVersion,dos_major);
        printf(" %s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
        }
   if(dostype == 5)
        {
        printf("\nWindows 95\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 6)
        {
        printf("\nWindows NT, Windows 2000 %s Windows XP\n",szOr);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 7)
        {
        printf("\nOS/2 ");
        if(dos_major == 10)
             {
             printf("1.%d\n",dos_minor);
             }
        else if(dos_major == 20 && dos_minor < 30)
                  {
                  printf("2.%d\n",dos_minor);
                  }
             else if(dos_major == 20 && dos_minor >= 30)
                  {
                  printf("Warp %1.2d\n",(dos_minor/10));
                  }
                  else{printf("%s\n",szUnknownVer);}
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 8)
        {
        printf("\nPTS-DOS, %s\n",szUnknownVer);
        printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
        }
   if(dostype == 9)
        {
        printf("\nRxDOS %s %d.%d\n",szVersion,dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 10)
        {
        printf("\nConcurrent DOS %s %d.%d\n",szVersion,dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 11)
        {
        printf("\nNovell DOS %s %d.%d\n",szVersion,dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 12)
        {
        printf("\nMS-DOS / PC-DOS %s %d.%d\n",szVersion,dos_major,dos_minor);
        }
   if(dostype == 13)
        {
        if(win_mi < 10)
            {
            printf("\nWindows 95 OSR 2 %s OSR 3\n",szOr);
            }
        else if(win_mi >= 10)
                 {
                 printf("\nWindows 98 %s 98 S.E.\n",szOr);
                 }
             else
                 {
                 printf("\nWindows 95 OSR 2 %s\n",szOrUpper);
                 }
        if(dos_major!=dos_sim_major || dos_minor!=dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(dostype == 14)
        {
        printf("\nWindows Millenium\n",dos_major,dos_minor);
        if(dos_major != dos_sim_major || dos_minor != dos_sim_minor)
             {
             printf("%s %d.%d\n",szSimulating,dos_sim_major,dos_sim_minor);
             }
        }
   if(desq_ma >= 2)
        {
        printf("%s DESQview %d.%d\n",szRunUnder,desq_ma,desq_mi);
        }
   if(_4dos_ma >= 2)
        {
        if(_4dos_mi < 10)
            printf("%s 4DOS %d.0%d\n",szRunUnder,_4dos_ma,_4dos_mi);
        else
            printf("%s 4DOS %d.%d\n",szRunUnder,_4dos_ma,_4dos_mi);
        }
   if(ndos_ma > 0)
        {
        printf("%s NDOS %d.%d\n",szRunUnder,ndos_ma,ndos_mi);
        }
   if(win_ma == 3 && win_mi < 10 && win_mode == 3)
        {
        printf("%s Windows %d.%d %s\n",szRunUnder,win_ma,win_mi,szEnhMode);
        }
   if(win_ma == 3 && win_mi >= 10)
        {
        if(win_mode == 2)
            {
            printf("%s Windows %d.%d %s\n",szRunUnder,win_ma,win_mi,szStdMode);
            }
        else if(win_mode == 3)
                 {
                 printf("%s Windows %d.%d %s\n",szRunUnder,win_ma,win_mi,szEnhMode);
                 }
                 else
                     {
                     printf("%s Windows %d.%d\n",szRunUnder,win_ma,win_mi);
                     }
        }
   if(win_ma == 2 && win_mode == 3)
        {
        printf("%s Windows/386 %d.%d\n",szRunUnder,win_ma,win_mi);
        }
   if(softice_ma != 0 && softice_mi == 3)
        {
        printf("%s %s\n",szRunUnder,szSoftIce); //Version detection no yet implemented
        }
   if(dostype == 0)
        {
        printf("\n%s %d.%d, %s %d.%d",szUnkDOS,dos_major,dos_minor,szThatSim,dos_sim_major,dos_sim_minor);
        printf("\n%s %x",szOEM,dos_oem);
        printf("\n%s\niosglpgc@teleline.es",szInfo);
	return(1);
        }
   else {return(0);}
}
