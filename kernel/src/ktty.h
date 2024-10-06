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
#ifndef KERNEL_KTTY_H
#define KERNEL_KTTY_H


/*
 * This module is responsible for providing basic text output
 * capabilities for the kernel for debugging and panic purposes.
 */


#include "arch/ktty.h"
#include <stdarg.h> /* built in */



/**
 * Buffer size for communication between `kvaprintf` and `vasnprintf`
 */
#define KPRINT_BUFFER_SIZE  256



/**
 * Print string to the terminal, may include ANSI escape codes
 * 
 * @param  str  The string to print
 */
void kputs(const char* str);

/**
 * Format an print a string into the terminal
 * 
 * @param   format  The format template to use
 * @param   ...     Input data with which to fill the template
 * @return          Zero if and only if everything was printed,
 *                  otherwise the output was truncated with an
 *                  ultimate length of `KPRINT_BUFFER_SIZE`
 */
int kprintf(const char* format, ...);

/**
 * Format an print a string into the terminal
 * 
 * @param   format  The format template to use
 * @param   args    Input data with which to fill the template
 * @return          Zero if and only if everything was printed,
 *                  otherwise the output was truncated with an
 *                  ultimate length of `KPRINT_BUFFER_SIZE`
 */
int kvaprintf(const char* format, va_list args);


#endif

