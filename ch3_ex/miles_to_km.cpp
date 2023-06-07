#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    double d_mi;
    cout << "Enter a value in miles:\n";
    cin >> d_mi;
    double d_km = d_mi * 1.609;
    cout << "There are " << d_km << " kilometers in " << d_mi << "miles.";
}