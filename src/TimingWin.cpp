#include <Optibits/Platform.hpp>
#if defined(OPTIBITS_WIN)

#include <Optibits/Timing.hpp>
#include <windows.h>

void Optibits::sleep(unsigned millisecs)
{
  usleep(millisecs * 1000);
}

unsigned long Optibits::milliseconds()
{
  static const unsigned long start = [] {
    timeBeginPeriod(1);
    return timeGetTime();
  }();
  return timeGetTime() - start;
}

#endif