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
C_FLAGS = $(OPTIMISE) $(WARN) -m$(MACHINE) -std=$(STD) -nostdlib -nodefaultlibs  \
          -Isrc/libc -fno-omit-frame-pointer -ffreestanding -ftree-vrp           \
          -fstrict-aliasing -fipa-pure-const -fstack-usage -fstrict-overflow     \
          -funsafe-loop-optimizations -fno-builtin


NORMALS = ktty arch/ktty libc/stdlib arch/kio
OBJECTS = arch/kernel kernel $(NORMALS)
HEADERS = $(NORMALS) libc/stdint libc/inttypes libc/stddef arch/libc/stdint  \
          arch/libc/inttypes kio



.PHONY: all
all: bin/kernel


bin/kernel: link.ld $(foreach O,$(OBJECTS),obj/$(O).o) # link.ld must be first
	mkdir -p bin/$(shell echo $@ | cut -d / -f 1 --complement | xargs dirname)
	ld $(LD_FLAGS) -o $@ -T $^

obj/arch/kernel.o: src/arch/kernel.asm
	mkdir -p obj/$(shell echo $@ | cut -d / -f 1 --complement | xargs dirname)
	nasm $(ASM_FLAGS) -o $@ $<

obj/%.o: src/%.c $(foreach H,$(HEADERS),src/$(H).h)
	mkdir -p obj/$(shell echo $@ | cut -d / -f 1 --complement | xargs dirname)
	gcc $(C_FLAGS) $(CPP_FLAGS) -c -o $@ $<


.PHONY: qemu
qemu: bin/kernel
	qemu-system-i386 -kernel bin/kernel

.PHONY: clean
clean:
	-rm -r obj bin

