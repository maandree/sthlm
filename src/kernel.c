void kmain(void);


#define VIDEO_MEMORY  0xb8000


void kmain(void)
{
  const char* str = "Kernels are magic";
  char* vidptr = (char*)VIDEO_MEMORY;
  unsigned int i;
  
  /* Clear everything */
  for (i = 0; i < 80 * 25; i++)
    {
      vidptr[i * 2 + 0] = 0;
      vidptr[i * 2 + 1] = 0x00;
      /* Byte using 00h (black on black)
         we are hiding the cursor. */
    }
  
  /* Write text */
  for (i = 0; str[i]; i++)
    {
      vidptr[i * 2 + 0] = str[i];
      vidptr[i * 2 + 1] = 0x19;
    }
}

