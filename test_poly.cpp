#include "gtest/gtest.h"
#include "poly.hpp"
#include <cstdint>

template <typename T>
class poly_test: public ::testing::Test{};

using TestTypes = ::testing::Types<uint8_t, int8_t, uint16_t, int16_t, 
                                   uint32_t, int32_t, uint64_t, int64_t,
                                   float, double, long double>;
TYPED_TEST_SUITE(poly_test, TestTypes);

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, self_identity)
{
    polynomial<TypeParam> p1({1,2,3});
    EXPECT_EQ(p1, p1);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, self_identity_type)
{
    polynomial<int, 1, 2, 3> p1;
    EXPECT_EQ(p1, p1);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, identity)
{
    polynomial<TypeParam> p1({1,2,3});
    polynomial<TypeParam> p2(1,2,3,0,0,0,0);
    EXPECT_EQ(p1, p2);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, self_subtraction)
{
    polynomial<TypeParam> p(1,2,3,4,5,6,7,8,7,6,5,4,3,2,1,0,0,0,0,1,1,1);
    EXPECT_EQ(p-p, 0);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, reduce) 
{
    polynomial<TypeParam> p(1, 0, 0, 0, 0, 0);
    p.reduce();
    EXPECT_EQ(p.coeffs.size(), 1);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, reduce_does_nothing) 
{
    polynomial<TypeParam> p(1, 0, 0, 0, 0, 1);
    p.reduce();
    EXPECT_EQ(p.coeffs.size(), 6);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, assignment)
{
    polynomial<TypeParam> p1(1,2,3);
    polynomial<TypeParam> p2({1,2,3});
    EXPECT_EQ(p1, p2);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, multiplication_1)
{
    polynomial<TypeParam> p1(1,2,3);
    polynomial<TypeParam> p2 = p1 * 1;
    EXPECT_EQ(p1, p2);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, multiplication_2)
{
    polynomial<TypeParam> p1(1,2,3);

    polynomial<TypeParam> p2 = p1 * 2;
    EXPECT_EQ(p1, p2/2);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, multiplication_3)
{
    polynomial<TypeParam> p1(1,2,3);

    polynomial<TypeParam> p2 = p1 * 3;
    EXPECT_EQ(p1, p2/3);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, self_division_1)
{
    polynomial<TypeParam> p(1,2,3,4,5,6,7,8,9,10);
    EXPECT_EQ(p/p, 1);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, self_division_2)
{
    polynomial<TypeParam> p(1,2,3,4,5,6,7,8,9,10);
    EXPECT_EQ(2*p/p, 2);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, self_division_0)
{
    polynomial<TypeParam> p(1,2,3,4,5,6,7,8,9,10);
    polynomial<TypeParam> q = 0*p/p;
    EXPECT_EQ(q, 0);
}

// -------------------------------------------------------------------------------------------------
TYPED_TEST(poly_test, mult1)
{
    polynomial<TypeParam> p11(1,1);
    polynomial<TypeParam> p10(1,0);
    polynomial<TypeParam> p01(0,1);
    polynomial<TypeParam> q(7, 6, 3, 1, 2, 3, 4, 5, 6, 6);
    
    EXPECT_EQ(q*p11, (q*p10)+(q*p01));
}

// -------------------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
