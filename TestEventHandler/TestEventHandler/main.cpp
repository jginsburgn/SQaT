//
//  main.cpp
//  TestEventHandler
//
//  Created by Jonathan Ginsburg on 8/27/17.
//  Copyright © 2017 Jonathan Ginsburg. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "gtest/gtest.h"

class TestEventHandler : public ::testing::TestEventListener {
private:
    std::ofstream logFile;
public:
    TestEventHandler() {
        logFile.open("log.txt");
    };
    ~TestEventHandler() override {
        logFile.close();
    };
    
    // Fired before any test activity starts.
    void OnTestProgramStart(const ::testing::UnitTest& unit_test) override {
        logFile << "Test program has started." << std::endl;
    };
    
    // Fired before each iteration of tests starts.  There may be more than
    // one iteration if GTEST_FLAG(repeat) is set. iteration is the iteration
    // index, starting from 0.
    void OnTestIterationStart(const ::testing::UnitTest& unit_test,
                              int iteration) override {
        logFile << "Test iteration number " << iteration << " has started." << std::endl;
    };
    
    // Fired before environment set-up for each iteration of tests starts.
    void OnEnvironmentsSetUpStart(const ::testing::UnitTest& unit_test) override {
        logFile << "Environment setup has started." << std::endl;
    };
    
    // Fired after environment set-up for each iteration of tests ends.
    void OnEnvironmentsSetUpEnd(const ::testing::UnitTest& unit_test) override {
        logFile << "Environment setup has ended." << std::endl;
    };
    
    // Fired before the test case starts.
    void OnTestCaseStart(const ::testing::TestCase& test_case) override {
        logFile << "Test case started; named: " << test_case.name() << std::endl;
    };
    
    // Fired before the test starts.
    void OnTestStart(const ::testing::TestInfo& test_info) override {
        logFile << ">> Test method started; named: " << test_info.name() << std::endl;
    };
    
    // Fired after a failed assertion or a SUCCEED() invocation.
    void OnTestPartResult(const ::testing::TestPartResult& test_part_result) override {
        if (test_part_result.failed()) {
            logFile << "Test failed. Summary:\n" << test_part_result.summary() << std::endl;
        }
        else {
            logFile << "Test succeeded. Summary:\n" << test_part_result.summary() << std::endl;
        }
    };
    
    // Fired after the test ends.
    void OnTestEnd(const ::testing::TestInfo& test_info) override {
        logFile << "<< Test method ended; named: " << test_info.name() << std::endl;
    };
    
    // Fired after the test case ends.
    void OnTestCaseEnd(const ::testing::TestCase& test_case) override {
        logFile << "Test case ended; named: " << test_case.name() << std::endl;
    };
    
    // Fired before environment tear-down for each iteration of tests starts.
    void OnEnvironmentsTearDownStart(const ::testing::UnitTest& unit_test) override {
        logFile << "Environment teardown has ended." << std::endl;
    };
    
    // Fired after environment tear-down for each iteration of tests ends.
    void OnEnvironmentsTearDownEnd(const ::testing::UnitTest& unit_test) override {
        logFile << "Environment teardown has ended." << std::endl;
    };
    
    // Fired after each iteration of tests finishes.
    void OnTestIterationEnd(const ::testing::UnitTest& unit_test, int iteration) override {
        logFile << "Test iteration number " << iteration << " has ended." << std::endl;
    };
    
    // Fired after all test activities have ended.
    void OnTestProgramEnd(const ::testing::UnitTest& unit_test) override {
        logFile << "Test program has ended." << std::endl;
        logFile << "Total tests: " << unit_test.total_test_count() << std::endl;
        logFile << "Succeeded: " << unit_test.successful_test_count() << std::endl;
        logFile << "Failed: " << unit_test.failed_test_count() << std::endl;
    };
};

TEST(FirstDummyTestCase, SucceedTest) {
    SUCCEED();
}

TEST(FirstDummyTestCase, FailTest) {
    FAIL();
}

TEST(SecondDummyTestCase, AssertSuccess) {
    ASSERT_TRUE(true);
}

TEST(SecondDummyTestCase, AssertFail) {
    ASSERT_TRUE(false);
}

TEST(ThirdDummyTestCase, ExpectSuccess) {
    ASSERT_TRUE(true);
}

TEST(ThirdDummyTestCase, ExpectFail) {
    ASSERT_TRUE(false);
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    // Gets hold of the event listener list.
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    // Release and delete default listener.
    delete listeners.Release(listeners.default_result_printer());
    // Adds a listener to the end.  Google Test takes the ownership.
    listeners.Append(new TestEventHandler);
    return RUN_ALL_TESTS();
}
