OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
   . = 0x100000;
   .text : { *(.text) }
   .data : { *(.data) }
   .bss  : { *(.bss)  }

   /* End of the kernel */
   end = .;

   /* Get rid of unnecessary GCC bits */
   /DISCARD/ :
   {
     *(.comment)
     *(.eh_frame)
     *(.note.gnu.build-id)
   }
}

