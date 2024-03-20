#include <Optibits/Platform.hpp>
#if defined(OPTIBITS_WIN)

#include <Optibits/Utility.hpp>
#include <stdexcept>
#include <windows.h>


std::wstring utf8ToUtf16(const std::string& utf8)
{
  if (utf8.empty()) {
    return std::wstring();
  }

  std::wstring utf16(utf8.size(), '\0');
  int result = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8.data(), utf8.size(), utf16.data(), utf16.size());

  if (result == 0) {
    throw std::runtime_error("Could not convert UTF-8 to UTF-16, GetLastError() = " + std::to_string(GetLastError()));
  }

  utf16.resize(result);
  return utf16;
}

std::string utf16ToUtf8(const std::string& utf16)
{
  if (utf16.empty()) {
    return std::wstring();
  }

  int result = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), utf16.size(), nullptr, 0, nullptr, nullptr);

  if (result == 0) {
    throw std::runtime_error("Could not convert UTF-16 to UTF-8, GetLastError() = " + std::to_string(GetLastError()));
  }

  std::string utf8(result, '\0');
  WideCharToMultiByte(CP_UTF8, MB_ERR_INVALID_CHARS, utf16.c_str(), utf16.size(), utf8.data(), utf8.size(), nullptr, nullptr);
  return utf8;

}

#endif
