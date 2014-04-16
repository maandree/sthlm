#include "ktty.h"


/**
 * The beginning of the memory where the output is written
 */
#define VIDEO_MEMORY  0xb8000


/**
 * Print single character to the terminal, may not include ANSI escape codes
 * 
 * @param  symbol  The charcter to print
 * @param  attr    Charcter attributes
 * @param  y       The line on which to print
 * @param  x       The column at which to print, may overflow to set line
 */
void kputc(char symbol, char attr, long y, long x)
{
  char* vidptr = (char*)VIDEO_MEMORY;
  *(vidptr + (y * KTTY_COLUMNS + x) * 2 + 0) = symbol;
  *(vidptr + (y * KTTY_COLUMNS + x) * 2 + 1) = attr;
}


/**
 * Move a printed text segment
 * 
 * @param  dest_y  The start destination line
 * @param  dest_x  The start destination column, may overflow to set line
 * @param  src_y   The start source line
 * @param  src_x   The start source column, may overflow to set line
 * @param  n       The number of characters to move
 */
void kttymove(long dest_y, long dest_x, long src_y, long src_x, long n)
{
  char* vidptr = (char*)VIDEO_MEMORY;
  long dest = 2 * (dest_y * KTTY_COLUMNS + dest_x);
  long src  = 2 * ( src_y * KTTY_COLUMNS +  src_x);
  long i;
  
  n *= 2;
  if (dest < src)
    for (i = 0; i < n; i++)
      *(vidptr + dest + i) = *(vidptr + src + i);
  else if (dest > src)
    for (i = n - 1; i >= 0; i--)
      *(vidptr + dest + i) = *(vidptr + src + i);
}

