
#include "threads.h"

#include "common/Knot.h"
#include "common/types.h"

#if defined(OPTI_LINUX)
#include <signal.h>
#endif


namespace opti {
  namespace thread {

    Lock::Lock(Mutex *m)
      : mutex(m)
    {
      mutex->lock();
    }

    Lock::Lock(Mutex &m)
     : mutex(&m)
    {
      mutex->lock();
    }

    Lock::Lock(Lock &&other)
    {
      mutex = other.mutex;
      other.mutex = nullptr;
    }

    Lock::~Lock()
    {
      if (mutex)
        mutex->unlock();
    }

    EmptyLock::EmptyLock()
      : mutex(nullptr)
    {
    }

    EmptyLock::~EmptyLock()
    {
      if (mutex)
        mutex->unlock();
    }

    void EmptyLock::setLock(Mutex *m)
    {
      if (m)
        m->lock();

      if (mutex)
        mutex->unlock();

      mutex = m;
    }

    void EmptyLock::setLock(Mutex &m)
    {
      m.lock();

      if (mutex)
        mutex->unlock();

      mutex = &m;
    }

    opti::Type Threadable::type("Threadable", &Knot::type);

    Threadable::Threadable()
    {
      owner = newThread(this);
    }

    Threadable::~Threadable()
    {
      delete owner;
    }

    bool Threadable::start()
    {
      return owner->start();
    }

    void Threadable::wait()
    {
      owner->wait();
    }

    bool Threadable::isRunning() const
    {
      return owner->isRunning();
    }

    const char *Threadable::getThreadName() const
    {
      return threadName.empty() ? nullptr : threadName.c_str();
    }

    MutexRef::MutexRef()
  : mutex(newMutex())
    {
    }

    MutexRef::~MutexRef()
    {
      delete mutex;
    }

    MutexRef::operator Mutex*() const
    {
      return mutex;
    }

    Mutex *MutexRef::operator->() const
    {
      return mutex;
    }

    ConditionalRef::ConditionalRef()
      : conditional(newConditional())
    {
    }

    ConditionalRef::~ConditionalRef()
    {
      delete conditional;
    }

    ConditionalRef::operator Conditional*() const
    {
      return conditional;
    }

    Conditional *ConditionalRef::operator->() const
    {
      return conditional;
    }

#if defined(OPTI_LINUX)
    static sigset_t oldset;

    void disableSignals()
    {
      sigset_t newset;
      sigfillset(&newset);
      pthread_sigmask(SIG_SETMASK, &newset, &oldset);
    }

    void reenableSignals()
    {
      pthread_sigmask(SIG_SETMASK, &oldset, nullptr);
    }
#endif

  }
}