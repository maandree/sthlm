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
#ifndef KERNEL_LIBC_INTTYPES_H
#define KERNEL_LIBC_INTTYPES_H


#include <stdint.h>
#include <arch/inttypes.h>


/* Printing with decimal notation. (Explicit) */

#define PRId8		__PRI8_PREFIX "d"
#define PRId16		__PRI16_PREFIX "d"
#define PRId32		__PRI32_PREFIX "d"
#define PRId64		__PRI64_PREFIX "d"

#define PRIdLEAST8	PRId8
#define PRIdLEAST16	PRId16
#define PRIdLEAST32	PRId32
#define PRIdLEAST64	PRId64

#define PRIdFAST8	__PRI_FAST8_PREFIX "d"
#define PRIdFAST16	__PRI_FAST16_PREFIX "d"
#define PRIdFAST32	__PRI_FAST32_PREFIX "d"
#define PRIdFAST64	__PRI_FAST64_PREFIX "d"


/* Printing with decimal notation. (Implicit) */

#define PRIi8		__PRI8_PREFIX "i"
#define PRIi16		__PRI16_PREFIX "i"
#define PRIi32		__PRI32_PREFIX "i"
#define PRIi64		__PRI64_PREFIX "i"

#define PRIiLEAST8	PRIi8
#define PRIiLEAST16	PRIi16
#define PRIiLEAST32	PRIi32
#define PRIiLEAST64	PRIi64

#define PRIiFAST8	__PRI_FAST8_PREFIX "i"
#define PRIiFAST16	__PRI_FAST16_PREFIX "i"
#define PRIiFAST32	__PRI_FAST32_PREFIX "i"
#define PRIiFAST64	__PRI_FAST64_PREFIX "i"


/* Printing with octal notation. */

#define PRIo8		__PRI8_PREFIX "o"
#define PRIo16		__PRI16_PREFIX "o"
#define PRIo32		__PRI32_PREFIX "o"
#define PRIo64		__PRI64_PREFIX "o"

#define PRIoLEAST8	PRIo8
#define PRIoLEAST16	PRIo16
#define PRIoLEAST32	PRIo32
#define PRIoLEAST64	PRIo64

#define PRIoFAST8	__PRI_FAST8_PREFIX "o"
#define PRIoFAST16	__PRI_FAST16_PREFIX "o"
#define PRIoFAST32	__PRI_FAST32_PREFIX "o"
#define PRIoFAST64	__PRI_FAST64_PREFIX "o"


/* Printing with unsigned decimal notation. */

#define PRIu8		__PRI8_PREFIX "u"
#define PRIu16		__PRI16_PREFIX "u"
#define PRIu32		__PRI32_PREFIX "u"
#define PRIu64		__PRI64_PREFIX "u"

#define PRIuLEAST8	PRIu8
#define PRIuLEAST16	PRIu16
#define PRIuLEAST32	PRIu32
#define PRIuLEAST64	PRIu64

#define PRIuFAST8	__PRI_FAST8_PREFIX "u"
#define PRIuFAST16	__PRI_FAST16_PREFIX "u"
#define PRIuFAST32	__PRI_FAST32_PREFIX "u"
#define PRIuFAST64	__PRI_FAST64_PREFIX "u"


/* Printing with lowercase hexadecimal notation. */

#define PRIx8		__PRI8_PREFIX "x"
#define PRIx16		__PRI16_PREFIX "x"
#define PRIx32		__PRI32_PREFIX "x"
#define PRIx64		__PRI64_PREFIX "x"

#define PRIxLEAST8	PRIx8
#define PRIxLEAST16	PRIx16
#define PRIxLEAST32	PRIx32
#define PRIxLEAST64	PRIx64

#define PRIxFAST8	__PRI_FAST8_PREFIX "x"
#define PRIxFAST16	__PRI_FAST16_PREFIX "x"
#define PRIxFAST32	__PRI_FAST32_PREFIX "x"
#define PRIxFAST64	__PRI_FAST64_PREFIX "x"


/* Printing with uppercase hexadecimal notation. */

#define PRIX8		__PRI8_PREFIX "X"
#define PRIX16		__PRI16_PREFIX "X"
#define PRIX32		__PRI32_PREFIX "X"
#define PRIX64		__PRI64_PREFIX "X"

