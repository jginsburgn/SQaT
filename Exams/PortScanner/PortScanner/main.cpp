//
//  main.cpp
//  PortScanner
//
//  Created by Jonathan Ginsburg on 8/25/17.
//  Copyright © 2017 Jonathan Ginsburg. All rights reserved.
//

#include "PortScanner.cpp"
#include "gtest/gtest.h"

std::vector<std::string> inputPorts;
class TestGlobals {
public:
    static std::vector<std::string> * GetInputPorts () {return &inputPorts;}
};

class TestEventHandler : public ::testing::EmptyTestEventListener {
    void OnTestProgramEnd(const ::testing::UnitTest& unit_test) {
        ASSERT_EQ(0, PortScanner::_referenceCount) << "Memory leak(s).";
    }
};

class PositivesParametrizedTester : public ::testing::TestWithParam<std::string> {};
const std::vector<std::string> positives = {"4370", "4380", "4381", "4371", "57621", "52808"};
INSTANTIATE_TEST_CASE_P(RangeTest, PositivesParametrizedTester, ::testing::ValuesIn(positives));
TEST_P(PositivesParametrizedTester, RangePositives) {
    std::string portToTest = GetParam();
    PortScanner * ps = new PortScanner;
    EXPECT_TRUE(ps->isUsedPort(portToTest)) << "Port [" << portToTest << "] is expected to be open, although reported as closed.";
    delete ps;
}

class NegativesParametrizedTester : public ::testing::TestWithParam<std::string> {};
const std::vector<std::string> negatives = {"4370", "4380", "4381", "4371", "57621", "52808"};
INSTANTIATE_TEST_CASE_P(RangeTest, NegativesParametrizedTester, ::testing::ValuesIn(negatives));
TEST_P(NegativesParametrizedTester, RangeNegatives) {
    std::string portToTest = GetParam();
    PortScanner * ps = new PortScanner;
    EXPECT_FALSE(ps->isUsedPort(portToTest)) << "Port [" << portToTest << "] is expected to be closed, although reported as open.";
    delete ps;
}

TEST(InputPortTester, ArgumentsFromInput) {
    PortScanner * ps = new PortScanner();
    for (std::vector<std::string>::iterator it = inputPorts.begin(); it != inputPorts.end(); ++it) {
        EXPECT_TRUE(ps->isUsedPort(*it)) << "Port [" << *it << "] is expected to be open, although reported as closed.";
    }
    delete ps;
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) != "-v") {
            TestGlobals::GetInputPorts()->push_back(argv[i]);
        }
    }
    TestGlobals::GetInputPorts()->erase(TestGlobals::GetInputPorts()->begin()); //Remove first argument, which is the full path to the executable.
    // Gets hold of the event listener list.
    ::testing::TestEventListeners& listeners =
    ::testing::UnitTest::GetInstance()->listeners();
    // Adds a listener to the end.  Google Test takes the ownership.
    listeners.Append(new TestEventHandler);
    return RUN_ALL_TESTS();
}
