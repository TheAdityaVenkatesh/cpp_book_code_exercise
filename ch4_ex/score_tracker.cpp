#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<std::string> nameList;
std::vector<int> scoreList;

void printScore(std::string nameToSearch){
    for(int i=0; i<nameList.size(); i++){
        if(nameList[i] == nameToSearch){
            std::cout << "\nCorresponding score = " << scoreList[i];
            return;
        }
    }
    std::cout << "\nname not found";
    return;
}

void printNames(int scoreToSearch){
    int c=0;
    std::cout << "\nCorresponding names:\n";
    for(int i=0; i<scoreList.size(); i++){
        if(scoreList[i] == scoreToSearch){
            std::cout << nameList[i] << "\n";
            c++;
        }
    }
    if(c==0)
        std::cout << "\nscore not found";
}

int main(){

    std::cout << "Enter a list of name-score pairs:\n";
    
    int scoreInp;
    for(std::string nameInp; std::cin >> nameInp >> scoreInp;){     //input loop
        if(nameInp == "NoName" && scoreInp == 0)        //exit case
            break;
        for(std::string nameCheck: nameList){      //checking for duplicates in names
            if(nameInp == nameCheck){           //if dupe, return with error msg
                std::cout << "Error - duplicate name entered";
                return 1;
            }
        }
        nameList.push_back(nameInp);        //add the name and score if no issues
        scoreList.push_back(scoreInp);
    }

    for(int i=0; i<nameList.size(); i++){       //printing loop
        std::cout << nameList[i] << ": " << scoreList[i] << "\n";
    }

    std::string nameToFind;         //test to search for scores corresponding to a name
    std::cout << "Enter a name to get the corresponding score: ";
    std::cin >> nameToFind;
    printScore(nameToFind);

    int scoreToFind;         //test to search for scores corresponding to a name
    std::cout << "Enter a score to get the corresponding names: ";
    std::cin >> scoreToFind;
    printNames(scoreToFind);
}