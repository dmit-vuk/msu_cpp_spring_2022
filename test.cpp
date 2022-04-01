#include <iostream>
#include <gtest/gtest.h>
#include "allocator.hpp"


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

TEST_F(TestFoo, test_const_method)
{
	Allocator alc;
    alc.makeAllocator(7);
    char *p1 = alc.alloc(5);
    char *p2 = alc.alloc(1);
    char *p3 = alc.alloc(1);
    char *p4 = alc.alloc(1);
    
    ASSERT_EQ(p2 - p1, 5);
    ASSERT_EQ(p3 - p2, 1);
    ASSERT_EQ(p4, nullptr);
    
    alc.reset();
    p4 = alc.alloc(4);
    char *p5 = alc.alloc(3);
    ASSERT_EQ(p5 - p4, 4);
    
    ASSERT_ANY_THROW(alc.alloc(0));
}

TEST_F(TestFoo, test_string_method)
{
    Allocator alc;
    alc.makeAllocator(7);
    alc.makeAllocator(1);
    alc.makeAllocator(100);
    alc.makeAllocator(70);
    
    ASSERT_ANY_THROW(alc.makeAllocator(0));
}

TEST_F(TestFoo, test)
{
    Allocator alc;
    ASSERT_ANY_THROW(alc.alloc(10));
    alc.makeAllocator(20);
    
    char *p1 = alc.alloc(21);
    ASSERT_EQ(p1, nullptr);
    
    p1 = alc.alloc(20);
    char *p2 = alc.alloc(1);
    ASSERT_EQ(p2, nullptr);
    
    alc.reset();
    p1 = alc.alloc(13);
    p2 = alc.alloc(5);
    ASSERT_EQ(p2 - p1, 13);
    
    p1 = alc.alloc(3);
    ASSERT_EQ(p1, nullptr);
    
    p1 = alc.alloc(2);
    ASSERT_EQ(p1 - p2, 5);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
