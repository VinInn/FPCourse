// generate hard-to-round cases for sinf in [0.5,1)
// with at least 20 identical bits after the round bit

#include <stdio.h>
#include <mpfr.h>

static void
check (mpfr_t x) {
 mpfr_t y, z,w;
 mpfr_init2 (w, 24 + 30);
 mpfr_init2 (y, 24 + 20);
 mpfr_init2 (z, 25);
 mpfr_sin (w, x, MPFR_RNDN);
 mpfr_sin (y, x, MPFR_RNDN);
 mpfr_set (z, y, MPFR_RNDN);
 if (mpfr_cmp (y, z) == 0)
   mpfr_printf ("%Ra, sin = %Ra %Ra\n", x,w,z);
 mpfr_clear (z);
 mpfr_clear (y);
}

int main()
{
 mpfr_t x;
 mpfr_init2 (x, 24);
 mpfr_set_d (x, 0.5, MPFR_RNDN);
 while (mpfr_cmp_ui (x, 1) < 0) {
   check (x);
   mpfr_nextabove (x);
 }
 mpfr_clear (x);
}

