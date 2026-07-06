#include<cmath>

template<typename T>
struct V {
  T x() const {return m_x;}
  T y() const {return m_y;}
  T z() const {return m_z;}
  T mag() const { return sqrt(mag2());}
  T mag2() const { return  perp2() + z()*z();}
  T perp() const { return sqrt(perp2());} 
  T perp2() const { return x()*x()+y()*y();}

  T m_x, m_y, m_z;
};

using VD = V<double>;
using VF = V<float>;

namespace original {
// Original

void eloss(VD mom, double radLen, double & z, double & varz ) {
  // Energy loss and variance according to Bethe and Heitler, see also
  // Comp. Phys. Comm. 79 (1994) 157. 
  //
  double p = mom.mag();
  double normalisedPath = fabs(p/mom.z())*radLen;
  z = exp(-normalisedPath);
  varz = (exp(-normalisedPath*log(3.)/log(2.))- exp(-2*normalisedPath));
}


double r_x, r_y, s;
void sniplet(VD mom, double a_i, double d_x, double d_y) {
  double pt = mom.perp();  
  double j = a_i*(d_x * mom.x() + d_y * mom.y())/(pt*pt);      
  r_x = d_x - 2* mom.x()*(d_x*mom.x()+d_y*mom.y())/(pt*pt);         
  r_y = d_y - 2* mom.y()*(d_x*mom.x()+d_y*mom.y())/(pt*pt);         
  s = 1/(pt*pt*sqrt(1 - j*j));
}

}

namespace optimized {
// Optimized (?!?)

void eloss(VF mom, float radLen, float & z, float & varz ) {
  // Energy loss and variance according to Bethe and Heitler, see also
  // Comp. Phys. Comm. 79 (1994) 157.
  //
  const float log3o2 = log(3.)/log(2.);
  float p = mom.mag();
  float normalisedPath = std::abs(p/mom.z())*radLen;
  z = std::exp(-normalisedPath);
  varz = std::exp(-normalisedPath*log3o2)- z*z;
}


float r_x, r_y, s;
void sniplet(VF mom, float a_i, float d_x, float d_y) {
  float pt2Inv = 1.f/mom.perp2();
  auto fact = pt2Inv*(d_x*mom.x()+d_y*mom.y());
  float j = a_i*fact;
  r_x = d_x - mom.x()*(2.f*fact);
  r_y = d_y - mom.y()*(2.f*fact);
  s = pt2Inv/std::sqrt(1.f - j*j);
}

}
