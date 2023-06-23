#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

/*
-----------------------------
PARSE TREE
-----------------------------
Expression:
 Term
 Expression “+” Term
 Expression “–” Term
Term:
 Primary
 Term “*” Primary
 Term “/” Primary
Primary:
 Number
 “(” Expression “)”
Number:
 floating-point-literal
==============================

Program specs:
------------------------------
- accept input, calculate result of expression so far, triggered by a 'calculate' character
- program terminated by a 'quit' character
- parse expression according to PEDMAS - using above grammar (starts as expression)
- make token class for each expression element - contains kind and value elements
- tokenbuffer class to 1) make a buffer for tokens, also to 2) get tokens from buffer or cin
- Tokenputback() - puts token (param) into buffer
- get() - returns token either from buffer, or cin

- keep accepting inputs from cin until print or quit token entered, then act accordingly.
    otherwise put it back into buffer
- ';' to evaluate and print expression
- 'q' to quit program

==============================*/


//define error function
void error(std::string errMsg){         //standard error function, throwing runtime error
    throw std::runtime_error(errMsg);
}

//define Token class
class Token{            //new Token type, objects have a type and a value
    public:
        char type;      //respective character for an operator, 'n' for a number
        double val;     //if type = 'n', contains the respective value of the number
};

//define TokenBuffer class
class TokenBuffer{
    public:
        Token get();        //tries to get a token from first the buffer, and if not poss., from std::cin
        void putInBuffer(Token t);     //tries to put the provided token in the buffer
    private:
        bool full{false};       //state of the buffer
        Token buffer;           //actual buffer of a single token
};

//define TokenStream functions

//accepts a Token as parameter, and attempts to put it in the TokenBuffer's buffer
void TokenBuffer::putInBuffer(Token t){     //implementation of putInBuffer
    if(full == true) error("cannot putInBuffer with buffer already full");      //condition if buffer full
    full = true;
    buffer = t;
}

//if there is a token in buffer, get that token. Otherwise get a token from cin
Token TokenBuffer::get(){
    if(full == true){       //if there is a token in the buffer
        full = false;
        return buffer;
    }
    //if no token in buffer, obtain a token from cin
    char ch;
    std::cin >> ch;     //obtain a character from cin, will identify token from that

    switch(ch){
        case ';': case 'q':     //listing cases where only character needed for token
        case '(': case ')': case '+': case '-': case '*': case '/':
            return Token{ch};       //return a token with type = ch (since no value)

        case '.': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
        case '8': case '9': case '0':       //other cases where the next token is a number
        {
            std::cin.putback(ch);       //return the character to cin to read the full token
            double val;
            std::cin >> val;        //obtain the token as a double
            return Token{'n', val};
        }
        default:            //in case bad token is entered
            error("bad token");
            return Token{'x', 0};       //this line can be removed, but compiler raises warning without
                                        //default ret
    }
}

//function definitions here since they go back and forth in the grammar - prevents compile issues
double expression();
double term();
double primary();

TokenBuffer tb;

//define expression function
double expression(){        //expression is a sum (+ or -) of terms
    double left = term();       //start with the first (leftmost) term
    Token curTok = tb.get();

    while(true){        //scroll through terms and perform operations accordingly
        switch(curTok.type){
            case '+':
                left += term();
                curTok = tb.get();
                break;
            case '-':
                left -= term();
                curTok = tb.get();
                break;
            default:
                tb.putInBuffer(curTok);     //return taken token to buffer in case expression is finished
                return left;
        }
    }
}

//define term function
double term(){      //term is a product (* or /) of primaries
    double left = primary();
    Token curTok = tb.get();

    while(true){        //all identical to expression()
        switch(curTok.type){
            case '*':
                left *= primary();
                curTok = tb.get();
                break;
            case '/':
                {
                    double divisor = primary();
                    if(divisor != 0){
                        left /= divisor;
                        curTok = tb.get();
                    }else{
                        error("cannot divide by 0");
                    }
                break;
                }
            default:
                tb.putInBuffer(curTok);
                return left;
        }
    }
}

//define primary function
double primary(){       //primary is either an expression within parentheses, or a number
    Token curTok = tb.get();

    switch(curTok.type){
        case '(':       //handles case when next token is a parenthesis
        {
            double val = expression();
            if(tb.get().type != ')') error("no closing parenthesis");
            return val;
        }
        case 'n':       //if token is a number
            return curTok.val;
        default:
            error("calculator - primary expected");
            return 0;
    }
}

//main function
int main(){
    std::cout << "Program start\n";
    double val;
    while(std::cin){
        Token t = tb.get();     //gets next token
        
        if(t.type == 'q') break;        //break if quit token
        if(t.type == ';'){          //print if print token
            std::cout << "\n= " << val << "\n";
        }else{      //otherwise, put the token back and evaluate the incoming expression (will happen until
            tb.putInBuffer(t);      //an unexpected token occurs - be it ';', 'q', or an erroneous token
            val = expression();     //gets the next expression - note that expression() runs until it receives
        }                           //an entire expression - so this loop isn't quite token-by-token
    }
}