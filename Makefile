# Copyright © 2014  Mattias Andrée (maandree@member.fsf.org)
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


# The architecture to compile the kernel with.
KARCH ?= x86


# Programs to use.
CC ?= gcc
LD ?= ld
ASM ?= nasm
RM ?= rm
RM_R ?= $(RM) -r
MKDIR ?= mkdir
MKDIR_P ?= $(MKDIR) -p
ECHO ?= /bin/echo
ECHO_E ?= $(ECHO) -e
TOUCH ?= touch
LN ?= ln
LN_S ?= ln -s
FALSE ?= false
MAKE ?= make
SH ?= sh
XARGS ?= xargs
DIRNAME ?= dirname
CUT ?= cut
# `cut` must support --complement


# Output format for the directly used assembler.
ifeq ($(ASM_FORMAT),)
ifeq ($(KARCH),x86)
ASM_FORMAT = elf32
endif
endif

# Output format for the linker.
ifeq ($(LD_FORMAT),)
ifeq ($(KARCH),x86)
LD_FORMAT = elf_i386
endif
endif

# Architecture for the C compiler.
ifeq ($(MACHINE),)
ifeq ($(KARCH),x86)
MACHINE = 32
endif
endif


# Optimisation level (and debug flags.)
# TODO -O3 translates code segments into function calls, but why?
OPTIMISE = -O2

# Enabled Warnings.
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

# The C standard used in the code.
STD = gnu99


# Options for the assembler when compiling assembly directly.
ASM_FLAGS = -f$(ASM_FORMAT)

# Options for the linker.
LD_FLAGS = -nodefaultlibs -nostdlib -m$(LD_FORMAT)

# Options for the C preprocessor.
# We define _KERNEL_ for good practive.
CPP_FLAGS = -D_KERNEL_

# Options for the C compiler.
C_FLAGS = $(OPTIMISE) $(WARN) -m$(MACHINE) -std=$(STD) -nostdlib -nodefaultlibs  \
          -Isrc/libc -fno-omit-frame-pointer -ffreestanding -ftree-vrp           \
          -fstrict-aliasing -fipa-pure-const -fstack-usage -fstrict-overflow     \
          -funsafe-loop-optimizations -fno-builtin


# Objects that have both headers and source.
NORMALS = ktty arch/ktty libc/stdlib arch/kio

# Object that have (perhaps only) source.
OBJECTS = arch/kernel kernel $(NORMALS)

# C header files.
HEADERS = $(NORMALS) libc/stdint libc/inttypes libc/stddef arch/libc/stdint  \
          arch/libc/inttypes kio


# Architecture for QEMU.
ifeq ($(QEMU_ARCH),)
ifeq ($(KARCH),x86)
QEMU_ARCH = i386
endif
endif

# Flags for QEMU.
QEMU_RAM ?= 512
QEMU_CPU ?= host
QEMU_CPUS ?= 1
QEMU_MACHINE ?= type=pc,accel=kvm
# QEMU_FLAGS ?= -m $(QEMU_RAM) -machine $(QEMU_MACHINE) -cpu $(QEMU_CPU) -smp $(QEMU_CPUS) -sdl
# Not needed at the moment, just slows down the initialisation of QEMU



# Build everything.
.PHONY: all
all: _makeflags
	@$(ECHO_E) -e "\e[01;34m$@\e[21m: $^\e[00m"
	$(MAKE) src/arch
	$(MAKE) bin/kernel


# Rebuild when flags are changed.
_MAKEFLAGS_GROUPS = ASM_FLAGS LD_FLAGS CPP_FLAGS C_FLAGS
_MAKEFLAGS = $(foreach G,$(_MAKEFLAGS_GROUPS),$(foreach F,$($(G)),$(G)=$(subst /,\\,$(F))))
.PHONY: _makeflags
_makeflags:
	@if $(foreach F,$(_MAKEFLAGS),[ ! -e .flags/$(F) ] ||) $(FALSE); then $(MAKE) _makeflags_; fi
.PHONY: _makeflags_
_makeflags_:
	@$(MAKE) clean
	@$(MKDIR_P) .flags
	@$(TOUCH) $(foreach F,$(_MAKEFLAGS),.flags/$(F))


# Select architecture.
src/arch:
	@$(ECHO_E) "\e[01;34m$@\e[21m: $^\e[00m"
	-$(RM) $@
	$(LN_S) "../archs/$(KARCH)" $@


# Link everything together to a usable kernel image.
bin/kernel: link.ld $(foreach O,$(OBJECTS),obj/$(O).o) # $link.ld must be first
	@$(ECHO_E) "\e[01;34m$@\e[21m: $^\e[00m"
	$(MKDIR_P) -p bin/$(shell echo $@ | $(CUT) -d / -f 1 --complement | $(XARGS) $(DIRNAME))
	$(LD) $(LD_FLAGS) -o $@ -T $^

# Compile an assembly file.
obj/%.o: src/%.asm
	@$(ECHO_E) "\e[01;34m$@\e[21m: $^\e[00m"
	$(MKDIR_P) -p obj/$(shell echo $@ | $(CUT) -d / -f 1 --complement | $(XARGS) $(DIRNAME))
	$(ASM) $(ASM_FLAGS) -o $@ $<

# Compile a C file, recompile all (for simplicity) if a header is modified.
obj/%.o: src/%.c $(foreach H,$(HEADERS),src/$(H).h)
	@$(ECHO_E) "\e[01;34m$@\e[21m: $^\e[00m"
	$(MKDIR_P) -p obj/$(shell echo $@ | $(CUT) -d / -f 1 --complement | $(XARGS) $(DIRNAME))
	$(CC) $(C_FLAGS) $(CPP_FLAGS) -c -o $@ $<



# Test kernel image using QEMU.
.PHONY: qemu
qemu: bin/kernel
	@$(ECHO_E) "\e[01;32m$@\e[21m: $^\e[00m"
	qemu-system-$(QEMU_ARCH) $(QEMU_FLAGS) -kernel $<


# Clean the directory from compiled files.
.PHONY: clean
clean:
	@$(ECHO_E) "\e[01;33m$@\e[21m: $^\e[00m"
	-$(RM_R) obj bin .flags
	-$(RM) src/arch

