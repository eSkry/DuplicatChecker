#ifndef TST_DUPLICATFINDER_H
#define TST_DUPLICATFINDER_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "duplicatchechertestclass.h"

TEST(DuplicatCountCheck_1, test_eq) {
    DuplicatChecherTestClass dt("../TestEnv", "../TestEnv/dir1", 0);
    dt.runTest();
    ASSERT_EQ(dt.getCountDuplicates(), 2);
}

TEST(DuplicatCountCheck_2, test_eq) {
    DuplicatChecherTestClass dt("../TestEnv", "../TestEnv", 0);
    dt.runTest();
    ASSERT_EQ(dt.getCountDuplicates(), 4);
}

TEST(DuplicatCountCheck_3, test_eq) {
    DuplicatChecherTestClass dt("../TestEnv", "../TestEnv", 10);
    dt.runTest();
    ASSERT_EQ(dt.getCountDuplicates(), 0);
}


#endif // TST_DUPLICATFINDER_H
