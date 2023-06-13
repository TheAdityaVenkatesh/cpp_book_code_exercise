#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main(){
    std::vector<std::string> words;
    std::vector<std::string> blacklist = {"damn", "crap", "shit"};
    
    std::cout << "Enter a sentence:\nTo terminate, press enter to flush buffer, then Ctrl+Z, then enter again\n";
    for(std::string word; std::cin >> word;){
        //if(word == std::string('\x04'))
        //    break;
        if(std::find(blacklist.begin(), blacklist.end(), word) != blacklist.end()){
            words.push_back("BLEEP");}
        else{
            words.push_back(word);}
    }
    for(std::string changedWord: words){
        std::cout << changedWord << " ";
    }
}