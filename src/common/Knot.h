
#ifndef OPTI_KNOT_H
#define OPTI_KNOT_H

#include <atomic>
#include "types.h"

namespace opti
{
   /**
    * Superclass of all objects
    * Named Knot as a reference to the Weavers in the all souls ;)
    * Hopping to one day grasp and master all the knots of gamedev
    **/
  class Knot
  {
    public:

      static opti::Type type;

      Knot();
      Knot(const Knot &other);

      virtual ~Knot() = 0;

      int getReferenceCount() const;

      /**
       * Tie the knot i.e. increases the
       * reference count by one.
       **/
      void tie();

      /**
       * Releases one reference to the Knot i.e. decrements the
       * reference count by one, and potentially deletes the Object
	   * if there are no more references.
       **/
      void release();

    private:
      std::atomic<int> count;
  }; // Knot

  struct Proxy
  {
    // Holds type information
    opti::Type *type;

    // Pointer to the actual knot
    Knot *knot;
  };

  enum Acquire
  {
    RETAIN,
    NORETAIN,
  };

  template <typename T>
  class StrongRef
  {
    public:
      StrongRef(T *knot, Acquire acquire = Acquire::RETAIN)
        : knot(knot)
      {
        if (knot && acquire == Acquire::RETAIN) knot->tie();
      }

      StrongRef(const StrongRef &other)
        : knot(other.get())
      {
        if (knot) knot->tie();
      }

      StrongRef(StrongRef &&other)
        : knot(other.knot)
      {
        other.knot = nullptr;
      }

      ~StrongRef()
      {
        if (knot) knot->release();
      }

      void set(T *knt, Acquire acquire = Acquire::RETAIN)
      {
        if (knt && acquire == Acquire::RETAIN) knt->retain();
        if (knot) knot->release();
        knot = knt;
      }

      T *get() const
      {
        return knot;
      }

      StrongRef &operator = (const StrongRef &other)
      {
        set(other.get());
        return *this;
      }

      T *operator->() const
      {
        return knot;
      }

      explicit operator bool() const
      {
        return knot != nullptr;
      }

      operator T*() const
      {
        return knot;
      }

    private:

      T *knot;
  };


}



#endif
