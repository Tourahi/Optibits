#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>


namespace Optibits
{

  class Buffer
  {
    void* m_buffer;
    std::size_t m_size;
    std::function<void(void*)> m_purge;

  public:

    Buffer() = default;

    Buffer(void* buffer, std::size_t size, std::function<void(void*)> purger);

  };
}
