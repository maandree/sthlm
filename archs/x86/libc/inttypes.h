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
#ifndef KERNEL_LIBC_ARCH_INTTYPES_H
#define KERNEL_LIBC_ARCH_INTTYPES_H


#include <arch/stdint.h>


/* Printing prefixes. */

#define __PRI8_PREFIX
#define __PRI16_PREFIX
#define __PRI32_PREFIX
#define __PRI64_PREFIX       "ll"
#define __PRIMAX_PREFIX      __PRI64_PREFIX
#define __PRIPTR_PREFIX      __PRI32_PREFIX
#define __PRISIZE_PREFIX     __PRIPTR_PREFIX
#define __PRIPTRDIFF_PREFIX  __PRISIZE_PREFIX
#define __PRI_FAST8_PREFIX   __PRI8_PREFIX
#define __PRI_FAST16_PREFIX  __PRIPTR_PREFIX
#define __PRI_FAST32_PREFIX  __PRIPTR_PREFIX
#define __PRI_FAST64_PREFIX  __PRI64_PREFIX


/* Scanning prefixes. */

#define __SCN8_PREFIX        "hh"
#define __SCN16_PREFIX       "h"
#define __SCN32_PREFIX
#define __SCN64_PREFIX	     "ll"
#define __SCNMAX_PREFIX      __SCN64_PREFIX
#define __SCNPTR_PREFIX      __SCN32_PREFIX
#define __SCNSIZE_PREFIX     __SCNPTR_PREFIX
#define __SCNPTRDIFF_PREFIX  __SCNSIZE_PREFIX
#define __SCN_FAST8_PREFIX   __SCN8_PREFIX
#define __SCN_FAST16_PREFIX  __SCNPTR_PREFIX
#define __SCN_FAST32_PREFIX  __SCNPTR_PREFIX
#define __SCN_FAST64_PREFIX  __SCN64_PREFIX


#endif

