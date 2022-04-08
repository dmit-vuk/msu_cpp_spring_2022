#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include "parser.hpp"

using std::string;

class TestFoo : public ::testing::Test
{
protected:
    std::ifstream file;
	void SetUp()
	{
        file.open("test.txt");
        std::cout << "SetUp" << std::endl;
	}
	void TearDown()
	{
        file.close();
        std::cout << "TearDown" << std::endl;
	}
};

static void dig_func(const string &str) {
    std::cout << "Digit: " << str << "\n";
}
static void str_func(const string &str) {
    std::cout << "String: " << str << "\n";
}

TEST_F(TestFoo, test_set)
{
    TokenParser parser;

    parser.SetDigitTokenCallback(dig_func);
    parser.SetStringTokenCallback(str_func);
    
    string line;
    while (std::getline(file, line)) {
        parser.Parse(line);
    }
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
