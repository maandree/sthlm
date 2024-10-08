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
#ifndef KERNEL_ARCH_KIO_H
#define KERNEL_ARCH_KIO_H


/**
 * Master programmable interrupt controller command port
 */
#define PIC_MASTER_COMMAND  0x20

/**
 * Master programmable interrupt controller data port
 */
#define PIC_MASTER_DATA     0x21

/**
 * Slave programmable interrupt controller command port
 */
#define PIC_SLAVE_COMMAND   0xA0

/**
 * Slave programmable interrupt controller data port
 */
#define PIC_SLAVE_DATA      0xA1


/**
 * Read byte from a port
 * 
 * @param   port  The port
 * @return        The read byte
 */
unsigned char portgetc(unsigned short port);

/**
 * Write byte to a port
 * 
 * @param  port  The port
 * @param  data  The byte to write to the port
 */
void portputc(unsigned short port, unsigned char data);


#endif

