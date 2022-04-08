#ifndef PARSER
#define PARSER

#include <string>

using std::string;

class TokenParser
{
private:
	void (*StartFunc)(const string &) = nullptr;
	void (*EndFunc)(const string &) = nullptr;
	void (*DigitFunc)(const string &) = nullptr;
	void (*StringFunc)(const string &) = nullptr;

public:
    TokenParser() = default;

    // Устанавливаем callback-функцию перед стартом парсинга.
    void SetStartCallback(void (*func)(const string &));

    // Устанавливаем callback-функцию после окончания парсинга.
    void SetEndCallback(void (*func)(const string &));

    // Устанавливаем callback-функцию для обработки чисел.
    void SetDigitTokenCallback(void (*func)(const string &));
    
    // Устанавливаем callback-функцию для обработки строк.
    void SetStringTokenCallback(void (*func)(const string &));

    void Parse(const string &);
};


#endif
