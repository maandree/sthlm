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
#ifndef KERNEL_ARCH_TIMER_H
#define KERNEL_ARCH_TIMER_H


#include "../system.h"


/**
 * The programmable interrupt timer interrupt IRQ number
 */
#define IRQ_TIMER  0

/**
 * Command number to send timer tick frequency
 */
#define TIMER_PHASE_COMMAND  0x36

/**
 * Dividend for data to set timer tick frequency
 */
#define TIMER_PHASE_DIVIDEND  0x36


/**
 * Initialise the timer
 */
void timer_initialise(void);

/**
 * Set how often the timer ticks
 * 
 * @parma  hertz  The number of ticks per second
 */
void timer_phase(int hertz);

/**
 * Wait a selected number of timer tick
 */
void timer_wait(int ticks);


#endif

