#include <iostream>
#include <iomanip>
#include <tuple>

template<typename T> 
std::tuple<T,T> aSum(T x, T y) {
  /// valid only if |x| > |y|
  auto s = x+y;
  auto t = s-x;
  auto e = y-t;
  return {s,e};
}


template<typename T>
std::tuple<T,T> aMul(T x, T y) {
  auto r = x*y;
  return {r, std::fma (x, y, -r)} ;
}


template<typename T>
std::tuple<T,T> aRcp(T x, T e) {
  T a = 1.;
  auto t = a/x;
  auto [hi,s] = aMul(t,x);
  auto lo = std::fma(t, e, s);
  auto p = a - hi;
  auto d = p - lo;
  d = d/hi;
  return aSum(t, d);
}

#ifndef KK
#define KK 2
#endif

template<typename T> 
T pairwise(T step, int p, int e) {
 // std::cout << "rec " << p << ' ' << e << std::endl;
 if (e-p<=KK) {
    T sum=0; 
    for (int i=p; i<e; ++i) {
       T x = (T(i) + T(0.5))*step; 
       sum +=  T(4)/(T(1)+x*x);         
    }
    return sum;
 } else {
   int m = p+(e-p)/2;
   return pairwise(step,p,m)+pairwise(step,m,e);
  }  
}

using T = float;


int main() {


  for (int k=1; k<4*1024; k*=2) {

  int N = k * 256;

  T step = T(1)/T(N);
  T sum=0, isum=0; 
  T ksum=0, t=0;
  T old = 0; int nnew=0;
#ifdef SUM
  T x = - T(0.5)*step;
#endif
  for (int i=0; i<N; ++i) {
#ifdef SUM
    x += step;
#else
    T x = (T(i) + T(0.5))*step;
#endif
    auto w = T(4)/(T(1)+x*x);
    if (w!=old) { old=w; ++nnew;}
    sum +=w;
    auto y = w - t; 
    auto s = ksum + y;
    t = (s - ksum) - y;   
    ksum = s;
    w = (T(N-i) - T(0.5))*step;
    w = T(4)/(T(1)+w*w);
    isum +=w;
  }
  sum *=step; ksum*=step; isum*=step;
  std::cout << N << ' ' << nnew << ": " << std::hexfloat << sum << ' ' << ksum << ',' << t*step << ' ' << isum << ' ' << step*pairwise(step,0,N) << std::endl; 



//   T s,t, r,e;
  T vsum=0, esum=0;;
  for (int i=0; i<N; ++i) {
    T x = (T(i) + T(0.5f))*step;
    auto [s,t] = aSum(T(1), x*x); 
    auto [r,e] = aRcp(s,t);
    vsum +=r; esum+=e;
    // std::cout << std::hexfloat << x << ' ' << x*x << ' ' << s << ',' << t << ' ' << T(1)/s << ' ' << r << ',' << e << ' ' << -r*r*t << std::endl; 
  }
  vsum *= T(4)*step; esum *= T(4)*step;
  std::cout << N << ' ' << std::hexfloat << vsum <<',' << esum << std::endl;


}
  return 0;
}
