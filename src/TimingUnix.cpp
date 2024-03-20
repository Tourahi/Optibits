#include <Optibits/Platform.hpp>
#if defined(OPTIBITS_UNIX)

#include <Optibits/Timing.hpp>
#include <sys/time.h>
#include <unistd.h>

void Optibits::sleep(unsigned millisecs)
{
  usleep(millisecs * 1000);
}

unsigned long Optibits::milliseconds()
{
  timeval tp;
  gettimeofday(&tp, nullptr);
  unsigned long ms = tp.tv_usec / 1000UL + tp.tv_sec * 1000UL;

  static unsigned long start = ms;
  return ms - start;
}


#endif