#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    string op;
    double ond1, ond2, res;
    cout << "Enter a prefix expression:\n";
    cin >> op >> ond1 >> ond2;
    cout << "Result = ";

    if(op == "+" || op == "plus"){
        res = ond1 + ond2;
    }else if(op == "-" || op == "minus"){
        res = ond1 - ond2;
    }else if(op == "*" || op == "mul"){
        res = ond1 * ond2;
    }else if(op == "/" || op == "div"){
        res = ond1 / ond2;
    }else{
        cout << "Parser error: Unidentified operator";
        return 0;
    }

    cout << res;
}