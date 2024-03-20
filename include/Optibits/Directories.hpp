#pragma once

#include <string>

namespace Optibits
{

  void useResourceDir();

  std::string resourcePath(const std::string& relativeFileName = "");

  std::string userSettingsPath(const std::string& org, const std::string& app, const std::string& relativeFileName = "");
  
}