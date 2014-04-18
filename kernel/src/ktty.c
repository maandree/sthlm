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
#include "ktty.h"

#include <stdlib.h>



/**
 * How long an escape sequence can be before it is ridiculous
 */
#define ESCAPE_SEQUENCE_LIMIT  20


/**
 * The default boldness of printed text
 */
#define DEFAULT_BOLDNESS  0 /* Not bold by default. */

/**
 * The default background colour of printed text
 */
#define DEFAULT_BACKGROUND  0 /* Black. */

/**
 * The default foreground colour of printed text
 */
#define DEFAULT_FOREGROUND  7 /* Dim white. */


/**
 * Bit to set to make a colour brighter
 */
#define BRILLIANT  8



/**
 * The current position of the cursor, line
 */
static long cursor_y = 0;

/**
 * The current position of the cursor, column
 */
static long cursor_x = 0;

/**
 * The colour currently being used for printing
 */
static int colour = (DEFAULT_BACKGROUND << 4) | DEFAULT_FOREGROUND;



/**
 * Set a colour attribute
 * 
 * @param  entry  Colour attribute value
 */
static void set_colour(int entry)
{
  static int attribute_bold = DEFAULT_BOLDNESS;
  static int attribute_foreground = DEFAULT_FOREGROUND;
  static int attribute_background = DEFAULT_BACKGROUND;
  
  /* Extract colour value. */
  int entry_ = entry % 10;
  /* In ANSI, bit 1 is red, bit 2 is green and bit 3 is blue,
      but in the video memory, bit 1 is blue and bit 3 is red. */
  int entry_colour = (entry_ >> 2) | (entry_ & 2) | ((entry_ & 1) << 2);
  
  switch (entry)
    {
    case 0:
      /* Colour reset. */
      attribute_bold = DEFAULT_BOLDNESS;
      attribute_foreground = DEFAULT_FOREGROUND;
      attribute_background = DEFAULT_BACKGROUND;
      break;
      
    case 1:
      /* Bold. */
      attribute_bold = 1;
      break;
      
    case 21:
      /* Not bold. */
      attribute_bold = 0;
      break;
      
    case 38:
      /* Foreground reset. */
      attribute_foreground = DEFAULT_FOREGROUND;
      break;
      
    case 48:
      /* Background reset. */
      attribute_background = DEFAULT_BACKGROUND;
      break;

# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wpedantic"
      
    case 30 ... 37:
      /* Dim foreground */
      attribute_foreground = entry_colour;
      break;
      
    case 40 ... 47:
      /* Dim background */
      attribute_background = entry_colour;
      break;
      
    case 90 ... 97:
      /* Brilliant foreground */
      attribute_foreground = entry_colour | BRILLIANT;
      break;
      
    case 100 ... 107:
      /* Brilliant background */
      attribute_background = entry_colour | BRILLIANT;
      break;

# pragma GCC diagnostic pop
      
    default:
      /* Not recognised, lets ignore it. */
      break;
    }
  
  /* Set colour. */
  colour = (attribute_background << 4) | attribute_foreground | (attribute_bold << 3);
}


/**
 * Print string to the terminal, may include ANSI escape codes
 * 
 * @param  str  The string to print
 */
