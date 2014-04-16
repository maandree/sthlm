bits 32					; 32-bits

section .text
	; Multiboot specification: http://www.gnu.org/software/grub/manual/multiboot
	align 4
	dd 0x1BADB002			; magic number
	dd 0x00				; flags
	dd - (0x1BADB002 + 0x00)	; checksum

	global start
	extern kmain			; kmain is defined elsewhere

start:
	cli				; block interrupts
	call kmain			; call the kmain function
	hlt				; halt the CPU

