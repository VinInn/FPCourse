#include <iostream>
#include <iomanip>
#include <tuple>
#include <cstring>
#include <cmath>
#include <cstdint>



int main() {


       float x = 3.5;

       uint32_t ix; memcpy(&ix,&x,sizeof(float));
       int e= ((ix >> 23) & 0xFF) -127; // extract exponent
       ix &= 0x007fffff; // significand
       ix |= 0x00800000; // add hidden bit

       std::cout <<  std::hexfloat << x << ' ' << e << ' ' << std::hex << ix << std::dec << std::endl;

       float y = exp2f(-23+e)*float(ix);
       uint32_t ie = (e-23+127) << 23;
       float z; memcpy(&z,&ie,sizeof(float));
       z *=float(ix);

       std::cout <<  std::hexfloat << x << ' ' << y << ' ' << z << std::endl;


}
