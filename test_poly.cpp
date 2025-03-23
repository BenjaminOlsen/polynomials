#include "gtest/gtest.h"
#include "poly.hpp"


// -------------------------------------------------------------------------------------------------
TEST(poly_test, self_identity)
{
    polynomial<double> p1({1,2,3});
    EXPECT_EQ(p1,p1);
}

// -------------------------------------------------------------------------------------------------
TEST(poly_test, assignment)
{
    polynomial<double> p1(1,2,3);
    polynomial<double> p2({1,2,3});
    EXPECT_EQ(p1, p2);
}

// -------------------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