#define PRIXLEAST8	PRIX8
#define PRIXLEAST16	PRIX16
#define PRIXLEAST32	PRIX32
#define PRIXLEAST64	PRIX64

#define PRIXFAST8	__PRI_FAST8_PREFIX "X"
#define PRIXFAST16	__PRI_FAST16_PREFIX "X"
#define PRIXFAST32	__PRI_FAST32_PREFIX "X"
#define PRIXFAST64	__PRI_FAST64_PREFIX "X"


/* Printing {{,u,x}{intmax,intptr},{,s}size,ptrdiff}_t. */

#define PRIdMAX		__PRIMAX_PREFIX "d"
#define PRIiMAX		__PRIMAX_PREFIX "i"
#define PRIoMAX		__PRIMAX_PREFIX "o"
#define PRIuMAX		__PRIMAX_PREFIX "u"
#define PRIxMAX		__PRIMAX_PREFIX "x"
#define PRIXMAX		__PRIMAX_PREFIX "X"

#define PRIdPTR		__PRIPTR_PREFIX "d"
#define PRIiPTR		__PRIPTR_PREFIX "i"
#define PRIoPTR		__PRIPTR_PREFIX "o"
#define PRIuPTR		__PRIPTR_PREFIX "u"
#define PRIxPTR		__PRIPTR_PREFIX "x"
#define PRIXPTR		__PRIPTR_PREFIX "X"

#define PRIdSIZE	__PRISIZE_PREFIX "d"
#define PRIiSIZE	__PRISIZE_PREFIX "i"
#define PRIoSIZE	__PRISIZE_PREFIX "o"
#define PRIuSIZE	__PRISIZE_PREFIX "u"
#define PRIxSIZE	__PRISIZE_PREFIX "x"
#define PRIXSIZE	__PRISIZE_PREFIX "X"

#define PRIdPTRDIFF	__PRIPTRDIFF_PREFIX "d"
#define PRIiPTRDIFF	__PRIPTRDIFF_PREFIX "i"
#define PRIoPTRDIFF	__PRIPTRDIFF_PREFIX "o"
#define PRIuPTRDIFF	__PRIPTRDIFF_PREFIX "u"
#define PRIxPTRDIFF	__PRIPTRDIFF_PREFIX "x"
#define PRIXPTRDIFF	__PRIPTRDIFF_PREFIX "X"



/* Scanning for decimal notation. (Explicit) */

#define SCNd8		__SCN8_PREFIX "d"
#define SCNd16		__SCN16_PREFIX "d"
#define SCNd32		__SCN32_PREFIX "d"
#define SCNd64		__SCN64_PREFIX "d"

#define SCNdLEAST8	SCNd8
#define SCNdLEAST16	SCNd16
#define SCNdLEAST32	SCNd32
#define SCNdLEAST64	SCNd64

#define SCNdFAST8	__SCN_FAST8_PREFIX "d"
#define SCNdFAST16	__SCN_FAST16_PREFIX "d"
#define SCNdFAST32	__SCN_FAST32_PREFIX "d"
#define SCNdFAST64	__SCN_FAST64_PREFIX "d"


/* Scanning for decimal notation. (Implicit) */

#define SCNi8		__SCN8_PREFIX "i"
#define SCNi16		__SCN16_PREFIX "i"
#define SCNi32		__SCN32_PREFIX "i"
#define SCNi64		__SCN64_PREFIX "i"

#define SCNiLEAST8	SCNi8
#define SCNiLEAST16	SCNi16
#define SCNiLEAST32	SCNi32
#define SCNiLEAST64	SCNi64

#define SCNiFAST8	__SCN_FAST8_PREFIX "i"
#define SCNiFAST16	__SCN_FAST16_PREFIX "i"
#define SCNiFAST32	__SCN_FAST32_PREFIX "i"
#define SCNiFAST64	__SCN_FAST64_PREFIX "i"


/* Scanning for octal notation. */

#define SCNo8		__SCN8_PREFIX "o"
#define SCNo16		__SCN16_PREFIX "o"
#define SCNo32		__SCN32_PREFIX "o"
#define SCNo64		__SCN64_PREFIX "o"

#define SCNoLEAST8	SCNo8
#define SCNoLEAST16	SCNo16
#define SCNoLEAST32	SCNo32
#define SCNoLEAST64	SCNo64

