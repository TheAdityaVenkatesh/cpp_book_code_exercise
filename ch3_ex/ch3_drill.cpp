#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    cout << "Enter the name of the person you want to write to\n";      //corresponding block
    string first_name, friend_name;
    cin >> first_name;

    int age;
    cout << "Enter the age of recipient\n";     //get age and handle exceptions
    cin >> age;
    if(age <= 0 || age >= 110){         //lib unavailable for simple_error() so just print to cout and exit
        cout << "youre kidding!";
        return 1;
    }

    cout << "Enter the name of your friend\n";      //corr block
    cin >> friend_name;

    char friend_sex = 0;
    cout << "Enter the sex of you friend\n";        //corr block
    cin >> friend_sex;

    cout << "Dear " << first_name << ",\n";
    cout << "\tHow are you? blah blah.\nHave you seen " << friend_name << " lately?\n";

    if(friend_sex == 'm'){      //if cond for sex
        cout << "If you see " << friend_name << " please ask him to call me.\n";
    }else if(friend_sex == 'f'){
        cout << "If you see " << friend_name << " please ask her to call me.\n";
    }

    if(age < 12){
        cout << "Next year you will be " << (age+1);
    }else if(age == 17){
        cout << "Next year you will be able to vote.";
    }else if(age > 70){
        cout << "I hope you are enjoying retirement.";
    }

    cout << "\nSincerely, Me"; 
}