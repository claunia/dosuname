/************************************************************************
  T h e   O p e n   W i n d o w s   P r o j e c t
 ------------------------------------------------------------------------

        Filename   : ver.h
        Version    : 0.03
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

/* OWP DOS Subsystem general definition */
#ifndef OWP_DOS_SUBSYSTEM
#define OWP_DOS_SUBSYSTEM
#endif

/* Program general definitions */
#define SYSTEM "OWP"
#define PROGRAM "VER"
#define MAJOR_VERSION 0
#define MINOR_VERSION_STRING "03"
#define SUB_VERSION_STRING ""
#define COPYRIGHT "2000 Open Windows Project"

/* DOS types definition */
#define UNKNOWN 0
#define MS_DOS  1
#define PC_DOS  2
#define DR_DOS  3
#define FreeDOS 4
#define Win95   5
#define WinNT   6
#define OS2     7 /* Not tested yet, so not implemented yet */
#define PTS_DOS 8
#define RxDOS   9
#define ConDOS  10 /* Concurrent DOS, not tested yet */
#define NVDOS   11 /* Novell version of DR_DOS, not tested yet */
#define OLD     12
#define Win98   13
#define ERROR   255
