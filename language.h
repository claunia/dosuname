/************************************************************************
  Claunia.com
 ------------------------------------------------------------------------

        Filename   : language.h
        Version    : 0.07
        Author(s)  : Natalia Portillo
                     Oliver Dick (translation to German)
            
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

/* Language definitions */

// No language defined, so english
#define szVersion "version"
#define szSimulating "simulating DOS version"
#define szOr "or"
#define szUnknownVer "unknown version"
#define szOrUpper "or upper"
#define szRunUnder "Running under"
#define szEnhMode "in enhanced mode"
#define szStdMode "in standard mode"
#define szSoftIce "SoftICE debugger"
#define szUnkDOS "Unknown DOS version"
#define szThatSim "that is simulating DOS"
#define szOEM "DOS OEM code"
#define szInfo "Please send this info and the operating system name and version to"

#ifdef __OWP__ENGLISH__ //English -- Natalia Portillo
#define szVersion "version"
#define szSimulating "simulating DOS version"
#define szOr "or"
#define szUnknownVer "unknown version"
#define szOrUpper "or upper"
#define szRunUnder "Running under"
#define szEnhMode "in enhanced mode"
#define szStdMode "in standard mode"
#define szSoftIce "SoftICE debugger"
#define szUnkDOS "Unknown DOS version"
#define szThatSim "that is simulating DOS version"
#define szOEM "DOS OEM code"
#define szInfo "Please send this info and the operating system name and version to"
#endif //End English

#ifdef __OWP__SPANISH__ //Spanish -- Natalia Portillo
#define szVersion "versi¢n"
#define szSimulating "simulando DOS versi¢n"
#define szOr "o"
#define szUnknownVer "versi¢n desconocida"
#define szOrUpper "o superior"
#define szRunUnder "Ejecut ndose bajo"
#define szEnhMode "en modo mejorado"
#define szStdMode "en modo est ndar"
#define szSoftIce "el depurador SoftICE"
#define szUnkDOS "DOS desconocido versi¢n"
#define szThatSim "que est  simulando DOS versi¢n"
#define szOEM "C¢digo OEM del DOS"
#define szInfo "Por favor env¡e esta informaci¢n y el nombre y versi¢n del sistema operativo a"
#endif //End Spanish

#ifdef __OWP__FRENCH__ //French -- Natalia Portillo
#define szVersion "version"
#define szSimulating "simulant DOS version"
#define szOr "ou"
#define szUnknownVer "version inconnu"
#define szOrUpper "ou sup‚rieur"
#define szRunUnder "se ex‚cutant vil"
#define szEnhMode "en mode am‚liorant"
#define szStdMode "en mode standard"
#define szSoftIce "l'‚purateur SoftICE"
#define szUnkDOS "Inconnu DOS version"
#define szThatSim "qui est simulant DOS"
#define szOEM "Code OEM du DOS"
#define szInfo "S'il vous plaŒt envoye este information et le nom et version du systŠme op‚rationel a"
#endif //End French

#ifdef __OWP__GERMAN__ //German -- Oliver Dick
#define szVersion "Version"
#define szSimulating "simuliert DOS-Version"
#define szOr "oder"
#define szUnknownVer "unbekannte Version"
//#define szOrUpper "oder hoeher" //Without any accent
#define szOrUpper "oder h”her"
//#define szRunUnder "Laeuft unter" //Without any accent
#define szRunUnder "L„uft unter"
#define szEnhMode "im erweiterten Modus"
#define szStdMode "im Standard Modus"
#define szSoftIce "SoftICE debugger"
#define szUnkDOS "unbekannte DOS-Version"
#define szThatSim "simuliert DOS"
#define szOEM "DOS OEM code"
#define szInfo "Bitte senden Sie diese Informationen, sowie Name und Version ihres Betriebssystems an"
#endif //End German

#ifdef __OWP__BABLE__ //Bable -- Javier Prieto Garamendi
#define szVersion "version"
#define szSimulating "ximulando DOS versi¢n"
#define szOr "o"
#define szUnknownVer "version desconoxia"
#define szOrUpper "o superior"
#define szRunUnder "Executandose baxo"
#define szEnhMode "en modu mexorau"
#define szStdMode "en modu estandar"
#define szSoftIce "el depurador SoftICE"
#define szUnkDOS "DOS desconoxia version"
#define szThatSim "que esta simulando DOS version"
#define szOEM "Codigu OEM del DOS"
#define szInfo "Por favor envie nesta informaxion y el nome y version del sistema operativu a"
#endif //End Bable
