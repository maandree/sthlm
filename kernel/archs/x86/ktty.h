/**
 * Copyright © 2014  Mattias Andrée (m@maandree.se)
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

