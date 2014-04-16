#include "ktty.h"


/**
 * The beginning of the memory where the output is written
 */
#define VIDEO_MEMORY  0xb8000


/**
 * How long an escape sequence can be before it is ridiculous
 */
#define ESCAPE_SEQUENCE_LIMIT  20



/**
 * The current position of the cursor, line
 */
static char cursor_y = 0;

/**
 * The current position of the cursor, column
 */
static char cursor_x = 0;



/**
 * Print string to the terminal, can include ANSI escape codes
 * 
 * @param  str  The string to print
 */
void kputs(const char* str)
{
  char* vidptr = (char*)VIDEO_MEMORY;
  char symbol;
  
  static int colour = 0x07;
  static int esc = 0;
  static char esc_buf[ESCAPE_SEQUENCE_LIMIT];
  static long esc_ptr = 0;

#define __colour_bit_swap(V) (((V) >> 2) | ((V) & 2) | (((V) & 1) << 2))
  
  for (; ((symbol = *str)); str++)
    if (esc == 1)
      esc = symbol == '[' ? 2 : 0;
    else if (esc == 2)
      if ((('0' > symbol) || (symbol > '9')) && (symbol != ';'))
	{
	  int entry = 0;
	  long i;
	  for (i = 0; i <= esc_ptr; i++)
	    if ((i == esc_ptr) || (esc_buf[i] == ';'))
	      {
		switch (symbol)
		  {
		  case 'm': /* That's colour! */
		    {
		      switch (entry)
			{
			case 0: /* Colour reset. */
			  colour = 0x08;
			  break;
			  
			case 38: /* Foreground reset. */
			  colour &= ~0x0F;
			  break;
			  
			case 48: /* Background reset. */
			  colour &= ~0xF0;
			  break;
			  
			case 30 ... 37: /* Dim foreground */
			  colour = (colour & ~0x0F) | (__colour_bit_swap(entry % 10) << 0) | 0x00;
			  break;
			  
			case 40 ... 47: /* Dim background */
			  colour = (colour & ~0xF0) | (__colour_bit_swap(entry % 10) << 4) | 0x00;
			  break;
			  
			case 90 ... 97: /* Brilliant foreground */
			  colour = (colour & ~0x0F) | (__colour_bit_swap(entry % 10) << 0) | 0x08;
			  break;
			  
			case 100 ... 107: /* Brilliant background */
			  colour = (colour & ~0xF0) | (__colour_bit_swap(entry % 10) << 4) | 0x80;
			  break;
			  
			default:
			  /* Not recognised, lets ignore it. */
			  break;
			}
		    }
		    break;
		    
		  case 'J': /* Clear everything after the cursor. */
		    {
		      long int j = cursor_y * KTTY_COLUMNS + cursor_x;
		      
		      for (; j < KTTY_COLUMNS * KTTY_LINES; j++)
			{
			  *(vidptr + 2 * j + 0) = ' ';
			  *(vidptr + 2 * j + 1) = (char)colour;
			}
		    }
		    
		  default:
		    /* Not recognised, lets ignore it. */
		    break;
		    }
		entry = 0;
	      }
	    else
	      entry = entry * 10 + (esc_buf[i] & 15);
	  esc = 0;
	  esc_ptr = 0;
	}
      else if (esc_ptr == sizeof(esc_buf) / sizeof(char))
	/* Attempt to overflow? Stop parsing! */
	esc = 0;
      else
	esc_buf[esc_ptr++] = symbol;
    else if (symbol == '\033')
      esc = 1;
    else
      {
	if ((symbol == '\n') || (cursor_x == KTTY_COLUMNS))
	  {
	    cursor_x = 0;
	    cursor_y++;
	  }
	if (cursor_y == KTTY_LINES)
	  {
	    /* Too far down, lets scroll the text one line up. */
	    long int i;
	    for (i = 0; i < 2 * KTTY_COLUMNS * (KTTY_LINES - 1); i++)
	      *(vidptr + i) = *(vidptr + i + 2 * KTTY_COLUMNS);
	    cursor_y--;
	    /* Clear the last line */
	    for (; i <  2 * KTTY_COLUMNS * KTTY_LINES; i += 2)
	      {
		*(vidptr + i + 0) = ' ';
		*(vidptr + i + 1) = (char)colour;
	      }
	  }
	if (symbol != '\n')
	  {
	    *(vidptr + (cursor_y * KTTY_COLUMNS + cursor_x) * 2 + 0) = symbol;
	    *(vidptr + (cursor_y * KTTY_COLUMNS + cursor_x) * 2 + 1) = (char)colour;
	    cursor_x++;
	  }
      }

#undef __colour_bit_swap
}

