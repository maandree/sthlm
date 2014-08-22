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
#ifndef KERNEL_ARCH_IDT_H
#define KERNEL_ARCH_IDT_H


#include "../system.h"

#include <stdint.h>


/**
 * The number of IDT gates on the system
 */
#define IDT_COUNT  256


/**
 * IDT handler function type
 */
typedef void idt_handler_t(registers_t* regs);


# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wpacked"
/* Pack it explicitly despite the compiler saying it is
   not unnecessary (already packed). It most be packed. */

/**
 * IDT gate entry
 */
typedef struct idt_entry
{
  /**
   * The lower half of the address to the handler
   */
  unsigned short int handler_low;
  unsigned short int select;
  
  /**
   * Set to me zero
   */
  unsigned char zero;
  unsigned char flags;
  
  /**
   * The upper half of the address to the handler
   */
  unsigned short int handler_high;
  
} __attribute__((packed)) idt_entry_t;

# pragma GCC diagnostic pop

 
/**
 * Selected IDT gate
 */
typedef struct idt_ptr
{
  /**
   * TODO: what is this?
   */
  unsigned short int limit;
  
  /**
   * Address to the handler
   */
  uintptr_t handler;
  
} __attribute__((packed)) idt_ptr_t;


/**
 * Initialises IDT support
 */
void idt_initialise(void);

/**
 * Set an interrupt descriptor gate
 * 
 * @param  index    The IDT index
 * @param  handler  The interrupt handler
 * @param  select   TODO: what is this?
 * @param  flags    TODO: what is this?
 *                  (When either is answered, add to .c file and
 *                   struct idt_entry.)
 */
void idt_set_gate(unsigned char index, idt_handler_t* handler,
		  unsigned short int select, unsigned char flags);

/**
 * Load selected interrupt descriptor
 */
extern void idt_load(void);


#endif

