// OPTI
#include "Data.h"
#include "thread/threads.h"

namespace opti {

    opti::Type Data::type("Data", &opti::Knot::type);

    Data::~Data() {
        delete mutex;
    }

    static void createMutex(opti::thread::Mutex **mutexAdr) {
        *mutexAdr = opti::thread::newMutex();
    }

    opti::thread::Mutex *Data::getMutex() {
        std::call_once(mutexCreated, createMutex, &mutex);
        return mutex;
    }

}