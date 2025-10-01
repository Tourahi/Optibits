
#include "threads.h"
#include "Thread.h"

namespace opti {
  namespace thread {
    namespace sdl {
      Mutex::Mutex()
      {
        mutex = SDL_CreateMutex();
      }

      Mutex::~Mutex()
      {
        SDL_DestroyMutex(mutex);
      }

      void Mutex::lock()
      {
        SDL_LockMutex(mutex);
      }

      void Mutex::unlock()
      {
        SDL_UnlockMutex(mutex);
      }

      Conditional::Conditional()
      {
        cond = SDL_CreateCondition();
      }

      Conditional::~Conditional()
      {
        SDL_DestroyCondition(cond);
      }

      void Conditional::signal()
      {
        SDL_SignalCondition(cond);
      }

      void Conditional::broadcast()
      {
        SDL_BroadcastCondition(cond);
      }

      bool Conditional::wait(thread::Mutex *_mutex, int timeout)
      {
        // Yes, I realise this can be dangerous,
        // however, you're asking for it if you're
        // mixing thread implementations.
        Mutex *mutex = (Mutex *) _mutex;
        if (timeout < 0)
        {
          SDL_WaitCondition(cond, mutex->mutex);
          return true;
        }
        else
          return SDL_WaitConditionTimeout(cond, mutex->mutex, timeout);
      }

    }

    /**
     * Implementations of the functions declared in src/modules/threads.h.
     **/

    thread::Mutex *newMutex()
    {
      return new sdl::Mutex();
    }

    thread::Conditional *newConditional()
    {
      return new sdl::Conditional();
    }

    thread::Thread *newThread(Threadable *t)
    {
      return new sdl::Thread(t);
    }

  }
}
