#include "Extended_gcd.h"
using namespace boost::multiprecision;



cpp_int extended_gcd(cpp_int a, cpp_int m, cpp_int& s, cpp_int& t) {
    s = 1; // s = y IN ((y * m) + (x * a) = 1)
    t = 0; // t = x IN ((y * m) + (x * a) = 1)

    if (a == 0) return 0;
    if (m == 0) return a;

    cpp_int r = cpp_int(m);
    cpp_int new_r = cpp_int(a);
    cpp_int temp_r;

    cpp_int new_s = 0;
    cpp_int temp_s;
    
    cpp_int new_t = 1;
    cpp_int temp_t;

    cpp_int q; // Quotient

    while (new_r != 0) {
        q = r / new_r;

        temp_r = r - (new_r * q);
        r = new_r; new_r = temp_r;

        temp_s = s - (new_s * q);
        s = new_s; new_s = temp_s;

        temp_t = t - (new_t * q);
        t = new_t; new_t = temp_t;
    }
    return r;
}