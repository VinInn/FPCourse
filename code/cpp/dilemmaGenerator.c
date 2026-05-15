// generate hard-to-round cases for sinf in [0.5,1)
// with at least 20 identical bits after the round bit

#include <stdio.h>
#include <mpfr.h>
#include <math.h>
#include <string.h>

int k =0;

void
check (mpfr_t x) {
 mpfr_t y, z,w,s;
 mpfr_init2 (w, 24 + 30);
 mpfr_init2 (y, 24 + 20);
 mpfr_init2 (z, 25);
 mpfr_init2 (s, 24);
 mpfr_sin (w, x, MPFR_RNDN);
 mpfr_sin (y, x, MPFR_RNDN);
 mpfr_sin (s, x, MPFR_RNDN);
 mpfr_set (z, y, MPFR_RNDN);
 if (mpfr_cmp (y, z) == 0) {
   mpfr_printf ("%Ra, sin = %Ra %Ra %Ra: ", x,w,z,s);
   double d = mpfr_get_d (x,MPFR_RNDN);
   double ww = mpfr_get_d (w,MPFR_RNDN);
   double zz = mpfr_get_d (z,MPFR_RNDN);
   double ss = mpfr_get_d (s,MPFR_RNDN);
   printf("%f %a %a %a %a:  %a %a %a\n",d, d,ww,zz,ss, sin(d), float(sin(d)), sinf(d));
 }
 mpfr_clear (z);
 mpfr_clear (y);
}


void checkS( float x) {
  double d = x;
  float sf = sinf(x);
  double sd = sin(d);
  unsigned long long si;
  memcpy(&si,&sd,sizeof(double));
  si = si>>8;
  int nz = __builtin_ctzll(si);
  int n1 = __builtin_ctzll(~si);
  if (nz==20 || n1==20) printf("ctz %f %a : %a %a %a %a\n",x, x, d, sd, sf, float(sd)); 
  if (sf != float(sd)) printf("sin %f %a : %a %a %a %a\n",x, x, d, sd, sf, float(sd));


}



int main()
{

 mpfr_t x,mx;
 mpfr_init2 (x, 24);
 mpfr_init2 (mx, 24);
 mpfr_set_d (x,  0x1.0p-2, MPFR_RNDN);
 mpfr_set_d (mx, 0x1.0p-1, MPFR_RNDN);
 while (mpfr_cmp (x, mx) < 0) {
   check (x);
   mpfr_nextabove (x);
 }
 mpfr_clear (x);


//  for (float x=0x1.0p-54; x<0x1.1p-1; x = nextafterf(x,10.f)) 
//    checkS(x);

  return 0;

}

