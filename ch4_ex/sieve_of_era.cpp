#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

//implementing sieve of eratosthenes alg with square optimization to find first 100 primes (can be expanded)
//check wikipedia for details and info

int main(){
    std::cout << "Prime numbers between 1 to 100:\n";

    std::vector<int> numberSet(100);
    for(int i=2; i<=100; i++){       //loop through the numbers
        if(numberSet[i-1] == 0){
            for(int j=(i*i); j<=100; j+=i){     //marking composite numbers using square optimization
                numberSet[j-1] = 1;
            }
        }
    }

    for(int i=2; i<=100; i++){      //printing primes
        if(numberSet[i-1] == 0)
            std::cout << i << " ";
    }
}