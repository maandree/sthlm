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
  
  int entry_ = entry % 10;
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
      
    case 30 ... 37:
      /* Dim foreground */
      attribute_foreground = entry_colour | 0;
      break;
      
    case 40 ... 47:
      /* Dim background */
      attribute_background = entry_colour | 0;
      break;
      
    case 90 ... 97:
      /* Brilliant foreground */
      attribute_foreground = entry_colour | 8;
      break;
      
    case 100 ... 107:
      /* Brilliant background */
      attribute_background = entry_colour | 8;
      break;
      
    default:
      /* Not recognised, lets ignore it. */
      break;
    }
  
  /* Set colour. */
  colour = (attribute_background << 4) | attribute_foreground | (attribute_bold << 3);
}



/**
 * Print string to the terminal, can include ANSI escape codes
 * 
 * @param  str  The string to print
 */
void kputs(const char* str)
{
  char* vidptr = (char*)VIDEO_MEMORY;
  char symbol;
  
  static int esc = 0;
  static char esc_buf[ESCAPE_SEQUENCE_LIMIT];
  static long esc_ptr = 0;
  
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
			{
			  *(vidptr + 2 * j + 0) = ' ';
			  *(vidptr + 2 * j + 1) = (char)colour;
			}
		    }
		    break;
		    
		  case 'K':
		    /* Clear everything, or everything after the cursor, on the line. */
		    {
		      long int j = (entry == 2 ? 0 : cursor_x) + cursor_y * KTTY_COLUMNS;
		      
		      for (; j < (cursor_y + 1) * KTTY_COLUMNS; j++)
			{
			  *(vidptr + 2 * j + 0) = ' ';
			  *(vidptr + 2 * j + 1) = (char)colour;
			}
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
	    /* Too far down, lets scroll the text one line up. */
	    long int i;
	    for (i = 0; i < 2 * KTTY_COLUMNS * (KTTY_LINES - 1); i++)
	      *(vidptr + i) = *(vidptr + i + 2 * KTTY_COLUMNS);
	    cursor_y--;
	    /* Clear the last line. */
	    for (; i <  2 * KTTY_COLUMNS * KTTY_LINES; i += 2)
	      {
		*(vidptr + i + 0) = ' ';
		*(vidptr + i + 1) = (char)colour;
	      }
	  }
	if (symbol != '\n')
	  {
	    /* Print the symbol, unless new line. */
	    *(vidptr + (cursor_y * KTTY_COLUMNS + cursor_x) * 2 + 0) = symbol;
	    *(vidptr + (cursor_y * KTTY_COLUMNS + cursor_x) * 2 + 1) = (char)colour;
	    /* Move the cursor one step, line overlow is checked at next print. */
	    cursor_x++;
	  }
      }
}
