#include "utf8.h"

#ifdef OPTI_WINDOWS

namespace opti
{

  std::string to_utf8(LPCWSTR wstr) {
    size_t wideLen = wslen(wstr) + 1;

    // get size in UTF-8
    int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wstr, wideLen, 0, 0, 0, 0);

    char *utf8Str = new char[utf8Size];

    int ok = WideCharToMultiByte(CP_UTF8, 0, wstr, wide_len, utf8_str, utf8_size, 0, 0);

    std::string ret;
    if (ok)
      ret = utf8_str;

    delete[] utf8_str;
    return ret;
  }

  std::wstring to_widestr(const std::string &str)
  {
    if (str.empty())
      return std::wstring();

    int wide_size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int) str.length(), nullptr, 0);

    if (wide_size == 0)
      return std::wstring();

    std::wstring widestr;
    widestr.resize(wide_size);

    int ok = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int) str.length(), &widestr[0], widestr.length());

    if (!ok)
      return std::wstring();

    return widestr;
  }

  void replace_char(std::string &str, char find, char replace)
  {
    int length = str.length();

    for (int i = 0; i<length; i++)
    {
      if (str[i] == find)
        str[i] = replace;
    }
  }
}

#endif
