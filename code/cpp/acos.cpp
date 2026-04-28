#include <cmath>
#include <iostream>
#include <iomanip>

int main(int argc, char** argv) {

  float one = argc;
  float piw = acosf(-one);  
  double pid = piw;  
  float pi = 0x1.921fb6p+1;
  
  std::cout << std::scientific << std::setprecision(8) << pid << std::endl;
  std::cout << std::pow(9.f*9.f + 19.f*19.f/22.f,0.25f) << std::endl;
  std::cout << std::exp(piw) -piw << std::endl;
  std::cout << std::exp(pi) -pi << std::endl;
  std::cout << exp(M_PI) -M_PI << std::endl;
  std::cout << std::hexfloat << piw << std::endl;
  std::cout << std::pow(9.f*9.f + 19.f*19.f/22.f,0.25f) << std::endl;
  std::cout << std::exp(piw) -piw << std::endl;
  std::cout << std::exp(piw) -piw << std::endl;
  std::cout << std::exp(pi) -pi << std::endl;
  std::cout << exp(M_PI) -M_PI << std::endl;

  return 0;
}
