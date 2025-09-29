//
// Created by mimir on 25/09/25.
//

#include "config.h";

#ifdef OPTI_WINDOWS

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


namespace opti
{

    /**
     * Convert the wide string to a UTF-8 encoded string.
     * @param wstr The wide-char string.
     * @return A UTF-8 string.
     **/
    std::string to_utf8(LPCWSTR wstr);

    /**
     * Convert a UTF-8 encoded string to a wide string.
     * @param str The UTF-8 string.
     * @return A wide string.
     **/
    std::wstring to_widestr(const std::string &str);


    /**
     * Replace all occurences of 'find' with 'replace' in a string.
     * @param str The string to modify.
     * @param find The character to match.
     * @param replace The character to replace matches.
     **/
    void replace_char(std::string &str, char find, char replace);

}



#endif
