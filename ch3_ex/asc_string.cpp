#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    string a, b, c, temp;
    cout << "Enter 3 strings:\n";
    cin >> a >> b >> c;

    if(b < a){      //insertion sort
        temp=b;     //insert 2nd element
        b=a;
        a=temp;
    }
    if(c<b){        //insert 3rd element
        temp=c;
        c=b;
        b=temp;
        if(b<a){
            temp=b;
            b=a;
            a=temp;
        }
    }

    cout << a << " " << b << " " << c;
    return 0;
}