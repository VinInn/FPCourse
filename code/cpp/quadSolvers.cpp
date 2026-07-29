// clang++ -fsanitize=numerical -Wall -g ~innocent/public/ctest/floatPrec/quadSolvers.cpp -fno-sanitize-trap=all -fsanitize-recover=all -Ofast -march=native -std=c++23 -fno-math-errno
// c++ -O3 -Wall quadSolvers.cpp -lquadmath -march=native -std=c++23 -fno-math-errno
// clang++ -O3 -Wall quadSolvers.cpp -lquadmath -I$gcc_home/lib/gcc/x86_64-pc-linux-gnu/15.0.0/include -march=native -std=c++23 -fno-math-errno
// see also https://marc-b-reynolds.github.io/math/2020/01/10/Quadratic.html
#include<cmath>
#include<tuple>
#include<limits>
// #include<quadmath.h>

template<typename T>
inline T det(T a, T b, T c) {
  // compute determinant for equation ax^2 + 2bx + c= 0
  return std::sqrt(b*b-a*c);
}

template<typename T>
T kahanDet(T a, T b, T c, T d) { // a*d-b*c
   using std::fma; 
   auto w = b*c; 
   auto e = fma(-b, c, w); // error on w: (w,-e) = augmentedMultiply(b,c)
   auto f = fma(a, d, -w); 
   return (f+e); 
}

template<typename T>
inline T kdet(T a, T b, T c) {
  // compute determinant for equation ax^2 + 2bx + c= 0
  return std::sqrt(kahanDet(b,a,c,b));
}


/*
template<>
inline __float128 det(__float128 a,  __float128 b, __float128 c) {
  // compute determinant for equation ax^2 + 2bx + c= 0
  return ::sqrtq(b*b-a*c);
}
*/

template<typename T,bool K>
inline std::tuple<T,T> quadSolverNaive(T a, T b, T c) {
  // solve equation ax^2 + 2bx + c= 0
  // using naive solution (as at college)
  auto d = -T(1)/a;
  auto q = K ? kdet(a,b,c) : det(a,b,c);
  return {d*(b-q),d*(b+q)};  
}


template<typename T,bool K>
inline std::tuple<T,T> quadSolverOpt(T a, T b, T c) {
  // solve equation ax^2 + 2bx + c= 0
  // using stable algorithm
  auto d  = K ? kdet(a,b,c) : det(a,b,c);
  auto q = -(std::copysign(d,b)+b);
  return {q/a,c/q};
}

/*
template<>
inline std::tuple<__float128,__float128> quadSolverOpt(__float128 a, __float128 b, __float128 c) {
  // solve equation ax^2 + 2bx + c= 0
  // using stable algorithm
  auto q = -(::copysignq(det(a,b,c),b)+b);
  return std::make_tuple(q/a,c/q);
}
*/



#include<iostream>
#include<iomanip>

using LD = long double;

template<typename T> 
void print(T x) {
  std::cout<< std::hexfloat << x <<' ' <<  std::scientific << std::setprecision(std::numeric_limits<T>::digits10+3) << LD(x) << std::endl;
}


template<typename T, bool K>
void go(T a) {
  std::cout <<' '<< std::endl;
  T c = 1.;
  T b=1;
  T n1, n2;
  // corse scan
  for (;;) { 
    b *=T(2);
    auto [s1,s2] = quadSolverNaive<T,K>(a,b,c);
    if (s1==0 || s2==0 ) break;
  }
  // last binned
  auto bl = b;
  for (b = bl/2; b<bl; b=nextafter(b,bl)) {
    auto [s1,s2] = quadSolverNaive<T,K>(a,b,c);
    if (s1==0 || s2==0 ) { n1 =s1; n2=s2; break; }
  }
 

  auto [o1,o2] = quadSolverOpt<T,K>(a,b,c);
  std::cout <<  std::scientific << std::setprecision(std::numeric_limits<T>::digits10+3);
  std::cout << a << ' ' << b << ' ' << c << std::endl;
  std::cout << "Naive Solution "<< LD(n1) << ' ' << LD(n2) << std::endl;
  std::cout << " Opt  Solution "<< LD(o1) << ' ' << LD(o2) << std::endl;
  std::cout << std::endl;
}


int main(int argc, char **){

  // go<__float128>(argc,vt);
  go<double,false>(argc);
  go<double,true>(argc);
  go<float,false>(argc);
  go<float,true>(argc);

  return 0;

}
