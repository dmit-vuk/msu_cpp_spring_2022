#ifndef PARSER
#define PARSER

#include <string>

using std::string;

class TokenParser
{
private:
	void (*StartFunc)(const string &) = nullptr;
	void (*EndFunc)(const string &) = nullptr;
	void (*DigitFunc)(const uint64_t) = nullptr;
	void (*StringFunc)(const string &) = nullptr;
	size_t num_digs=0, num_strs=0; 

public:
    TokenParser() = default;

    // Устанавливаем callback-функцию перед стартом парсинга.
    void SetStartCallback(void (*func)(const string &));

    // Устанавливаем callback-функцию после окончания парсинга.
    void SetEndCallback(void (*func)(const string &));

    // Устанавливаем callback-функцию для обработки чисел.
    void SetDigitTokenCallback(void (*func)(uint64_t));
    
    // Устанавливаем callback-функцию для обработки строк.
    void SetStringTokenCallback(void (*func)(const string &));


    size_t get_digs();
    size_t get_strs();
    void Parse(const string &);
};


#endif
