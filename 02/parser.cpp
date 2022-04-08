#include <iostream>
#include "parser.hpp"

using std::string;

void TokenParser::SetStartCallback( void (*func)(const string &))
{
    StartFunc = func;
}

void TokenParser::SetEndCallback( void (*func)(const string &))
{
    EndFunc = func;
}

void TokenParser::SetDigitTokenCallback( void (*func)(const string &))
{
    DigitFunc = func;
}

void TokenParser::SetStringTokenCallback( void (*func)(const string &))
{
    StringFunc = func;
}

void TokenParser::Parse(const string &str)
{
    string token;
    void (*CurrFunk)(const std::string &) = DigitFunc;
    
    if (StartFunc)
        StartFunc("Start parsing");
    for (size_t i=0; i < str.length(); ++i) {
        if (isspace(str[i])) {
            if (!token.empty()) {
                if (CurrFunk)
                    CurrFunk(token);
                CurrFunk = DigitFunc;
                token.clear();
            }
            continue;
        }
        token += str[i];
        if (!std::isdigit(str[i]))
            CurrFunk = StringFunc;
    }
    
    if (!token.empty()) {
        if (CurrFunk)
            CurrFunk(token);
        token.clear();
    }
    
    if (EndFunc)
        EndFunc("End parsing");
    return; 
}
