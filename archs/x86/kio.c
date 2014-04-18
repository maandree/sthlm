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
#include "kio.h"


/**
 * Read byte from a port
 * 
 * @param   port  The port
 * @return        The read byte
 */
unsigned char portgetc(unsigned short port)
{
  unsigned char rc;
  asm volatile("inb %1, %0" : "=a" (rc) : "dN" (port));
  return rc;
}


/**
 * Write byte to a port
 * 
 * @param  port  The port
 * @param  data  The byte to write to the port
 */
void portputc(unsigned short port, unsigned char data)
{
  asm volatile("outb %1, %0" : : "dN" (port), "a" (data));
}

