; Copyright © 2014  Mattias Andrée (m@maandree.se)
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


MBR equ 0x7C00			; BIOS have mapped the MBR for us.

;; BIOS have been nice enough to map some other things for us:
DRIVE_NUMBER         equ (MBR - 6)
SECTORS              equ (MBR - 8)
SECTORS_PER_CYLINDER equ (MBR - 12)

;; Some constants for readability
MBR_SIZE_BYTES equ 512
MBR_SIZE_WORDS equ (MBR_SIZE_BYTES / 2)


;; Macro for printing a message and halting.
%macro DIE 1
	mov si, %1		; Select message.
	jmp die			; and print it and then halt.
%endmacro


;; This is where we start.
bootsec:
	db 0x33, 0xC0		; For some reason this is common practice...
				; Like... really common. It has no effect...
				; (This is really `xor ax, ax`, so ax will be zero.)
	
	cli			; Disable interrupts.


;; Step 0: Relocate. (not working yet)

	;; 	mov di, bootsec
	;; 	mov cx, MBR_SIZE_WORDS
	;; 	rep movsw
	;; 	jmp word 0x0:vacate
	;; vacate:


;; Step 1: Find a bootable partition.
	
	mov ecx, (0 - 1)	; Start at first partition.
				; However, we do an increment at the beginning,
				; so we start at -1 rather than 0.
	mov ebx, -1		; Start state: no found partition.

next_partition:
	inc ecx			; Otherwise, check next partition.
	test ecx, 4		; There cannot be more than four primary/extended partitions.
 	jnz last_partition	; If we have check all...
	
	mov edx, ecx		; Calculates the partition entires position,
	imul edx, 16		; they are 16 byte long,
	add edx, 446		; and start 446. (Hopefully you see why it is
				; ludicrous to have this program 512 byte long.)
				; Their 8:th bit of their first byte specify
				; whether they are bootable.
	add edx, MBR		; Do not forget that MBR offset,
				; that is, where it is mapped in memory.
	
	mov edx, [edx]		; Read the first byte.
	and edx, 0x80		; And check the 8:th byte (boot flag.)
	jnz found_partition	; If the bit is set, we have found a partition.
	jmp next_partition	; Otherwise, check next.

found_partition:
	mov ebx, ecx		; Save found partition.
 	jmp next_partition	; Try the next one too, we want the last partition.
	;; Change this to `jmp last_partition` to load the first partition.

last_partition:
	cmp ebx, -1		; Check if we have found a bootable partition.
	jpe no_bootable		; If not, report it to the user.


;; Step 2: Locate that sucker. (not done)
	
	;;


;; Step 3: Boot the partition. (not done)
	
	mov dl, [DRIVE_NUMBER]	; Set the dl register to the device number.
	mov ax, 0		; Initialise segment registers to zero.
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	DIE MSG_OK


;; Your disc does not have have a bootable partition (that is not logical.)
no_bootable:
	DIE MSG_NO_BOOT		; Print error message and die.


;; Print message moved into `si` and halt.
die:
	mov ax, 0x07C0		; Needed for printing, I do not know why...
	mov ds, ax
	
	mov ah, 0x0E		; Enables printing.
.print_loop:
	lodsb			; Next byte (before the first print).
	cmp al, '.'		; Stop at (but include) a full stop.
	int 0x10		; Perform print.
	jne .print_loop		; Print next
	hlt			;  or halt.  ---  We could do `int 0x18` instead of halting.
	jmp ($ - 1)		; Rehalt forever.


;; Messages that can be printed.
MSG_NO_BOOT db "No bootable partition found."
MSG_OK db "OK."


; times 446 - ($ - $$) db 0	; Force the size of the file to be exactly
				; 446 bytes and no longer. Do not beleave
				; everything that you read on the Internet.
				; It should absolutely not be 512, that would
				; override the partition table, needer should
				; 0x55 0xAA be included, That is part the is
				; after the partition table.
;;  Currently disabled because it is nice to know how large our code is. ;;

