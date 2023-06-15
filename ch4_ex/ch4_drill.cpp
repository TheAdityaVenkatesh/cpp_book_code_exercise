#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main(){
    double a, b;
    while(std::cin >> a >> b){
        double diff = a - b;


        if(a==b)
            std::cout << "The numbers are equal\n\n";
        else if(diff > -0.01 && diff < 0.01)
            std::cout << "The numbers are almost equal\n\n";
        else if(a<b)
            std::cout << "The smaller value is: " << a << "\nThe larger value is: " << b << "\n\n";
        else
            std::cout << "The smaller value is: " << b << "\nThe larger value is: " << a << "\n\n";
    }
}