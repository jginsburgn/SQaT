//
//  fixtureTests.cpp
//  FixtureTests
//
//  Created by Jonathan Ginsburg on 8/15/17.
//  Copyright © 2017 Jonathan Ginsburg. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include "gtest/gtest.h"
#include "circularPrimes.cpp"
#include <algorithm>

class CircularPrimeTester : public ::testing::Test {
private:
    std::vector<std::string> getDecimalPermutationsRecursive(std::string strVal) {
        if (strVal.size() == 1) {
            return std::vector<std::string>{strVal};
        }
        else {
            char permuteCharacter = strVal[0];
            std::vector<std::string> retVal;
            std::vector<std::string> subResult = getDecimalPermutationsRecursive(strVal.substr(1));
            for (std::vector<std::string>::iterator it = subResult.begin(); it != subResult.end(); it++) {
                std::string currentString = *it;
                for (int i = 0; i < currentString.size() + 1; ++i) {
                    std::string newElement(currentString);
                    newElement.insert(i, std::string(1, permuteCharacter));
                    retVal.push_back(newElement);
                }
            }
            return retVal;
        }
    }
    std::vector<int> getDecimalPermutations(unsigned int value) {
        std::string strValue = std::to_string(value);
        std::vector<std::string> permutationStrings = getDecimalPermutationsRecursive(strValue);
        std::vector<int> permutations;
        for (std::vector<std::string>::iterator it = permutationStrings.begin(); it != permutationStrings.end(); it++) {
            permutations.push_back(std::stoi(*it));
        }
        return permutations;
    }
    std::vector<unsigned int> getDecimalRotations(unsigned int value) {
        std::vector<unsigned int> retVal;
        std::string strValue = std::to_string(value);
        for (int i = 0; i < strValue.size(); ++i) {
            value = (value % 10) * pow(10, strValue.size() - 1) + value / 10;
            retVal.push_back(value);
        }
        return retVal;
    }
public:
    std::vector<unsigned int> knownCircularPrimes;
    std::vector<unsigned int> knownPrimesLessThan900 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887};
    void SetUp() {
        std::vector<unsigned int> smallestRepresentativeKnownCircularPrimes = {2, 3, 5, 7, 11, 13, 17, 37, 79, 113, 197, 199, 337, 1193, 3779, 11939, 19937, 193939, 199933};
        for (std::vector<unsigned int>::iterator it = smallestRepresentativeKnownCircularPrimes.begin(); it != smallestRepresentativeKnownCircularPrimes.end(); ++it) {
            std::vector<unsigned int> rotations = getDecimalRotations(*it);
            knownCircularPrimes.insert(knownCircularPrimes.end(), rotations.begin(), rotations.end());
        }
    }
    void TearDown() {
        
    }
    bool isKnownCircularPrime(unsigned int value) {
        return std::find(this->knownCircularPrimes.begin(), this->knownCircularPrimes.end(), value) != this->knownCircularPrimes.end();
    }
};

TEST_F(CircularPrimeTester, TestKnownsCircular) {
    for (std::vector<unsigned int>::iterator it = this->knownCircularPrimes.begin(); it != this->knownCircularPrimes.end(); ++it) {
        ASSERT_TRUE(isCircularPrime(*it)) << "Tested value: " << *it;
    }
}

TEST_F(CircularPrimeTester, TestPositivesCircular) {
    for (unsigned int i = 0; i < 5000000; ++i) {
        ASSERT_EQ(isKnownCircularPrime(i), isCircularPrime(i)) << "Tested value: " << i;
        ++i;
    }
}

TEST_F(CircularPrimeTester, TestKnownsRegular) {
    for (std::vector<unsigned int>::iterator it = knownPrimesLessThan900.begin(); it != knownPrimesLessThan900.end(); ++it) {
        ASSERT_TRUE(isPrime(*it));
    }
}

TEST_F(CircularPrimeTester, TestPositivesRegular) {
    for (unsigned int i = 0; i < 900; ++i) {
        if (std::find(this->knownPrimesLessThan900.begin(), this->knownPrimesLessThan900.end(), i) != this->knownPrimesLessThan900.end()) {
            continue;
        }
        ASSERT_FALSE(isPrime(i));
    }
}
