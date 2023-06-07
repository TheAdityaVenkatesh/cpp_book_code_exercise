#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    int val1, val2;
    cout << "Enter value 1 and value 2:\n";
    cin >> val1 >> val2;

    int larger, smaller;
    if(val1 > val2){
        larger = val1;
        smaller = val2;
    }else{
        larger = val2;
        smaller = val1;
    }

    int difference = larger - smaller;

    int prod = (val1*val2);

    double d1 = val1;
    double d2 = val2;
    double ratioed = d1/d2;

    cout << "Larger: " << larger;
    cout << "\nSmaller: " << smaller;
    cout << "\nDifference: " << difference;
    cout << "\nProd: " << prod;
    cout << "\nRatio: " << ratioed;
}