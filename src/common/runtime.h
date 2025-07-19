
#ifndef OPTI_RUNTIME_H
#define OPTI_RUNTIME_H

// OPTI
#include "config.h"
#include "types.h"
#include "Knot.h"
#include "Variant.h"


// lua
extern "C" {
  #define LUA_COMPAT_ALL
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
}

// C++
#include <exception>
#include <algorithm>
#include <set>

namespace opti
{

  class Module;


  /**
   * Registries represent special tables which can be accessed with
   * luax_insistregistry and luax_getregistry.
   **/
  enum Registry
  {
    REGISTRY_MODULES,
    REGISTRY_KNOTS
  };


}

#endif
