#include <gtest/gtest.h>

#include <Optibits/Input.hpp>
#include <Optibits/common/Exception.hpp>
#include <Optibits/Keyboard.hpp>
#include <cstring>
#include <filesystem>
#include <iostream>


#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

class InputTests : public testing::Test
{
};


TEST_F(InputTests, id_to_char)
{
  std::string key = Optibits::Input::idToChar(Optibits::KEY_1);
  std::string key1 = Optibits::Input::idToChar(Optibits::KEY_SPACE);

  ASSERT_EQ(key, "1");
  ASSERT_EQ(key1, " ");
}