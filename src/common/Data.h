#ifndef OPTI_DATA_H
#define OPTI_DATA_H


// Opti
#include "Knot.h"

// C
#include <stddef.h>
#include <mutex>

namespace opti
{
  namespace thread
  {
    class Mutex;
  }

  /**
   * This class is a simple abstraction over all objects which contain data.
   **/
  class Data : public Knot
  {
    public:
      static opti::Type type;

      Data() {};
      virtual ~Data();

      /**
      * Creates a duplicate of Data derived class instance.
      **/
      virtual Data *clone() const = 0;

      /**
       * Gets a pointer to the data. This pointer will obviously not
       * be valid if the Data object is destroyed.
       **/
      virtual void *getData() const = 0;

      /**
       * Gets the size of the Data in bytes.
       **/
      virtual size_t getSize() const = 0;

      /**
       * Gets the Mutex associated with this Data object. Creates it in a thread-
       * safe manner if necessary.
       **/
      opti::thread::Mutex *getMutex();

    private:
      opti::thread::Mutex *mutex = nullptr;
      std::once_flag mutexCreated;
  };
}

#endif
