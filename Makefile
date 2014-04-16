OPTIMISE = -O3

WARN = -Wall -Wextra -pedantic -Wdouble-promotion -Wformat=2 -Winit-self       \
       -Wmissing-include-dirs -Wtrampolines -Wfloat-equal -Wshadow             \
       -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls           \
       -Wnested-externs -Winline -Wno-variadic-macros -Wsign-conversion        \
       -Wswitch-default -Wconversion -Wsync-nand -Wunsafe-loop-optimizations   \
       -Wcast-align -Wstrict-overflow -Wdeclaration-after-statement -Wundef    \
       -Wbad-function-cast -Wcast-qual -Wwrite-strings -Wlogical-op            \
       -Waggregate-return -Wstrict-prototypes -Wold-style-definition -Wpacked  \
       -Wvector-operation-performance -Wunsuffixed-float-constants             \
       -Wsuggest-attribute=const -Wsuggest-attribute=noreturn                  \
       -Wsuggest-attribute=pure -Wsuggest-attribute=format -Wnormalized=nfkc



.PHONY: all
all: bin/kernel


bin/kernel: link.ld obj/kernel_asm.o obj/kernel_c.o
	mkdir -p bin
	ld -m elf_i386 -o $@ -T $^ # link.ld must be first

obj/kernel_asm.o: src/kernel.asm
	mkdir -p obj
	nasm -f elf32 -o $@ $<

obj/kernel_c.o: src/kernel.c
	mkdir -p obj
	gcc $(OPTIMISE) $(WARN) -m32 -c -o $@ $<


.PHONY: qemu
qemu: bin/kernel
	qemu-system-i386 -kernel bin/kernel

.PHONY: clean
clean:
	-rm -r obj bin

