//
//  main.cpp
//  TypedTests
//
//  Created by Jonathan Ginsburg on 8/21/17.
//  Copyright © 2017 Jonathan Ginsburg. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
