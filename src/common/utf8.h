//
// Created by mimir on 25/09/25.
//

#include "config.h";

#ifdef OPTI_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


namespace opti
{

    std::string to_utf8(LPCWSTR wstr);

    std::wstring to_widestr(const std::string &str);

    void replace_char(std::string &str, char find, char replace);

}



#endif
