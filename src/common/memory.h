
#ifndef OPTI_MEMORY_H
#define OPTI_MEMORY_H


#include <stddef.h>

namespace opti
{

  bool alignedMalloc(void **mem, size_t size, size_t alignment);
  void alignedFree(void *mem);

  size_t getPageSize();

  // alignment must be *2
  // see notes: https://en.cppreference.com/w/c/memory/aligned_alloc
  size_t alignUp(size_t size, size_t alignment);

}




#endif
