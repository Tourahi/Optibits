#pragma once

#if defined(WIN32) || define(WIN64)
# define OPTIBITS_WIN
#else
# define OPTIBITS_UNIX
# if defined(__linux) || defined(__FreeBSD__)
# define OPTIBITS_X
# else
#  define OPTIBITS_MAC
#  include <TargetConditionals.h>
#  if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#   define OPTIBITS_IPHONE
#   define OPTIBITS_OPENGLES
#  endif
# endif
#endif


#ifndef OPTIBITS_DEPRECATED
/// https://en.cppreference.com/w/cpp/language/attributes/deprecated
# define OPTIBITS_DEPRECATED [[deprecated]]
#endif