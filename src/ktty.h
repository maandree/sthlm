#ifndef KERNEL_KTTY_H
#define KERNEL_KTTY_H


#include "arch/ktty.h"


/**
 * The number of lines in the terminal
 */
#define KTTY_LINES    25

/**
 * The number of columns in the terminal
 */
#define KTTY_COLUMNS  80


/**
 * Print string to the terminal, may include ANSI escape codes
 * 
 * @param  str  The string to print
 */
void kputs(const char* str);


#endif

