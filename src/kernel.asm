bits 32					; 32-bits

	
section .text
	; Multiboot specification: http://www.gnu.org/software/grub/manual/multiboot
	align 4
	
	MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
	MULTIBOOT_HEADER_FLAGS	equ 0
	MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
	
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_CHECKSUM
	
	
	; Global functions
	global start
	
	; Functions defined in C code
	extern kmain


start:
	cli				; block interrupts
	call kmain			; call the kmain function
	hlt				; halt the CPU

