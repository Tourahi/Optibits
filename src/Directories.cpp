#include <Optibits/Directories.hpp>
#include <Optibits/Platform.hpp>

#ifdef OPTIBITS_WIN
#include <Optibits/Utility.hpp>
#include <windows.h>
#else
#include <unistd.h>
#endif




#ifndef OPTIBITS_IPHONE
#include <SDL.h>
#include <memory>
#include <stdexcept>
#endif

#ifndef OPTIBITS_IPHONE

std::string resourcePath(const std::string& relativeFileName)
{
  static const char* resourcePrefix = SDL_GetBasePath();
  return relativeFileName.empty() ? resourcePrefix : resourcePrefix + relativeFileName;
}

std::string userSettingsPath(const std::string& org, const std::string& app, const std::string& relativeFileName)
{
  char* settingsPrefix = SDL_GetPrefPath(org.c_str(), app.c_str());

  if (!settingsPrefix) {
    throw std::runtime_error("Could not create settings directory : " + std::string(SDL_GetError()));
  }

  const std::unique_ptr<char, decltype(&SDL_free)> guard(settingsPrefix, &SDL_free);
  return relativeFileName.empty() ? settingsPrefix : settingsPrefix + relativeFileName;
}
#endif


void useResourceDir()
{
// #ifdef OPTIBITS_WIN
//   SetCurrentDirectoryW(utf8_to_utf16(resourcePath()).c_str());
// #else
//   chdir(resourcePath().c_str());
// #endif
}