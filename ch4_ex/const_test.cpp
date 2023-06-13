#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

constexpr int max = 100;

int main(){
    /*constexpr double pi = 3.141592;     //compile-time constant
    const double pi2 = 7;           //run-time constant (?)
    constexpr double pi3 = pi;      //cannot instead do constexpr double pi3 = pi2

    cout << pi << pi2 << pi3;*/
    
    int n = 8;

    constexpr int c1 = max + 7;
    const int c2 = n + 7;

}

//const handles casese where the value of a variable is not known at compile time,
//but doesnt change after initialization