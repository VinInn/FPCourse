/* 
c++ -std=c++23 -O3 test_rsqrt.cpp -DNNR=0 -march=native; ./a.out
c++ -std=c++23 -O3 test_rsqrt.cpp -DNNR=1 -march=native; ./a.out
c++ -std=c++23 -O3 test_rsqrt.cpp -DNNR=2 -march=native; ./a.out
c++ -std=c++23 -O3 test_rsqrt.cpp -DNNR=0 -DNEWMAGIC -DNEWNR -march=native; ./a.out
c++ -std=c++23 -O3 test_rsqrt.cpp -DNNR=1 -DNEWMAGIC -DNEWNR -march=native; ./a.out
c++ -std=c++23 -O3 test_rsqrt.cpp -DNNR=2 -DNEWMAGIC -DNEWNR -march=native; ./a.out
c++ -std=c++23 -O3 test_rsqrt.cpp -DNNR=0 -march=native -DNOMAGIC ; ./a.out
c++ -std=c++23 -O3 test_rsqrt.cpp -DNNR=1 -march=native -DNOMAGIC ; ./a.out
*/
#include <cmath>
#include<cstdio>
#include<cstring>

#if defined(__x86_64__)
#include <x86intrin.h>
#endif

#include<tuple>
#include<memory>

#ifdef NEWMAGIC
// https://web.archive.org/web/20180709021629/http://rrrola.wz.cz/inv_sqrt.html
    constexpr int MC = 0x5F1FFFF9; // 1597465647;
#else
    constexpr int MC = 0x5f3759df;
#endif


// optimized NR (works only as first iteration)
inline float nr1(float x, float y) {
#ifdef NEWNR
// https://web.archive.org/web/20180709021629/http://rrrola.wz.cz/inv_sqrt.html
  // return y * (1.47f - 0.47f*x*(y*y));
  return 0.703952253f * y * (2.38924456f - x * (y * y));
#else
  return 0.5f * y * (3.f - x * (y * y));
#endif
}

// standard NR for rsqrt
inline float nr(float x, float y) {
  return 0.5f * y * (3.f - x * (y * y));
}


template<int NR=NNR>
float rsqrt(float x) {
  float y;
   #if defined(NOMAGIC)
     _mm_store_ss( &y, _mm_rsqrt_ss( _mm_load_ss( &x ) ) );
   #else
    union {float f;int i;} tmp;
    tmp.f = x;
    tmp.i = MC - (tmp.i >> 1);
    y = tmp.f;
   #endif
   if constexpr (NR>0) y = nr1(x,y);
   for (int i=1; i<NR; ++i)
    y = nr(x,y);
   return y;
}


std::pair<float,float>
ulp_error (float x)
{
 auto y = rsqrt (x);
 double z = 1./sqrt(double(x));
 float zf = z;
 float errf = fabsf (y - zf);
 int ef;
 auto q = frexpf (zf, &ef);
 /* ulp(z) = 2^(e-24) */
 return {ldexpf (errf, 24 - ef),(y-zf)/zf};
}


void merr() {
  float x, maxerr = 0, eneg=0, epos=0;
  float xerr = 0, xneg=0, xpos=0;
   x = 0.0118255867f;
   // x = 0x1.fffffcp+1;
   auto r = ulp_error (x);
   printf ("x=%a errf=%f\n", x, r.first);
 // for (x = 0.0001f; x < 10000.0f; x = nextafterf (x, 100000.f))
 for (x = 1.0f; x < 4.0f; x = nextafterf (x, 100000.f))
 {
   auto r = ulp_error (x);
   if (r.first > maxerr) { maxerr = r.first; xerr=x; }
   if (r.second < eneg) { eneg = r.second; xneg=x; }
   if (r.second > epos) { epos = r.second; xpos=x; }
 } 
 printf ("x=%a err=%f\n", xerr, maxerr);
 printf ("x=%a errneg=%f\n", xneg, eneg);
 printf ("x=%a errpos=%f\n", xpos, epos);

}


int main() {

  merr();

   return 0;
}
