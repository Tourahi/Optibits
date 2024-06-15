

#include <Exception.h>
#include <cstdio>


namespace Optibits
{


  Exception::Exception(const char *fmt, ...)
  {

    va_list args;
    int sizeBuffer = 256, sizeOut;
    char *buffer;

    while(true)
    {

      buffer = new char[sizeBuffer];
      memset(buffer, 0, sizeBuffer);

      va_start(args, fmt);
      sizeOut = vsnprintf(buffer, sizeBuffer, fmt, args);
      va_end(args);

      if (sizeOut == sizeBuffer || sizeOut == -1 || sizeOut == sizeBuffer-1)
       sizeBuffer *= 2;
      else if (sizeOut > sizeBuffer)
        sizeBuffer = sizeOut + 2;
      else
        break;

      delete[] buffer;
    }

    msg = std::string(buffer);
    delete[] buffer;

  }


  Exception::~Exception() throw()
  {
  }

}

