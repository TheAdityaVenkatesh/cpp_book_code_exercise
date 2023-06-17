#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void error(std::string s){
    std::cout << "error() called\n";
    throw std::runtime_error(s);
}

int main()
try{
    std::cout << "Enter a positive or 0 integer\n";
    int x;

    std::cin >> x;

    if(x<0)
        error("you had one job\n");
    
    std::cout << "good job";

}
catch(std::out_of_range){           //results in uncaught error
    std::cout << "error caught!";
    return 1;
}