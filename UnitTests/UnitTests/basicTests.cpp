//
//  basicTests.cpp
//  UnitTests
//
//  Created by Jonathan Ginsburg on 8/15/17.
//  Copyright © 2017 Jonathan Ginsburg. All rights reserved.
//

#include "gtest/gtest.h"

TEST(FirstCase, TestOne) {
    ASSERT_FALSE(false);
    char * ariel = (char *)"Ariel";
    ASSERT_EQ("Ariel", ariel);
    ASSERT_NE("Ariel", "Jonathan");
    ASSERT_TRUE(false) << "It is only fatal, for the CURRENT TEST, if it fails.";
    SUCCEED(); //This will not run, for the previous test is fatal.
}

TEST(FirstCase, TestTwo) {
    ADD_FAILURE(); //Not fatal failure.
    ASSERT_LT(1, 2);
    ASSERT_LE(22, 22);
    ASSERT_GT(3, 2);
    ASSERT_GE(5, 2);
    FAIL();
}

TEST(FirstCase, TestThree) {
    ASSERT_STREQ("Ariel", "Ariel");
    ASSERT_STRNE("Ariel", "Jonathan");
    ASSERT_STRCASEEQ("ArIel", "Ariel");
    ASSERT_STRCASENE("ariel", "jonathan");
}

TEST(FirstCase, TestFour) {
    ASSERT_THROW(([](){throw std::out_of_range("Trivial out of range exception.");})(), std::out_of_range);
    ASSERT_ANY_THROW(([](){throw std::runtime_error("Trivial runtime error.");})());
    ASSERT_NO_THROW(([](){})());
    ASSERT_DOUBLE_EQ(3.56, 3.56);
    ASSERT_FLOAT_EQ(7.890, 7.890);
    ASSERT_NEAR(9.8, 10.4, 1);
}
