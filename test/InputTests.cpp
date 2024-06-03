#include <gtest/gtest.h>

#include <Optibits/Input.hpp>
#include <Optibits/Keyboard.hpp>
#include <cstring>
#include <filesystem>
#include <iostream>


#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

class InputTests : public testing::Test
{
};


TEST_F(InputTests, from_existing_memory)
{
  std::string key = Optibits::Input::idToChar(Optibits::KEY_1);

  GTEST_COUT << key << "\n";

  ASSERT_EQ(key, "2");
}