; Copyright © 2014  Mattias Andrée (maandree@member.fsf.org)
; 
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.

bits 32					; 32-bit machine.
align 4					; Align instructions.


section .text
	; Multiboot specification: http://www.gnu.org/software/grub/manual/multiboot
	
	MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
	MULTIBOOT_HEADER_FLAGS	equ 0
	MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
	
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_CHECKSUM
	
	
	; Global functions.
	global start
	
	; Functions defined in C code.
	extern kmane


start:
	cli				; Block interrupts.
	call kmane			; Call the kmane function.
	hlt				; Halt the CPU.


section .bss
	resb (8 << 10)			; 8 kB of memory reserved.

