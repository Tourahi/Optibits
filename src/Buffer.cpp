#include <Optibits/Buffer.hpp>
#include <limits>
#include <memory>
#include <stdexcept>

#include <SDL.h>


void Optibits::Buffer::drop()
{
  m_buffer = nullptr;
  m_size = 0;
  m_buffer = nullptr;
}

Optibits::Buffer::Buffer(void* buffer, std::size_t size, std::function<void(void*)> purger)
  : m_buffer(buffer),
    m_size(size),
    m_purger(purger)
{
  if (buffer == nullptr && size > 0) {
    throw std::invalid_argument("Tried to create non-empty Optibits::Buffer from nullptr");
  }
  if (size >= std::numeric_limits<std::ptrdiff_t>::max()) {
    throw std::length_error("Tried to create Optibits::Buffer with negative size");
  }
}

Optibits::Buffer::Buffer(Optibits::Buffer&& other) noexcept
  : m_buffer(nullptr),
    m_size(0),
    m_purger(nullptr)
{
  *this = std::move(other); /// Allow efficient transfer 
}

Optibits::Buffer& Optibits::Buffer::operator=(Optibits::Buffer&& other) noexcept
{

  if (this == &other) {
    return *this;
  }

  if (m_buffer && m_purger) {
    m_purger(m_buffer);
  }

  m_buffer = other.m_buffer;
  m_size = other.m_size;
  m_purger = std::move(other.m_purger);

  other.drop();

  return *this;
}

Optibits::Buffer::~Buffer() {
  if (m_buffer && m_purger) {
    m_purger(m_buffer);
  }
}

Optibits::Buffer::Buffer(std::size_t size)
  : m_buffer(nullptr),
    m_size(size),
    m_purger([](auto* p) { delete[] static_cast<std::uint8_t*>(p); })
{
  if (size >= std::numeric_limits<std::ptrdiff_t>::max()) {
    throw std::length_error("Tried creating Optibitx::Buffer with a negative size.");
  }

  if (m_size) {
    m_buffer = new std::uint8_t[m_size];
  }
}

Optibits::Buffer::Buffer(std::vector<std::uint8_t>&& vector) noexcept
  : m_buffer(vector.data()),
    m_size(vector.size()),
    m_purger([vec = std::move(vector)](void*) mutable { vec.clear(); })
{
}

Optibits::Buffer::Buffer(const Optibits::Buffer& other)
  : Buffer(std::vector<std::uint8_t>(other.data(), other.data() + other.size()))
{
}

Optibits::Buffer& Optibits::Buffer::operator=(const Optibits::Buffer& other)
{
  if (this == &other) {
    return *this;
  }

  return *this = Buffer(other);
}

#ifdef OPTIBITS_IPHONE
  // TODO
#else
Optibits::Buffer Optibits::load_file(const std::string& filename)
{
  std::size_t size = 0;
  void* contents = SDL_LoadFile(filename.c_str(), &size);
  if (contents == nullptr) {
    throw std::runtime_error("Could not read '" + filename + "', error: " + SDL_GetError());
  }
  return Buffer(contents, size, &SDL_free);
}

void Optibits::save_file(const Buffer& buffer, const std::string& filename)
{
  struct RWopsDeleter
    {
      void operator()(SDL_RWops* p) const
      {
        if (p) {
            SDL_RWclose(p);
        }
      }
    };

  std::unique_ptr<SDL_RWops, RWopsDeleter> rwops(SDL_RWFromFile(filename.c_str(), "w"));
  if (rwops == nullptr) {
    throw std::runtime_error("Could not open '" + filename + "', error: " + SDL_GetError());
  } 
  std::size_t written = SDL_RWwrite(rwops.get(), buffer.data(), buffer.size(), 1);

  if (written == 0) {
    throw std::runtime_error("Could not write to '" + filename + "', error: " + SDL_GetError());
  }
}


#endif