void kputs(const char* str)
{
  static int esc = 0;
  static char esc_buf[ESCAPE_SEQUENCE_LIMIT];
  static long esc_ptr = 0;
  
  char symbol;
  
  for (; ((symbol = *str)); str++)
    if (esc == 1)
      /* We expect it to be an CSI. */
      esc = symbol == '[' ? 2 : 0;
    else if (esc == 2)
      if ((('0' > symbol) || (symbol > '9')) && (symbol != ';'))
	{
	  int entry = 0;
	  long i;
	  for (i = 0; i <= esc_ptr; i++)
	    if ((i == esc_ptr) || (esc_buf[i] == ';'))
	      {
		/* End of attribute, possibly the last attribute. */
		switch (symbol)
		  {
		  case 'm':
		    /* That's colour! */
		    set_colour(entry);
		    break;
		    
		  case 'J':
		    /* Clear everything or everything after the cursor, on the display. */
		    {
		      long int j = entry == 2 ? 0 : cursor_y * KTTY_COLUMNS + cursor_x;
		      
		      for (; j < KTTY_COLUMNS * KTTY_LINES; j++)
			kputc(' ', (char)colour, 0 /* set by x */, j);
		    }
		    break;
		    
		  case 'K':
		    /* Clear everything, or everything after the cursor, on the line. */
		    {
		      long int j = (entry == 2 ? 0 : cursor_x) + cursor_y * KTTY_COLUMNS;
		      
		      for (; j < (cursor_y + 1) * KTTY_COLUMNS; j++)
			kputc(' ', (char)colour, 0 /* set by x */, j);
		    }
		    break;
		    
		  case 'H':
		    /* Jump home. */
		    if (cursor_y >= 0)
		      {
			/* On first parameter. */
			cursor_y = ~(entry == 0 ? 0 : (entry - 1));
			cursor_x = 0;
		      }
		    else
		      /* On second (or any later) parameter. */
		      cursor_x = entry == 0 ? 0 : (entry - 1);
		    break;
		    
		  default:
		    /* Not recognised, lets ignore it. */
		    break;
		  }
		/* Reset integer parser. */
		entry = 0;
	      }
	    else
	      /* Parse digit. */
	      entry = entry * 10 + (esc_buf[i] & 15);
	  /* For H (jump home): */
	  cursor_y = cursor_y < 0 ? ~cursor_y : cursor_y;
	  /* Reset escape reading. */
	  esc = 0;
	  esc_ptr = 0;
	}
      else if (esc_ptr == sizeof(esc_buf) / sizeof(char))
	/* Attempt to overflow? Stop parsing! */
	esc = 0;
      else
	/* Store symbol to be parsed as a part of a text attribute. */
	esc_buf[esc_ptr++] = symbol;
    else if (symbol == '\033')
      /* Beginning awesome magic. */
      esc = 1;
    else
      {
	if ((symbol == '\n') || (cursor_x == KTTY_COLUMNS))
	  {
	    /* Line overflow or new line requested. */
	    cursor_x = 0;
	    cursor_y++;
	  }
	if (cursor_y == KTTY_LINES)
	  {
	    long int i = KTTY_COLUMNS * (KTTY_LINES - 1);
	    /* Too far down, lets scroll the text one line up. */
	    kttymove(0, 0, 1, 0, KTTY_COLUMNS);
	    cursor_y--;
	    /* Clear the last line. */
	    for (; i < KTTY_COLUMNS * KTTY_LINES; i++)
	      kputc(' ', (char)colour, 0 /* set by x */, i);
	  }
	if (symbol != '\n')
	  {
	    /* Print the symbol, unless new line. */
	    kputc(symbol, (char)colour, cursor_y, cursor_x);
	    /* Move the cursor one step, line overlow is checked at next print. */
	    cursor_x++;
	  }
      }
}


/**
 * Format an print a string into the terminal
 * 
 * @param   format  The format template to use
 * @param   ...     Input data to fill the template with
 * @return          Zero if and only if everything was printed, otherwise
 *                  the output was truncated with an utimate length of `size`
 */
int kprintf(const char* format, ...)
{
  int rc;
  va_list args;
  va_start(args, format);
  rc = kvaprintf(format, args);
  va_end(args);
  return rc;
}


/**
 * Format an print a string into the terminal
 * 
 * @param   format  The format template to use
 * @param   args    Input data to fill the template with
 * @return          Zero if and only if everything was printed, otherwise
 *                  the output was truncated with an utimate length of `size`
 */
int kvaprintf(const char* format, va_list args)
{
  int rc;
  char buffer[KPRINT_BUFFER_SIZE + 1];
  rc = vasnprintf(buffer, KPRINT_BUFFER_SIZE + 1, format, args);
  kputs(buffer);
  return rc;
}

