#ifndef OPTI_EXCEPTION_H
#define OPTI_EXCEPTION_H

#include <exception>
#include <cstdarg> // vararg
#include <cstdio> // vsnprintf
#include <cstring> // strncpy
#include <string>


namespace opti
{
  class Exception : public std::exception
  {
    public:
      // See: http://www.cplusplus.com/reference/clibrary/cstdio/printf/
      Exception(const char *fmt, ...);
      virtual ~Exception() throw();

      /**
       * Returns a string containing reason for the exception.
       * @return A description of the exception.
       **/
      inline virtual const char *what() const throw()
      {
        return message.c_str();
      }

    private:

      std::string message;

  };
}

#endif
