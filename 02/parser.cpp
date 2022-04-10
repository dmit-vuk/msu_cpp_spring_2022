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

void TokenParser::SetDigitTokenCallback( void (*func)(uint64_t))
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
    bool digit = true;
    num_strs = num_digs = 0;
    if (StartFunc)
        StartFunc("Start parsing");
    for (size_t i=0; i < str.length(); ++i) {
        if (isspace(str[i])) {
            if (!token.empty()) {
                if (digit){
                    ++num_digs;
                    if(DigitFunc)
                        DigitFunc(std::stoull(token));
                } else {
                    ++num_strs;
                    if(StringFunc)
                        StringFunc(token);
                }
                digit = true;
                token.clear();
            }
            continue;
        }
        token += str[i];
        if (!std::isdigit(str[i]))
            digit = false;
    }
    
    if (!token.empty()) {
        if (digit) {
            ++num_digs;
            if(DigitFunc)
                DigitFunc(std::stoull(token));
        } else{
            ++num_strs;
            if(StringFunc)
                StringFunc(token);
        }
        token.clear();
    }
    if (EndFunc)
        EndFunc("End parsing");
    return;
}

size_t TokenParser::get_digs(){
    return num_digs;
}

size_t TokenParser::get_strs(){
    return num_strs;
}
