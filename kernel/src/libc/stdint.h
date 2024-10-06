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
#ifndef KERNEL_LIBC_STDINT_H
#define KERNEL_LIBC_STDINT_H


#include <arch/stdint.h>


#define INT8_BITS    8
#define INT16_BITS  16
#define INT32_BITS  32
#define INT64_BITS  64


/* Signed small integer types. */

typedef int8_t  int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

#define INT_LEAST8_BITS   INT8_BITS
#define INT_LEAST16_BITS  INT16_BITS
#define INT_LEAST32_BITS  INT32_BITS
#define INT_LEAST64_BITS  INT64_BITS


/* Unsigned small integer types. */

typedef uint8_t  uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

#define UINT_LEAST8_BITS   UINT8_BITS
#define UINT_LEAST16_BITS  UINT16_BITS
#define UINT_LEAST32_BITS  UINT32_BITS
#define UINT_LEAST64_BITS  UINT64_BITS


/* Possibly signed small integer types. */

typedef xint8_t  xint_least8_t;
typedef xint16_t xint_least16_t;
typedef xint32_t xint_least32_t;
typedef xint64_t xint_least64_t;

#define XINT_LEAST8_BITS   XINT8_BITS
#define XINT_LEAST16_BITS  XINT16_BITS
#define XINT_LEAST32_BITS  XINT32_BITS
#define XINT_LEAST64_BITS  XINT64_BITS


/* Boundaries of integrals. */

#define __singed_min(bits) \
  (-(1 << bits))

#define __singed_max(bits) \
  (-(1 - (1 << bits)))

#define __unsinged_max(bits) \
  ((1U << (bits - 1)) | ((1U << (bits - 1)) - 1U))


#define INT8_MIN   __singed_min(INT8_BITS)
#define INT16_MIN  __singed_min(INT16_BITS)
#define INT32_MIN  __singed_min(INT32_BITS)
#define INT64_MIN  (-__INT64_C(9223372036854775807) - 1)

#define INT8_MAX   __singed_max(INT8_BITS)
#define INT16_MAX  __singed_max(INT16_BITS)
#define INT32_MAX  __singed_max(INT32_BITS)
#define INT64_MAX  (__INT64_C(9223372036854775807))

#define UINT8_MAX   __unsinged_max(UINT8_BITS)
#define UINT16_MAX  __unsinged_max(UINT16_BITS)
#define UINT32_MAX  __unsinged_max(UINT32_BITS)
#define UINT64_MAX  (__UINT64_C(18446744073709551615)


#define INT_LEAST8_MIN   __singed_min(INT_LEAST8_BITS)
#define INT_LEAST16_MIN  __singed_min(INT_LEAST16_BITS)
#define INT_LEAST32_MIN  __singed_min(INT_LEAST32_BITS)
#define INT_LEAST64_MIN  

#define INT_LEAST8_MAX   __singed_max(INT_LEAST8_BITS)
#define INT_LEAST16_MAX  __singed_max(INT_LEAST16_BITS)
#define INT_LEAST32_MAX  __singed_max(INT_LEAST32_BITS)
#define INT_LEAST64_MAX  

#define UINT_LEAST8_MAX   __unsinged_max(UINT_LEAST8_BITS)
#define UINT_LEAST16_MAX  __unsinged_max(UINT_LEAST16_BITS)
#define UINT_LEAST32_MAX  __unsinged_max(UINT_LEAST32_BITS)
#define UINT_LEAST64_MAX  


#define INT_FAST8_MIN   __singed_min(INT_FAST8_BITS)
#define INT_FAST16_MIN  __singed_min(INT_FAST16_BITS)
#define INT_FAST32_MIN  __singed_min(INT_FAST32_BITS)
#define INT_FAST64_MIN  

#define INT_FAST8_MAX   __singed_max(INT_FAST8_BITS)
#define INT_FAST16_MAX  __singed_max(INT_FAST16_BITS)
#define INT_FAST32_MAX  __singed_max(INT_FAST32_BITS)
#define INT_FAST64_MAX  

#define UINT_FAST8_MAX   __unsinged_max(UINT_FAST8_BITS)
#define UINT_FAST16_MAX  __unsinged_max(UINT_FAST16_BITS)
#define UINT_FAST32_MAX  __unsinged_max(UINT_FAST32_BITS)
#define UINT_FAST64_MAX  


#if INTPTR_BITS <= 32
# define INTPTR_MIN   __singed_min(INTPTR_BITS)
# define INTPTR_MAX   __singed_max(INTPTR_BITS)
# define UINTPTR_MAX  __unsinged_max(UINTPTR_BITS)
#elif INTPTR_BITS == 64
# define INTPTR_MIN   INT64_MIN
# define INTPTR_MAX   INT64_MAX
# define UINTPTR_MAX  UINT64_MAX
#else
# error Integer with more than 32 bits, but not exactly 64 bits.
#endif


#if INTMAX_BITS <= 32
# define INTMAX_MIN   __singed_min(INTMAX_BITS)
# define INTMAX_MAX   __singed_max(INTMAX_BITS)
# define UINTMAX_MAX  __unsinged_max(UINTMAX_BITS)
#elif INTMAX_BITS == 64
# define INTMAX_MIN   INT64_MIN
# define INTMAX_MAX   INT64_MAX
# define UINTMAX_MAX  UINT64_MAX
#else
# error Integer with more than 32 bits, but not exactly 64 bits.
#endif


#undef __singed_min
#undef __singed_max
#undef __unsinged_max



#endif

