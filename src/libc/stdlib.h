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
#ifndef KERNEL_LIBC_STDLIB_H
#define KERNEL_LIBC_STDLIB_H


#include <stddef.h>
#include <stdarg.h> /* built in */


/**
 * NULL-pointer
 */
#define NULL  ((void*)0)


/**
 * Format an print a string into memory
 * 
 * @param   out     Location to print the string to
 * @param   size    The about of memory, in characters, allocated to `out`
 * @param   format  The format template to use
 * @param   ...     Input data with which to fill the template
 * @return          Zero if and only if everything was printed, otherwise
 *                  the output was truncated with an utimate length of
 *                  `size` including a NUL-termination.
 */
int snprintf(char* out, size_t size, const char* format, ...);


/**
 * Format an print a string into memory
 * 
 * @param   out     Location to print the string to
 * @param   size    The about of memory, in characters, allocated to `out`
 * @param   format  The format template to use
 * @param   args    Input data with which to fill the template
 * @return          Zero if and only if everything was printed, otherwise
 *                  the output was truncated with an utimate length of
 *                  `size` including a NUL-termination.
 */
int vasnprintf(char* out, size_t size, const char* format, va_list args);


#endif

