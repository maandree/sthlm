#ifndef KERNEL_ARCH_KTTY_H
#define KERNEL_ARCH_KTTY_H


/**
 * The number of lines in the terminal
 */
#define KTTY_LINES    25

/**
 * The number of columns in the terminal
 */
#define KTTY_COLUMNS  80


/**
 * Print single character to the terminal, may not include ANSI escape codes
 * 
 * @param  symbol  The charcter to print
 * @param  attr    Charcter attributes
 * @param  y       The line on which to print
 * @param  x       The column at which to print, may overflow to set line
 */
void kputc(char symbol, char attr, long y, long x);

/**
 * Move a printed text segment
 * 
 * @param  dest_y  The start destination line
 * @param  dest_x  The start destination column, may overflow to set line
 * @param  src_y   The start source line
 * @param  src_x   The start source column, may overflow to set line
 * @param  n       The number of characters to move
 */
void kttymove(long dest_y, long dest_x, long src_y, long src_x, long n);


#endif

