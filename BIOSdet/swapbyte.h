/************************************************************************
  Claunia.com
 ------------------------------------------------------------------------

        Filename   : swapbyte.h
        Version    : 0.01
        Author(s)  : Natalia Portillo
            
        Component : Any Claunia.com source code that needs endian swapping.

 --[ Description ]-------------------------------------------------------
  
        Swaps the value of a 2, 4 or 8 bytes number.

 --[ History ] ----------------------------------------------------------
	
        0.01: Original file by Natalia Portillo. Only 2 bytes number.

 --[ How to compile ]----------------------------------------------------

        Designed for compile in any compiler in any machine.

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
 Copyright (c) 2000 Claunia.com
*************************************************************************/

unsigned short swap_two_bytes(unsigned short value){ //Swap 2-bytes number
    unsigned char first_byte,second_byte; //Declare two bytes

    first_byte=value<<8>>8;  //Convert the second byte in the first
    second_byte=value>>8; //Convert the first byte in the second

    return first_byte<<8 ^ second_byte; //Return the swapped 2-bytes number
}
