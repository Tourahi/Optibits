
#ifndef OPTI_THREAD_THREADS_H
#define OPTI_THREAD_THREADS_H

#include "common/config.h"
#include "Thread.h"

// C++
#include <string>

#include "common/Knot.h"

namespace opti {
  namespace thread {
    class Mutex {
    public:
      virtual ~Mutex() {};
      virtual void lock() = 0;
      virtual void unlock() = 0;
    };

    class Conditional {
    public:
      virtual ~Conditional() {}
      virtual void signal() = 0;
      virtual void broadcast() = 0;
      virtual bool wait(Mutex *mutex, int timeout=-1) = 0;
    };

    class Lock {
    public:
      Lock(Mutex *m);
      Lock(Mutex &m);
      Lock(Lock &&other);
      ~Lock();
    private:
      Mutex *mutex;
    };

    class EmptyLock
    {
    public:
      EmptyLock();
      ~EmptyLock();

      void setLock(Mutex *m);
      void setLock(Mutex &m);

    private:
      Mutex *mutex;
    };

    class Threadable : public opti::Knot {
    public:
      static opti::Type type;

      Threadable();
      virtual ~Threadable();

      virtual void threadFunction() = 0;

      bool start();
      void wait();
      bool isRunning() const;
      const char *getThreadName() const;

    protected:

      Thread *owner;
      std::string threadName;

    };

    class MutexRef {
      MutexRef();
      ~MutexRef();

      operator Mutex*() const;
      Mutex *operator->() const;

    private:
      Mutex *mutex;
    };

    class ConditionalRef
    {
    public:
      ConditionalRef();
      ~ConditionalRef();

      operator Conditional*() const;
      Conditional *operator->() const;

    private:
      Conditional *conditional;
    };

    Mutex *newMutex();
    Conditional *newConditional();
    Thread *newThread(Threadable *t);

    #if defined(OPTI_LINUX)
    void disableSignals();
    void reenableSignals();

    struct ScopedDisableSignals {
      ScopedDisableSignals() { disableSignals(); }
      ~ScopedDisableSignals() { reenableSignals(); }
    };
    #endif

    };
  }

#endif // OPTI_THREAD_THREADS_H
