#include<cmath>
#include<iostream>
#include<iomanip>

// only for  -45deg < x < 45deg

inline float sin7d( float x) {

    float z = x * x;
/*
    return x + (((-1.9515295891E-4f * z
       + 8.3321608736E-3f) * z
       - 1.6666654611E-1f) * z * x);
*/

//  return  x + x*z * (-0.1666665375232696533203125f + z * (8.332121185958385467529296875e-3f 
//                    + z * (-1.951101585291326045989990234375e-4f)));

//  return  x + x * z * (-0.1666665375232696533203125f + z * (8.3321221172809600830078125e-3f + z * -1.951117883436381816864013671875e-4f));
 return  x + x*z * (-0.16666655242443084716796875 + z * (8.332191966474056243896484375e-3 + z * (-1.95187909412197768688201904296875e-4))) ;
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


int main() {

   float zero = ::sinf(0.0f);
   float a = ::sinf(0xb.5755p-4);
   float b = ::sinf(0xb.5755p-4+zero);
   float s7d = sin7d(0xb.5755p-4+zero);
   float s9 = sin9(0xb.5755p-4+zero);
   float s7 = sin7(0xb.5755p-4+zero);
   float s5 = sin5(0xb.5755p-4+zero);
   double d = ::sin(0xb.5755p-4);

   std::cout << "compile time " << std::hexfloat << a << std::endl; 
   std::cout << "sinf " << std::hexfloat << b << std::endl;
   std::cout << "sin7d " << std::hexfloat << s7d << std::endl;
   std::cout << "sin9 " << std::hexfloat << s9 << std::endl;
   std::cout << "sin7 " << std::hexfloat << s7 << std::endl;
   std::cout << "sin5 " << std::hexfloat << s5 << std::endl;
   std::cout << "sin " << std::hexfloat << d << std::endl;
   std::cout << "sin(f) " << std::hexfloat << float(d) << std::endl;


   return 0;
}
