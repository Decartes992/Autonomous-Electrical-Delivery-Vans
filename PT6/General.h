#pragma once
/*MODULE: GENERAL HEADER
*
* WHAT IT DOES: THE GENERAL HEADER FILE ACHEIVE THE PURPOSE 
* OF DECLARING THE REQUIRED GENERAL PREPROCESSOR DIRECTIVES 
* 
* DATE: 10-29-2023
*
* NAME:
* IFTEKHAR RAFI
* WILLIAM THORNTON
*
*/




#ifndef GENERAL_H
#define GENERAL_H

#include <Windows.h> /* For Windows-specific graphic data type and functions */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>

#define NUL 0x00
#define ESC 0x1b


#define UL 218
#define LL 192
#define UR 191
#define LR 217
#define HBAR 196
#define VBAR 179

#define MAXSIZE 100
#define NumeroAEDV 4
#define MAXMAP 20
#define offsetid 999
#define ZERO 0

#define yoffset 1
#define Voffset 6
#define cursoroffset 2
#define Voffsetfortext 9
#define lowbatterylevel 20	//definition for the battery level at which AEDVs will stop taking orders and go to charge
#define buildoffset 6
#define Hoffset 4
#define Voffset 4

/* Prefixes for ESC sequences */
#define ESC "\x1b"	/* Escape */
#define CSI "\x1b["	/* Control Sequence Introducer */

#define TRUE	1
#define FALSE	0

/* Some commonly used VT-100 commands */
#define CUP(c,r)	printf(CSI "%d;%dH", (r), (c)); /* Move cursor position to col, row */
#define EL(r)		printf(CSI "%d;1H" CSI "K", (r)); /* Erase in Line */
#define CLRSCR		printf(CSI "2J");

/* Colour: ESC [ <n> m */
enum VT100_COLOURS {
	FGWHITE = 32,
	BGRED = 41,
	BGGREEN = 42,
	BGYELLOW = 43,
	BGBLUE = 44,
	BGCYAN = 46
};

#define DISP(x) putc((x), stdout)

HANDLE Console; /* Identify action and I/O stream */
extern FILE* filein;




#endif //GENERAL_H
