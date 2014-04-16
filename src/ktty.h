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

