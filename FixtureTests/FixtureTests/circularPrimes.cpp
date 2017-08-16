//
//  circularPrimes.cpp
//  FixtureTests
//
//  Created by Jonathan Ginsburg on 8/15/17.
//  Copyright © 2017 Jonathan Ginsburg. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>

bool isPrime(unsigned int n) {
    if (n < 2)
        return false;
    for (int i = 2; i*i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

bool isCircularPrime(unsigned int value) {
    unsigned long max = std::to_string(value).size() - 1;
    for (int i = 0; i <= max; ++i) {
        if (!isPrime(value)) {
            return false;
        }
        value = (value % 10) * (int)pow(10, max) + value / 10;
    }
    return true;
}

