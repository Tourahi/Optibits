
#include "Thread.h"


namespace opti {
  namespace thread {
    namespace sdl {
      Thread::Thread(Threadable *t)
        : t(t)
        , running(false)
        , thread(nullptr)
      {
      }

      Thread::~Thread()
      {
        // Clean up handle
        if (thread)
          SDL_DetachThread(thread);
      }

      bool Thread::start() {
#if defined(OPTI_LINUX)
        opti::thread::ScopedDisableSignals disableSignals;
#endif
        Lock l(mutex);

        if (running)
          return false;

        if (thread)
          SDL_WaitThread(thread, nullptr);

        // Keep the threadable around until the thread is done with it.
        // This is done before thread_runner executes because there can be a delay
        // between CreateThread and the start of the thread code's execution.
        t->release();

        thread = SDL_CreateThread(thread_runner, t->getThreadName(), this);
        running = (thread != nullptr);

        if (!running)
          t->release(); // thread_runner is never called in this situation.

        return running;
      }

      void Thread::wait()
      {
        {
          Lock l(mutex);
          if (!thread)
            return;
        }
        SDL_WaitThread(thread, nullptr);
        Lock l(mutex);
        running = false;
        thread = nullptr;
      }

      bool Thread::isRunning()
      {
        Lock l(mutex);
        return running;
      }

      int Thread::thread_runner(void *data)
      {
        Thread *self = static_cast<Thread *>(data); // some compilers don't like 'this'

        self->t->threadFunction();

        {
          Lock l(self->mutex);
          self->running = false;
        }

        // This was retained in start().
        self->t->release();
        return 0;
      }

    }
  }
}