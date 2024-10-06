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
#include "stdlib.h"

#include <macros.h>


/**
 * Convert an unsigned integer to a string
 * 
 * @param   buffer  Buffer that may be used and return
 * @param   size    The usable size of the buffer
 * @param   value   The value to convert
 * @return          The value as a string
 */
static const char* utostr(char* buffer, size_t size, unsigned int value)
{
  char digits[3 * sizeof(unsigned int)];
  /* Hack for calculating the max length of the string. */
  
  unsigned int digit;
  size_t i, max, off;
  
  /* Calculate digits in reverse order. */
  for (max = 1;; max++) /* Starting at 1 for simplicity. */
    {
      /* Calculate digit and remove it. */
      digit = value % 10;
      value = value / 10;
      
      /* Store the digit in a buffer. */
      digits[3 * sizeof(unsigned int) - max] = (char)('0' + digit);
      
      /* We have zero real digits left, or the buffer is too small, stop. */
      if ((value == 0) || (max == size))
	break;
    }
  
  /* Copy the bufferd data to the output buffer,
     this done instead of writing directly to the
     output buffer in case the buffer is too small. */
  off = 3 * sizeof(unsigned int) - max;
  for (i = 0; i < max; i++)
    *(buffer + i) = digits[off + i];
  
  /* NUL-terminate buffer. */
  *(buffer + max) = '\0';
  
  return (const char*)buffer;
}


/**
 * Convert a signed integer to a string
 * 
 * @param   buffer  Buffer that may be used and return
 * @param   size    The usable size of the buffer
 * @param   value   The value to convert
 * @return          The value as a string
 */
static const char* itostr(char* buffer, size_t size, signed int value)
{
  /* Use `utostr` to convert any non-negative integer,
     it is possible because all non-negative signed integers
     fits in unsigned integers. */
  if (likely(value >= 0))
    return utostr(buffer, size, (unsigned int)value);
  
  /* Use `utostr` to convert to string, this preferable because
     it means we do not have the care about the case where `-value`
     is still negative, that is when `value == INT_MIN`. */
  *buffer = '-';
  utostr(buffer + 1, size - 1, (unsigned int)-value);
  return (const char*)buffer;
}


/**
 * Format an print a string into memory
 * 
 * @param   out     Location to print the string to
 * @param   size    The about of memory, in characters, allocated to `out`
 * @param   format  The format template to use
 * @parma   ...     Input data with which to fill the template
 * @return          Zero if and only if everything was printed, otherwise
 *                  the output was truncated with an utimate length of
 *                  `size` including a NUL-termination.
 */
int snprintf(char* out, size_t size, const char* format, ...)
{
  int rc;
  va_list args;
  va_start(args, format);
  rc = vasnprintf(out, size, format, args);
  va_end(args);
  return rc;
}


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
int vasnprintf(char* out, size_t size, const char* format, va_list args)
{
  const char* print_this = NULL;
  size_t out_skip = 0;
  char* out_end = out + (size - 1);
  char symbol;

# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wpedantic"
  /**
   * Print a symbol to the the buffer
   * 
   * @param   c  The symbol to print
   * @return     Zero if and only if the symbol could be printed
   */
  inline int vasnprintf_(int c)
  {
# pragma GCC diagnostic pop
    if (out_skip > 0)
      /* Skipping some printing. */
      out_skip--;
    else if (unlikely(out == out_end))
      {
	/* We have no space for anything more. */
	*out = '\0';
	return 1;
      }
    else
      /* Doing some printing. */
      *out++ = (char)c;
    return 0;
  }
  
  
  /* Print string. */
  for (;;)
    {
      /* Get next symbol or symbol from template. */
      if (unlikely(print_this == NULL))
	{
	  /* Normal printing, from template. */
	  if (unlikely((symbol = *format++) == '\0'))
	    /* End of template. */
	    break;
	}
      else
	/* Printing from string spitt out from the template. */
	if (unlikely((symbol = *print_this++) == '\0'))
	  {
	    /* End of the temporary string, return to template. */
	    print_this = NULL;
	    continue;
	  }
      
      /* Parse symbol. */
      if ((unlikely(symbol == '%')) && (print_this == NULL))
	{
	  /* Parse escape if not in temporary string. */
	  symbol = *format++;
	  if (symbol == '\0')
	    /* Format error, at end of string, stop and ignore the unfinished escape. */
	    break;
	  
	  /* Parse escape. */
	  switch (symbol)
	    {
	    case '%':
	      /* We have an escaped escape symbol. */
	      print_this = "%";
	      break;
	      
	    case 'e':
	      /* Compiler/standard agnostic alternative to \e for \033 .*/
	      print_this = "\033";
	      break;
	      
	    case '[':
	      /* CSI shorthand. */
	      print_this = "\033[";
	      break;
	      
	    case 's':
	      /* Print a string. */
	      print_this = va_arg(args, const char*);
	      break;
	      
	    case 'c':
	      /* Print a string single character. */
	      if (unlikely(vasnprintf_((char)va_arg(args, int /* (!) */))))
		return 1;
	      break;
	      
	    case 'i':
	    case 'd':
	      /* Print a signed integer. */
	      print_this = itostr(out, (size_t)(out_end - out), va_arg(args, signed int));
	      break;
	      
	    case 'u':
	      /* Print an unsigned integer. */
	      print_this = utostr(out, (size_t)(out_end - out), va_arg(args, unsigned int));
	      break;
	      
	    default:
	      /* Invalue format, notify the programmer. */
	      print_this = "{{ENCOUNTERED INVALID SYMBOL}}";
	      break;
	    }
	}
      else
	/* Just a number symbol, nothing special. */
	if (unlikely(vasnprintf_(symbol)))
	  return 1;
    }
  
  /* We did not have to truncate. */
  *out = '\0';
  return 0;
}

