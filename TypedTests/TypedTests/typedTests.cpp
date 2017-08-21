//
//  typedTests.cpp
//  TypedTests
//
//  Created by Jonathan Ginsburg on 8/21/17.
//  Copyright © 2017 Jonathan Ginsburg. All rights reserved.
//

#define VECTOR_SIZE 1000

#include "gtest/gtest.h"
#include "Sorters.cpp"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

template <typename T>
class SortTester : public ::testing::Test {
public:
    std::vector<int> unsortedVector;
    T sorter;
    void SetUp() {
        std::srand((unsigned int)std::time(0));
        for (int i = 0; i < VECTOR_SIZE; ++i) {
            unsortedVector.push_back(std::rand());
        }
    }
};

typedef ::testing::Types<Merge, Insertion, Bubble> types;
TYPED_TEST_CASE(SortTester, types);

TYPED_TEST(SortTester, correctness) {
    std::vector<int> sortedVector = this->sorter.sort(this->unsortedVector);
    ASSERT_EQ(this->unsortedVector.size(), sortedVector.size()) << "Sizes of sorted and unsorted vector differ.";
    for (int i = 0; i < sortedVector.size() - 1; ++i) {
        ASSERT_LE(sortedVector[i], sortedVector[i + 1]);
    }
}
