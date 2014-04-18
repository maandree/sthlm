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
#include "timer.h"

#include "kio.h"
#include "irq.h"


/**
 * Our tick count
 */
static volatile uint_fast32_t timer_ticks = 0;
/* Volatile so that checking this variable
   is not optimised away. Which would be an
   incorrect optimisation. */



/**
 * Our tick counter tht is invoked when
 * the timer interrupts us
 * 
 * @param  regs  The registers
 */
static void timer_handler(registers_t* regs)
{
  (void) regs;
  
  timer_ticks++;
}


/**
 * Initialise the timer
 */
void timer_initialise(void)
{
  asm volatile("sti");
  irq(IRQ_TIMER, timer_handler);
}


/**
 * Set how often the timer ticks
 * 
 * @parma  hertz  The number of ticks per second
 */
void timer_phase(int hertz)
{
  int data = TIMER_PHASE_DIVIDEND / hertz;
  if (unlikely(data > 0xFFFF))
    data = 0xFFFF;
  portputc(BLACK_MAGIC(0x43), TIMER_PHASE_COMMAND);
  portputc(BLACK_MAGIC(0x40), (unsigned char)(data & 0xFF));
  portputc(BLACK_MAGIC(0x40), (unsigned char)(data >> 8));
}


/**
 * Wait a selected number of timer tick
 */
void timer_wait(uint_fast32_t ticks)
{
  uint_fast32_t cur_tick = timer_ticks;
  uint_fast32_t end_tick = cur_tick + ticks;
  
  /* Handle overflow at the 2147483648:th
     (slightly below 25 days at 1000 hz) tick! */
  if (unlikely(end_tick < cur_tick))
    while (timer_ticks >= cur_tick)
      relax();
  
  while (timer_ticks < end_tick)
    relax();
}

