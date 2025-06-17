
#include "common/config.h"
#include "Exception.h"

namespace opti
{

  Exception::Exception(const char *fmt, ...)
  {
    va_list args;
    int size_buffer = 256, size_out;
    char *buffer;

    while (true)
    {
      buffer = new char[size_buffer];
      memset(buffer, 0, size_buffer);

      va_start(args, fmt);
      size_out = vsnprintf(buffer, size_buffer, fmt, args);
      va_end(args);

      if (size_out == size_buffer || size_out == -1 || size_out == size_buffer-1)
        size_buffer *= 2;
      else if (size_out > size_buffer)
        size_buffer = size_out + 2;
      else
        break;

      delete[] buffer;
    }
    message = std::string(buffer);
    delete[] buffer;
  }

  Exception::~Exception() throw()
  {

  }

}
