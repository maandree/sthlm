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
#include "ktty.h"
#include "timer.h"


/*
 * The module is responsible for the process flow of the kernel.
 * arch/kernel.S is however the canonical starting point of the
 * kernel's process flow.
 */


/**
 * This is the entry point of the kernel,
 * although there is actually stuff in
 * arch/kernel.asm that starts before this
 * and calls this.
 */
void kmane(void) __attribute__((noreturn));
void kmane(void)
{
  int i;
  kprintf("%[1;34;44m%s%[;30;40m%[J", "Kernels are magic");
  /* By using 30;40 (black on black) we are hiding the cursor. */
  
  timer_initialise();
  timer_phase(1000);
  
  for (i = 0;; i++)
    {
      timer_wait(1000);
      kprintf("%[H%[1;34;44m%i%[;30;40m%[K", i);
    }
}

