# ExtendedGCD

## Description
This program is a simple realisation of the Extended Euclidean algorithm (using *Boost:\:multiprecision::cpp_int*).

## Features
- Calculating the greatest common divisor
- Calculating the modular inverse of a number if the GCD is 1
- Finding (y * m) + (x * a) = GCD using the Extended Euclidean algorithm

# Usage
 ExtendedGCD.exe -a [Your Number] -m [Your Modulo Number] [flags] or no arguments.
 
*Flags:*

+ -n / -N: No input. If you dont have any of the numbers and this flag it will output nothing and exit.

+ -r / -R: Outputs only the result: (x * a) + (y * m). Can mix with -g and -i.
+ -g / -G: Outputs only the GCD. Can mix with -i and -r.
+ -i / -I: Outputs only the modular inverse, if there is no modular inverse it outputs 0. Can mix with -g and -r.
-> Output order: Result (-r), GCD (-g), Modular Inverse (-i).


Example usage: ExtendedGCD-x64.exe -a 111 -m 991 -gi
