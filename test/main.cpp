#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include "gtest/gtest.h"
  using ::testing::Test;
#include "../src/Chip8Emulator/CPU.h"

namespace testing
{
    class SomeTest : public Test
    {
    protected:
        SomeTest(){}
        ~SomeTest(){}

        virtual void SetUp(){}
        virtual void TearDown(){}
    };



    TEST_F(SomeTest, constructor_createsEmptyList)
    {
        EXPECT_THAT("hello", Eq("hello"));
    }

} // namespace testing