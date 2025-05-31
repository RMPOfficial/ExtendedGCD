#pragma once

#include <boost/multiprecision/cpp_int.hpp>

#define NOTONLYNUMBERS c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9'

#define EXIT 2
#define NO 1
#define YES 0

boost::multiprecision::cpp_int extended_gcd(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int m, boost::multiprecision::cpp_int& s, boost::multiprecision::cpp_int& t);
