#include <Optibits/Platform.hpp>
#if defined(OPTIBITS_MAC)

#include <Optibits/Timing.hpp>
#include <unistd.h>

void Optibits::sleep(unsigned millisecs)
{
  usleep(millisecs * 1000);
}

#include <mach/mach_time.h>

unsigned long Optibits::milliseconds()
{
  static mach_timebase_info_data_t info;
  static const uint64_t first_tick = [] {
    mach_timebase_info(&info);
    return mach_absolute_time();
  }();

  uint64_t runtime = mach_absolute_time() - first_tick;
  return runtime * info.numer / info.denom / 1'000'000;
}

#endif