/**
 * Copyright © 2014  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
  if (likely(dest < src))
    for (i = 0; i < n; i++)
      *(vidptr + dest + i) = *(vidptr + src + i);
  else if (unlikely(dest > src))
    for (i = n - 1; i >= 0; i--)
      *(vidptr + dest + i) = *(vidptr + src + i);
}

