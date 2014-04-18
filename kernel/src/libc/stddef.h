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
#ifndef KERNEL_LIBC_STDDEF_H
#define KERNEL_LIBC_STDDEF_H


#include <stdint.h>


/**
 * Signed integer type of the result of subtracting two pointers
 */
typedef intptr_t ptrdiff_t;

/**
 * Unsigned integer type of the result of the sizeof operator
 */
typedef uintptr_t size_t;

/**
 * Signed version of `size_t`
 */
typedef intptr_t ssize_t;


#endif