#define SCNoFAST8	__SCN_FAST8_PREFIX "o"
#define SCNoFAST16	__SCN_FAST16_PREFIX "o"
#define SCNoFAST32	__SCN_FAST32_PREFIX "o"
#define SCNoFAST64	__SCN_FAST64_PREFIX "o"


/* Scanning for unsigned decimal notation. */

#define SCNu8		__SCN8_PREFIX "u"
#define SCNu16		__SCN16_PREFIX "u"
#define SCNu32		__SCN32_PREFIX "u"
#define SCNu64		__SCN64_PREFIX "u"

#define SCNuLEAST8	SCNu8
#define SCNuLEAST16	SCNu16
#define SCNuLEAST32	SCNu32
#define SCNuLEAST64	SCNu64

#define SCNuFAST8	__SCN_FAST8_PREFIX "u"
#define SCNuFAST16	__SCN_FAST16_PREFIX "u"
#define SCNuFAST32	__SCN_FAST32_PREFIX "u"
#define SCNuFAST64	__SCN_FAST64_PREFIX "u"


/* Scanning for lowercase hexadecimal notation. */

#define SCNx8		__SCN8_PREFIX "x"
#define SCNx16		__SCN16_PREFIX "x"
#define SCNx32		__SCN32_PREFIX "x"
#define SCNx64		__SCN64_PREFIX "x"

#define SCNxLEAST8	SCNx8
#define SCNxLEAST16	SCNx16
#define SCNxLEAST32	SCNx32
#define SCNxLEAST64	SCNx64

#define SCNxFAST8	__SCN_FAST8_PREFIX "x"
#define SCNxFAST16	__SCN_FAST16_PREFIX "x"
#define SCNxFAST32	__SCN_FAST32_PREFIX "x"
#define SCNxFAST64	__SCN_FAST64_PREFIX "x"


/* Scanning for uppercase hexadecimal notation. */

#define SCNX8		__SCN8_PREFIX "X"
#define SCNX16		__SCN16_PREFIX "X"
#define SCNX32		__SCN32_PREFIX "X"
#define SCNX64		__SCN64_PREFIX "X"

#define SCNXLEAST8	SCNX8
#define SCNXLEAST16	SCNX16
#define SCNXLEAST32	SCNX32
#define SCNXLEAST64	SCNX64

#define SCNXFAST8	__SCN_FAST8_PREFIX "X"
#define SCNXFAST16	__SCN_FAST16_PREFIX "X"
#define SCNXFAST32	__SCN_FAST32_PREFIX "X"
#define SCNXFAST64	__SCN_FAST64_PREFIX "X"


/* Scanning for {{,u,x}{intmax,intptr},{,s}size,ptrdiff}_t. */

#define SCNdMAX		__SCNMAX_PREFIX "d"
#define SCNiMAX		__SCNMAX_PREFIX "i"
#define SCNoMAX		__SCNMAX_PREFIX "o"
#define SCNuMAX		__SCNMAX_PREFIX "u"
#define SCNxMAX		__SCNMAX_PREFIX "x"
#define SCNXMAX		__SCNMAX_PREFIX "X"

#define SCNdPTR		__SCNPTR_PREFIX "d"
#define SCNiPTR		__SCNPTR_PREFIX "i"
#define SCNoPTR		__SCNPTR_PREFIX "o"
#define SCNuPTR		__SCNPTR_PREFIX "u"
#define SCNxPTR		__SCNPTR_PREFIX "x"
#define SCNXPTR		__SCNPTR_PREFIX "X"

#define SCNdSIZE	__SCNSIZE_PREFIX "d"
#define SCNiSIZE	__SCNSIZE_PREFIX "i"
#define SCNoSIZE	__SCNSIZE_PREFIX "o"
#define SCNuSIZE	__SCNSIZE_PREFIX "u"
#define SCNxSIZE	__SCNSIZE_PREFIX "x"
#define SCNXSIZE	__SCNSIZE_PREFIX "X"

#define SCNdPTRDIFF	__SCNPTRDIFF_PREFIX "d"
#define SCNiPTRDIFF	__SCNPTRDIFF_PREFIX "i"
#define SCNoPTRDIFF	__SCNPTRDIFF_PREFIX "o"
#define SCNuPTRDIFF	__SCNPTRDIFF_PREFIX "u"
#define SCNxPTRDIFF	__SCNPTRDIFF_PREFIX "x"
#define SCNXPTRDIFF	__SCNPTRDIFF_PREFIX "X"


#endif

