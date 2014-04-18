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



static volatile int timer_ticks = 0;


static void timer_handler(registers_t* regs)
{
  (void) regs;
  
  timer_ticks++;
}


void timer_phase(int hertz)
{
  int divisor = 1193180 / hertz;
  portputc(0x43, 0x36);
  portputc(0x40, (unsigned char)(divisor & 0xFF));
  portputc(0x40, (unsigned char)(divisor >> 8));
}


void timer_initialise(void)
{
  asm volatile("sti");
  irq(0, timer_handler);
}


# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wsuggest-attribute=const"
# pragma GCC diagnostic ignored "-Wsuggest-attribute=pure"
/* Calls to function must never be optimised away.  */

void timer_wait(int ticks)
{
  int end_tick = timer_ticks + ticks;
  while (timer_ticks < end_tick)
    ; /* TODO: How do we relax the CPU? */
}

# pragma GCC diagnostic pop

