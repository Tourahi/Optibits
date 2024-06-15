#pragma once



#include <exception>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>



namespace Optibits 
{

  class Exception : public std::exception
  {

  public:

    Exception(const char *fmt, ...);
    virtual ~Exception() throw();

    inline virtual const char *why() const throw()
    {
      return msg.c_str();
    }

  private:

    std::string msg;

  };


}