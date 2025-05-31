#include "config.h"
#include "memory.h"


#include <stdlib.h>


#ifdef OPTI_WINDOWS
# include <malloc.h>
# include <Windows.h>
#else
# include <unistd.h> // Assume POSIX support.
#endif


namespace opti
{

  bool alignedMalloc(void **mem, size_t size, size_t alignment)
  {
#ifdef OPTI_WINDOWS
    *mem = _aligned_malloc(size, alignment);
    return mem != nullptr;
#else
    return posix_memalign(mem, alignment, size) == 0;
#endif
  }

  void alignedFree(void *mem)
  {
#ifdef OPTI_WINDOWS
    _aligned_free(mem);
#else
    free(mem);
#endif
  }

  size_t getPageSize()
  {
#ifdef OPTI_WINDOWS
    static DWORD size = 0;
    if (size == 0)
    {
      SYSTEM_INFO si;
      GetSystemInfo(&si);
      size = si.dwPageSize;
    }

    return (size_t) size;
#else
    static const long size = sysconf(_SC_PAGESIZE);
	return size > 0 ? (size_t) size : 4096;
#endif
  }

  size_t alignUp(size_t size, size_t alignment)
  {
    return (size + alignment - 1) & (~(alignment - 1));
  }

} // opti
