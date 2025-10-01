//
// Created by mimir on 01/10/25.
//

#ifndef OPTI_THREAD_SDL_THREAD_H
#define OPTI_THREAD_SDL_THREAD_H

// OPTI
#include "thread/Thread.h"
#include "threads.h"

// SDL
#include <SDL3/SDL_thread.h>

namespace opti {
  namespace thread {
    namespace sdl {

      class Thread : public thread::Thread {
      public:

        Thread(Threadable *t);
        ~Thread();
        bool start();
        void wait();
        bool isRunning();
      private:

        Threadable *t;
        bool running;
        SDL_Thread *thread;
        Mutex mutex;

        static int thread_runner(void *data);
      };
    }
  }
}

#endif // OPTI_THREAD_SDL_THREAD_H
