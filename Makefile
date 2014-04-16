OPTIMISE = -O2

WARN = -Wall -Wextra -Wdouble-promotion -Wformat=2 -Winit-self                 \
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
# not using:  -pedantic

ASM_FLAGS = -f elf32

LD_FLAGS = -nodefaultlibs -nostdlib -m elf_i386

CPP_FLAGS = -D_KERNEL_

MACHINE = 32
STD = gnu99
C_FLAGS = $(OPTIMISE) $(WARN) -m$(MACHINE) -std=$(STD) -nostdlib -nodefaultlibs \
          -fno-omit-frame-pointer -ffreestanding -fstrict-aliasing -ftree-vrp   \
          -fipa-pure-const -fstack-usage -funsafe-loop-optimizations            \
          -fstrict-overflow -fno-builtin



OBJ = kernel_asm kernel_c ktty


.PHONY: all
all: bin/kernel


bin/kernel: link.ld $(foreach O,$(OBJ),obj/$(O).o) # link.ld must be first
	@mkdir -p bin
	ld $(LD_FLAGS) -o $@ -T $^

obj/kernel_asm.o: src/kernel.asm
	@mkdir -p obj
	nasm $(ASM_FLAGS) -o $@ $<

obj/kernel_c.o: src/kernel.c src/ktty.h
	@mkdir -p obj
	gcc $(C_FLAGS) $(CPP_FLAGS) -c -o $@ $<

obj/%.o: src/%.c src/%.h
	@mkdir -p obj
	gcc $(C_FLAGS) $(CPP_FLAGS) -c -o $@ $<


.PHONY: qemu
qemu: bin/kernel
	qemu-system-i386 -kernel bin/kernel

.PHONY: clean
clean:
	-rm -r obj bin

