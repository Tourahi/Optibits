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
    std::function<void(void*)> m_purger;

  public:

    Buffer() = default;

    Buffer(void* buffer, std::size_t size, std::function<void(void*)> purger);
    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;
    ~Buffer();

    explicit Buffer(std::size_t size);
    explicit Buffer(std::vector<std::uint8_t>&& vector) noexcept; 

    Buffer(const Buffer& other);
    Buffer& operator=(const Buffer& other);

    void drop();
    const std::uint8_t* data() const { return static_cast<const std::uint8_t*>(m_buffer); }
    std::uint8_t* data() { return static_cast<std::uint8_t*>(m_buffer); }
    std::size_t size() const { return m_size; }
  };

  Buffer load_file(const std::string& filename);

  void save_file(const Buffer& buffer, const std::string& filename);
  
}
