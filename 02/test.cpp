#include <iostream>
#include <gtest/gtest.h>
#include "parser.hpp"

using std::string;

class TestFoo : public ::testing::Test
{
protected:
	void SetUp()
	{
        std::cout << "SetUp" << std::endl;
	}
	void TearDown()
	{
        std::cout << "TearDown" << std::endl;
	}
};

static void dig_func(uint64_t num) {
    std::cout << "Digit: " << num << "\n";
}

static void str_func(const string &str) {
    std::cout << "String: " << str << "\n";
}

TEST_F(TestFoo, test1)
{
    TokenParser parser;

    parser.SetDigitTokenCallback(dig_func);
    parser.SetStringTokenCallback(str_func);
    
    parser.Parse("tyu87 78cvbn 		12   96u78 ");
    ASSERT_EQ(parser.get_digs(),  1);
    ASSERT_EQ(parser.get_strs(),  3);
    
    parser.Parse("12 7878 iu89 		fghj        ");
    ASSERT_EQ(parser.get_digs(),  2);
    ASSERT_EQ(parser.get_strs(),  2);
    
    parser.Parse("	     789213");
    ASSERT_EQ(parser.get_digs(),  1);
    ASSERT_EQ(parser.get_strs(),  0);
    
    parser.Parse("");
    ASSERT_EQ(parser.get_digs(),  0);
    ASSERT_EQ(parser.get_strs(),  0);
    
    parser.Parse("\n");
    ASSERT_EQ(parser.get_digs(),  0);
    ASSERT_EQ(parser.get_strs(),  0);
    
    parser.Parse("       	");
    ASSERT_EQ(parser.get_digs(),  0);
    ASSERT_EQ(parser.get_strs(),  0);
    
    parser.Parse("   1 a");
    ASSERT_EQ(parser.get_digs(),  1);
    ASSERT_EQ(parser.get_strs(),  1);
    
    parser.Parse("1");
    ASSERT_EQ(parser.get_digs(),  1);
    ASSERT_EQ(parser.get_strs(),  0);
    
    parser.Parse("a");
    ASSERT_EQ(parser.get_digs(),  0);
    ASSERT_EQ(parser.get_strs(),  1);
    
    parser.Parse("18446744073709551615");
    ASSERT_EQ(parser.get_digs(),  1);
    ASSERT_EQ(parser.get_strs(),  0);
    
    ASSERT_ANY_THROW(parser.Parse("18446744073709551616"));
}

TEST_F(TestFoo, test2)
{
    TokenParser parser;

    parser.SetDigitTokenCallback(nullptr);
    parser.SetStringTokenCallback(nullptr);
    parser.SetStartCallback(nullptr);
    parser.SetEndCallback(nullptr);
    
    parser.Parse("tyu87 78cvbn 		12   96u78 ");
    ASSERT_EQ(parser.get_digs(),  1);
    ASSERT_EQ(parser.get_strs(),  3);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
