#include<cmath>
#include<iostream>
#include<iomanip>

// only for  -45deg < x < 45deg

inline float sin7d( float x) {

    float z = x * x;

    return x + (((-1.9515295891E-4f * z
       + 8.3321608736E-3f) * z
       - 1.6666654611E-1f) * z * x);


//  return  x + x*z * (-0.1666665375232696533203125f + z * (8.332121185958385467529296875e-3f 
//                    + z * (-1.951101585291326045989990234375e-4f)));

//  return  x + x * z * (-0.1666665375232696533203125f + z * (8.3321221172809600830078125e-3f + z * -1.951117883436381816864013671875e-4f));
// return  x + x*z * (-0.16666655242443084716796875 + z * (8.332191966474056243896484375e-3 + z * (-1.95187909412197768688201904296875e-4))) ;
}


inline float sin5( float x) {

    float z = x * x;

    return  x * (0x1.ffffcep-1f + z * (-0x1.553eeep-3f + z * 0x1.0b10dap-7f));
}


inline float sin7( float x) {

    float z = x * x;
    return x +  x * z * (-0x1.555544p-3f + z * (0x1.1106e6p-7f + z * (-0x1.992cf8p-13f)));
}

inline float sin9( float x) {
// float s =  x * (1 + x^2 * (-0.16666667163372039794921875 + x^2 * (8.33337195217609405517578125e-3 + x^2 * (-1.98499110410921275615692138671875e-4 + x^2 * 2.800547008519060909748077392578125e-6)))) ;
   float z = x * x;
   return x +  x*z * (-0x1.555556p-3f + z * (0x1.111164p-7f + z * (-0x1.a04866p-13f + z * 0x1.77e21p-19f)));
}


void go(float x, double sx, float sf) {

   float zero = ::sinf(0.0f);
   float a = ::sinf(x);
   float b = ::sinf(x+zero);
   float s7d = sin7d(x+zero);
   float s9 = sin9(x+zero);
   float s7 = sin7(x+zero);
   float s5 = sin5(x+zero);
   double d = ::sin(x);

   std::cout << "x x/pi " << std::defaultfloat << x << " " << x/float(M_PI) << std::endl; 
   std::cout << "mpfr sin(" << std::hexfloat << x<< ") = " << sx << ' ' << sf << std::endl; 
   std::cout << "compile time " << std::hexfloat << a << std::endl; 
   std::cout << "sinf " << std::hexfloat << b << std::endl;
   std::cout << "sin7d " << std::hexfloat << s7d << std::endl;
   std::cout << "sin9 " << std::hexfloat << s9 << std::endl;
   std::cout << "sin7 " << std::hexfloat << s7 << std::endl;
   std::cout << "sin5 " << std::hexfloat << s5 << std::endl;
   std::cout << "sin " << std::hexfloat << d << std::endl;
   std::cout << "sin(f) " << std::hexfloat << float(d) << std::endl;
   std::cout << std::endl;
}

int main() {
// 0xb.5755p-4
//   float x = 0xd.c46p-4; double sx = 0xc.214e980000518p-4; float sf =  0xc.214e98p-4;
//   float x = 0xb.adc51p-4; double sx = 0xa.ab444fffffff4p-4; float sf= 0xa.ab445p-4;
//   float x = 0xc.8dceap-4; double sx = 0xb.4e0ea8000023p-4;float sf= 0xb.4e0ea8p-4;

     go(0x5.806b1p-4,  0x5.64d3f400000a6p-4, 0x5.64d3f4p-4);
     go(0x5.d3e418p-4, 0x5.b31f4fffffcb2p-4, 0x5.b31f5p-4);
     go(0x8.e31a6p-4,  0x8.6fe8b0000072p-4, 0x8.6fe8bp-4);
     
     go(0xb.adc51p-4, 0xa.ab444fffffff4p-4, 0xa.ab445p-4);
     go(0xc.55f1ap-4, 0xb.2641e0000076cp-4, 0xb.2641ep-4);

     go(0x2.e26e88p-12, 0x2.e26e840000066p-12, 0x2.e26e84p-12);
     go(0x2.e26e8cp-12, 0x2.e26e87fffff5cp-12, 0x2.e26e88p-12);

     go(0x1.d4f6b8p-4, 0x1.d3f098fffff6d8p-4, 0x1.d3f099p-4);
     go(0x1.9eab2ep-4, 0x1.9df5f10000003p-4, 0x1.9df5f1p-4);
     go(0x1.b51f12p-4, 0x1.b44ac800000f08p-4, 0x1.b44ac8p-4);

   return 0;
}


