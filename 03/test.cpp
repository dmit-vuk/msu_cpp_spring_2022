#include <ostream>
#include <gtest/gtest.h>
#include "DenseMatrix.hpp"


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
    const size_t rows = 5;
    const size_t cols = 3;

    DenseMatrix m(rows, cols);

    ASSERT_EQ(m.num_rows(),  5);
    ASSERT_EQ(m.num_columns(), 3);

    m[1][2] = 5; // строка 1, колонка 2
    double x = m[4][1];
    
    ASSERT_EQ(x,  0);
    ASSERT_EQ(m[1][2],  5);
    ASSERT_EQ(m[1][2],  m.get(1, 2));
    
    DenseMatrix m1(rows, cols);
    
    ASSERT_NE(m, m1);
    
}

TEST_F(TestFoo, test_const_method2)
{
    const size_t rows = 5;
    const size_t cols = 3;

    DenseMatrix m1(rows, cols), m2(rows, cols);
    
    m1[1][1] = 5; // строка 1, колонка 2
    m2[2][1] = 10;
    m2[1][1] = 15;
    DenseMatrix m3 = m1 + m2;
    
    ASSERT_EQ(m3[1][1],  20);
    ASSERT_EQ(m3[2][1],  10);
    
    ASSERT_ANY_THROW(m3[5][1]);
    ASSERT_ANY_THROW(m3[1][3]);
    
    **(m3 + 1) = 30;
    std::cout << m3;
    ASSERT_EQ(m3[1][0], 30);
    
    m3 *= 2;
    
    ASSERT_EQ(m3[1][1],  40);
    ASSERT_EQ(m3[2][1],  20);
    ASSERT_EQ(m3[1][0],  60);
    
    const DenseMatrix m4 = m3;
    ASSERT_EQ(m3,  m4);
    std::cout << m4;
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
