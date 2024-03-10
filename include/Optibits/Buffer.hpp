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

    /// @brief Creates a Buffer. The purger will be called when freed or re-assigned
    /// @param buffer 
    /// @param size 
    /// @param purger 
    Buffer(void* buffer, std::size_t size, std::function<void(void*)> purger);
    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;
    ~Buffer();

    /// @brief Creates a new Buffer by allocating memory. Memory is not initialized.
    /// @param size 
    explicit Buffer(std::size_t size);

    /// @brief Takes ownership of the given vector.
    /// @param vector 
    explicit Buffer(std::vector<std::uint8_t>&& vector) noexcept; 

    /// @brief  Makes a copy of the given buffer.
    /// @param other 
    Buffer(const Buffer& other);

    /// @brief Makes a copy of the given buffer.
    /// @param other 
    /// @return 
    Buffer& operator=(const Buffer& other);

    /// @brief Drops the members of the buffer. (Basically resets them)
    void drop();

    const std::uint8_t* data() const { return static_cast<const std::uint8_t*>(m_buffer); }
    std::uint8_t* data() { return static_cast<std::uint8_t*>(m_buffer); }
    std::size_t size() const { return m_size; }
  };

  /// @brief Loads a whole file into a buffer.
  /// @param filename 
  /// @return 
  Buffer load_file(const std::string& filename);

  /// @brief Creates or overwrites a file with the contents of a buffer.
  /// @param buffer 
  /// @param filename 
  void save_file(const Buffer& buffer, const std::string& filename);
  
}
