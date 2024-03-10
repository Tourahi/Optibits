#include <gtest/gtest.h>

#include <Optibits/Utility.hpp>

class UtilityTests : public testing::Test
{
};

TEST_F(UtilityTests, has_extension)
{
  ASSERT_TRUE(Optibits::has_extension("filename.bmp", ".bmp"));
}


TEST_F(UtilityTests, user_languages)
{
  for (const std::string& lang : Optibits::user_languages()) {
    ASSERT_GE(lang.length(), 2);
  }
}

