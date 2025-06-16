
#include "delay.h"

#include <SDL3/SDL_timer.h>


namespace opti
{

  void eep(double ms)
  {
    // We don't need to initialize the SDL timer subsystem for SDL_Delay to
    // function - and doing so causes SDL to create a worker thread.
    SDL_DelayNS(SDL_NS_PER_MS * ms);
  }

}
