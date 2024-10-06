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
#ifndef KERNEL_LIBC_MACROS_H
#define KERNEL_LIBC_MACROS_H


/*
 * Common macros
 */


/**
 * The expression is likely to evaluate to `1`
 * 
 * This macro provides hits for the compiler
 * for optimisation of branching
 * 
 * @param   EXPRESSION:int  The expression
 * @return  :int            `EXPRESSION` is returned without any modifications
 */
#define likely(EXPRESSION)  __builtin_expect(EXPRESSION, 1)

/**
 * The expression is likely to evaluate to `0`
 * 
 * This macro provides hits for the compiler
 * for optimisation of branching
 * 
 * @param   EXPRESSION:int  The expression
 * @return  :int            `EXPRESSION` is returned without any modifications
 */
#define unlikely(EXPRESSION)  __builtin_expect(EXPRESSION, 0)


#endif

