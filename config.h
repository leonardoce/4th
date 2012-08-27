#ifndef __CONFIG_H
#define __CONFIG_H

/**
 * This code permit to configure this Forth System to operate
 * on 32 or 64 bit computers
 */ 

#ifdef SYSTEM_64

typedef long ForthInstructionAddress;
typedef long ForthDataAddress;
typedef long ForthCell;
#define CELL_PRINTF_FORMAT "%li "

#else

typedef int ForthInstructionAddress;
typedef int ForthDataAddress;
typedef int ForthCell;
#define CELL_PRINTF_FORMAT "%i "
#endif

#endif
