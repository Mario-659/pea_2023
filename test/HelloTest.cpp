#include "gtest/gtest.h"

#include "Hello.cpp"

TEST(HelloTest, getOne){
    auto test = new Hello();
    EXPECT_EQ(1, test->getOne());
}

