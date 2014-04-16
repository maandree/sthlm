#include "ktty.h"


void kmain(void);


void kmain(void)
{
  kputs("\033[94;44mKernels are magic\033[30;40m\033[J");
  /* By using 30;40 (black on black) we are hiding the cursor. */
}

