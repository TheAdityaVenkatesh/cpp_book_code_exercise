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
 "-" Primary         //to allow for expressions like : -1/2
 "+" Primary
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

//defining a const for the character token type
const char numberSym = 'n';
const char letSym = 'L';
const char nameSym = 'a';
const std::string declKey = "let";


//define error function
void error(std::string errMsg){         //standard error function, throwing runtime error
    throw std::runtime_error(errMsg);
}

//define Token class
class Token{            //new Token type, objects have a type and a value
    public:
        char type;      //respective character for an operator, 'n' for a number
        double val;     //if type = 'n', contains the respective value of the number
        std::string name;
        Token(char ch): type{ch}{}                  //3 different constructors
        Token(char ch, double val): type{ch}, val{val}{}
        Token(char ch, std::string n): type{ch}, name{n}{} 
        Token(){}
};

//define Variable class
class Variable{
    public:
        std::string name;
        double val;
};

//define TokenBuffer class
class TokenBuffer{
    public:
        Token get();        //tries to get a token from first the buffer, and if not poss., from std::cin
        void putInBuffer(Token t);     //tries to put the provided token in the buffer
        void ignoreUntil(char c);       //moves through the token stream (std::cin in this case)
                                        //until given character occurs. skips over specified char too
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
        case ';':       //listing cases where only character needed for token
        case 'q':     
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
            return Token{ch};       //return a token with type = ch (since no value)

        case '.': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
        case '8': case '9': case '0':       //other cases where the next token is a number
        {
            std::cin.putback(ch);       //return the character to cin to read the full token
            double val;
            std::cin >> val;        //obtain the token as a double
            return Token{numberSym, val};
        }
        default:            //in case bad token is entered
            if(isalpha(ch)){
                std::string s;
                s += ch;
                while(std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                std::cin.putback(ch);
                if(s == declKey) return Token{letSym};
                return Token{nameSym,s};
            }
            error("bad token");
            return Token{'x', 0};       //this line can be removed, but compiler raises warning without
                                        //default ret
    }
}

//ignoreUntil definition
void TokenBuffer::ignoreUntil(char c){
    if(full && (buffer.type == c)){       //if the buffer contains the character
        full = false;
        return;
    }

    full = false;
    char ch;
    while(std::cin >> ch){      //moves cin position along
        if(ch == c) return;
    }
}

//function definitions here since they go back and forth in the grammar - prevents compile issues
double expression();
double term();
double primary();

//creating tokenbuffer
TokenBuffer tb;

//creating variable table
std::vector<Variable> varTable;

//getValue() definition - gets the value of a variable whose name we know
double getValue(std::string varName){
    for(Variable v: varTable){
        if(v.name == varName){
            return v.val;
        }
    }
    error("unknown variable referenced");
    return -1;
}

//setValue() definition - sets the value of a known varaible
void setValue(std::string varName, double d){
    for(Variable v: varTable){
        if(v.name == varName){
            v.val = d;
            return;
        }
    }
    error("unkown variable refernced");
}

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
            case '%':
                {
                    double denom = primary();
                    if(denom == 0) error("cannot modulo by 0");
                    left = std::fmod(left, denom);
                    curTok = tb.get();
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
        case numberSym:       //if token is a number
            return curTok.val;
        case '+':
            return primary();
        case '-':
            return (- primary());
        case nameSym:
        {
            return getValue(curTok.name);
        }
        default:
            error("calculator - primary expected");
            return 0;
    }
}

//isDeclared function - returns whether a given variable has already been declared
bool isDeclared(std::string name){
    for(const Variable& v: varTable){
        if(v.name == name) return true;
    }
    return false;
}

//defineName function - allows for the declaration of a variable
double defineName(std::string name, double val){
    if(isDeclared(name)) error("variable already initialized");
    varTable.push_back(Variable{name,val});
    return val;
}

//declaration function - grammar section that allows to declare variables
double declaration(){
    Token t = tb.get();
    if(t.type != nameSym) error("name of variable expected in declaration");
    std::string varName = t.name;

    Token t2 = tb.get();
    if(t2.type != '=') error("'=' missing in declaration of variable");

    double d = expression();
    defineName(varName, d);
    return d;
}

//statement function - selects between a declaration or expression
double statement(){
    Token t = tb.get();
    switch(t.type){
        case letSym:
            return declaration();
        default:
            tb.putInBuffer(t);
            return expression();
    }
}

//inputExceptionHandler function
void inputExceptionHandler(){       //skips the rest of the equation, goes to the next one
    tb.ignoreUntil(';');
}

//calculate function
void calculate(){
    double val;
    while(std::cin){
        try{
            Token t = tb.get();     //gets next token
        
            if(t.type == 'q') break;        //break if quit token
            if(t.type == ';'){          //print if print token
                std::cout << "= " << val << "\n";
            }else{      //otherwise, put the token back and evaluate the incoming expression (will happen until
                tb.putInBuffer(t);      //an unexpected token occurs - be it ';', 'q', or an erroneous token
                val = statement();     //gets the next expression - note that expression() runs until it receives
            }                           //an entire expression - so this loop isn't quite token-by-token
        }
        catch(std::exception& e){
            std::cerr << "Error: " << e.what() << "\n";
            inputExceptionHandler();
        }                  
    }
}

//main function
int main()
try{
    std::cout << "Program start\n";
    calculate();
}
catch(std::exception& e){
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
}catch(...){
    std::cerr << "an unknown exception occurred\n";
    return 2;
}