// generate hard-to-round cases for sinf in [0.5,1)
// with at least 20 identical bits after the round bit

#include <stdio.h>
#include <mpfr.h>
#include <math.h>

static void
check (mpfr_t x) {
 mpfr_t y, z,w;
 mpfr_init2 (w, 24 + 30);
 mpfr_init2 (y, 24 + 20);
 mpfr_init2 (z, 25);
 mpfr_sin (w, x, MPFR_RNDN);
 mpfr_sin (y, x, MPFR_RNDN);
 mpfr_set (z, y, MPFR_RNDN);
 if (mpfr_cmp (y, z) == 0) {
   mpfr_printf ("%Ra, sin = %Ra %Ra\n", x,w,z);
   double d = mpfr_get_d (x,MPFR_RNDN);
   printf("%a %a %a\n",d,sin(d), sinf(d));
 }
 mpfr_clear (z);
 mpfr_clear (y);
}

int main()
{
 mpfr_t x,mx;
 mpfr_init2 (x, 24);
 mpfr_init2 (mx, 24);
 mpfr_set_d (x,  0x1.0p-4, MPFR_RNDN);
 mpfr_set_d (mx, 0x1.0p-3, MPFR_RNDN);
 while (mpfr_cmp (x, mx) < 0) {
   check (x);
   mpfr_nextabove (x);
 }
 mpfr_clear (x);
}

