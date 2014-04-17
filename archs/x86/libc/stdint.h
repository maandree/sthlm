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
#ifndef KERNEL_LIBC_ARCH_STDINT_H
#define KERNEL_LIBC_ARCH_STDINT_H


#define ___define(SIGN, PREFIX, INT8, INT16, INT32, INT64)	\
  typedef SIGN INT8   PREFIX ## 8_t;				\
  typedef SIGN INT16  PREFIX ## 16_t;				\
  typedef SIGN INT32  PREFIX ## 32_t;				\
  typedef SIGN INT64  PREFIX ## 64_t;

#define __define(INFIX, INT8, INT16, INT32, INT64)		\
  ___define(signed,          INFIX, INT8, INT16, INT32, INT64)	\
  ___define(unsigned,   u ## INFIX, INT8, INT16, INT32, INT64)	\
  ___define(/* omit */, x ## INFIX, INT8, INT16, INT32, INT64)



/* Exact size integrals. */

__define(int, char,
	      short int,
	      long int,
	      long long int)


/* Fast size integrals. */

__define(int_fast, char,
		   long int,
		   long int,
		   long long int)

#define INT_FAST8_BITS    8
#define INT_FAST16_BITS  32
#define INT_FAST32_BITS  32
#define INT_FAST64_BITS  64

#define UINT_FAST8_BITS    8
#define UINT_FAST16_BITS  32
#define UINT_FAST32_BITS  32
#define UINT_FAST64_BITS  64

#define XINT_FAST8_BITS    8
#define XINT_FAST16_BITS  32
#define XINT_FAST32_BITS  32
#define XINT_FAST64_BITS  64


/* Integrals large enough to hold pointers. */

typedef signed   long int   intptr_t;
typedef unsigned long int  uintptr_t;
typedef          long int  xintptr_t;

#define INTPTR_BITS   32
#define UINTPTR_BITS  INTPTR_BITS
#define XINTPTR_BITS  INTPTR_BITS


/* Largest integral types. */

typedef signed   long long int   intmax_t;
typedef unsigned long long int  uintmax_t;
typedef          long long int  xintmax_t;

#define INTMAX_BITS   64
#define UINTMAX_BITS  INTMAX_BITS
#define XINTMAX_BITS  INTMAX_BITS


#undef __define
#undef ___define


/* Limits of size_t, ssize_t and ptrdiff_t.  */

#define SIZE_MAX   (4294967295U)
#define SIZE_BITS  32

#define SSIZE_MAX   (2147483647)
#define SSIZE_BITS  32

#define PTRDIFF_MAX   (2147483647)
#define PTRDIFF_BITS  32


/* Integral literal makers. */

#define __INT8_C(V)	V
#define __UINT8_C(V)	V

#define __INT16_C(V)	V
#define __UINT16_C(V)	V

#define __INT32_C(V)	V
#define __UINT32_C(V)	V ## U

#define __INT64_C(V)	V ## LL
#define __UINT64_C(V)	V ## ULL

#define __INTMAX_C(V)	V ## LL
#define __UINTMAX_C(V)	V ## ULL


#endif

