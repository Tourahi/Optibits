
#ifndef OPTI_THREAD_THREAD_H
#define OPTI_THREAD_THREAD_H

// OPTI
#include "common/config.h"

namespace opti {
  namespace thread {

    class Thread {
    public:

      virtual ~Thread() {};
      virtual bool start() = 0;
      virtual void wait() = 0;
      virtual bool isRunning() = 0;

    };

  }
}


#endif //OPTI_THREAD_THREAD_H
