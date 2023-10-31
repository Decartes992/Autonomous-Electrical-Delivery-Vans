#pragma once

#ifndef GENERAL_H
#define GENERAL_H

#include <Windows.h> /* For Windows-specific graphic data type and functions */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define NUL 0x00
#define ESC 0x1b

/*
 - Box character codes (decimal)
 - See https://www.lookuptables.com/text/extended-ascii-table
*/
#define UL 218
#define LL 192
#define UR 191
#define LR 217
#define HBAR 196
#define VBAR 179

#define MAXSIZE 100
#define NumeroAEDV 4
#define MAXMAP 5
#define offsetid 999
#define yoffset 1
#define buildoffset 20
#define Hoffset 5
#define Voffset 6
#define cursoroffset 2



#define DISP(x) putc((x), stdout)

HANDLE Console; /* Identify action and I/O stream */
extern FILE* filein;





#endif GENERAL_H
