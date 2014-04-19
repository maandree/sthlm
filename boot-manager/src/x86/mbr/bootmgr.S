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

bits 16				; 16 bits (explicitly.)


;; Macro for printing a message and halting.
%macro DIE 1
	mov si, %1		; Select message.
	jmp die			; and print it and then halt.
%endmacro


;; This is where we start.
bootsec:
	db 0x33, 0xC0		; For some reason this is common practice...
				; Like... really common. It has no effect...

	cli			; Disable interrupts.

	mov ax, 0x07C0		; Needed for printing, I do not know why...
	mov ds, ax

	DIE MSG_HELLO_WORLD


;; Print message moved into `si` and halt.
die:
	mov ah, 0x0E		; Enables printing.
.print_loop:
	lodsb			; Next byte (before the first print).
	cmp al, '.'		; Stop at (but include) a full stop.
	int 0x10		; Perform print.
	jne .print_loop		; Print next
	hlt			;  or halt.


;; Messages that can be printed.
MSG_HELLO_WORLD db "Hello world."


; times 446 - ($ - $$) db 0	; Force the size of the file to be exactly
				; 446 bytes and no longer. Do not beleave
				; everything that you read on the Internet.
				; It should absolutely not be 512, that would
				; override the partition table, needer should
				; 0xAA55 be included, That is part the is
				; after the partition table.
;;  Currently disabled because it is nice to know how large our code is. ;;

