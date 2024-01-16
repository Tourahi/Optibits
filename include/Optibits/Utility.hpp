#pragma once

#include <Optibits/Platform.hpp>
#include <string>
#include <string_view>
#include <vector>

namespace Optibits
{

  bool has_extension(std::string_view filename, std::string_view ext);

  std::vector<std::string> user_languages();

}