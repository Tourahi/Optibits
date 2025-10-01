
#ifndef OPTI_THREAD_SDL_THREADS_H
#define OPTI_THREAD_SDL_THREADS_H

#include "common/config.h"
#include "thread/threads.h"

#include <SDL3/SDL_thread.h>
#include <SDL3/SDL_mutex.h>

namespace opti {
  namespace thread {
    namespace sdl {

      class Conditional;

      class Mutex : public thread::Mutex {
      public:
        Mutex();
        ~Mutex();

        void lock();
        void unlock();

      private:

        SDL_Mutex *mutex;
        Mutex(const Mutex&) {}

        friend class Conditional;
      }; // Mutex

      class Conditional : public thread::Conditional {
      public:
        Conditional();
        ~Conditional();

        void signal();
        void broadcast();
        bool wait(thread::Mutex *mutex, int timeout=-1);

      private:
        SDL_Condition *cond;

      }; // Conditional
    }
  }
}



#endif // OPTI_THREAD_SDL_THREADS_H
