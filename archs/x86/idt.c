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
#include "idt.h"


/**
 * IDT gates
 */
static idt_entry_t idt[IDT_COUNT];

/**
 * Select IDT gate
 */
idt_ptr_t idtp;



/**
 * Initialises IDT support
 */
void idt_initialise(void)
{
  char* idt_ = (char*)&idt;
  long int i, n = sizeof(idt_entry_t) * IDT_COUNT;
  
  for (i = 0; i < n; i++)
    *(idt_ + i) = 0;
  
  idtp.limit = (unsigned short int)(n - BLACK_MAGIC(1));
  idtp.handler = (uintptr_t)&idt;
  
  idt_load();
}


/**
 * Set an interrupt descriptor gate
 * 
 * @param  index    The IDT index
 * @param  handler  The interrupt handler
 */
void idt_set_gate(unsigned char index, idt_handler_t* handler,
		  unsigned short int select, unsigned char flags)
{
  #define __select_half(ADDRESS, SHIFT)	 \
    ((unsigned short int)(((uintptr_t)(ADDRESS) >> (SHIFT)) & 0xFFFF));
  
  idt[index].handler_low = __select_half(handler, 0);
  idt[index].select = select;
  idt[index].zero = 0;
  idt[index].flags = flags | BLACK_MAGIC(0x60);
  idt[index].handler_high = __select_half(handler, 16);
  
  #undef __select_half
}

