#include <Optibits/Buffer.hpp>

#include <limits>
#include <memory>
#include <stdexcept>

#include <SDL.h>


Optibits::Buffer::Buffer(void* buffer, std::size_t size, std::function<void(void*)> purger)
  : m_buffer(buffer),
    m_size(size),
    m_purge(purger)
{
  if (buffer == nullptr && size > 0) {
    throw std::invalid_argument("Tried to create non-empty Optibits::Buffer from nullptr");
  }
  if (size >= std::numeric_limits<std::ptrdiff_t>::max()) {
    throw std::invalid_argument("Tried to create Optibits::Buffer with negative size");
  } 
}
