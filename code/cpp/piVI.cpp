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

using T = float;


int main() {


  for (int k=1; k<4*1024; k*=2) {

  int N = k * 256;

  T step = T(1)/T(N);
  T sum=0;
  T ksum=0, t=0;
  for (int i=0; i<N; ++i) {
    T x = (T(i) + T(0.5f))*step;
    x = T(4)/(T(1)+x*x);
    sum +=x;
    auto y = x - t; 
    auto s = ksum + y;
    t = (s - ksum) - y;   
    ksum = s;                                    
  }
  sum *=step; ksum*=step;
  std::cout << N << ' ' << std::hexfloat << sum << ' ' << ksum << ',' << t*step << std::endl; 



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
