
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
  class Reference;

  template<typename T>
  class StrongRef;

  /**
   * Registries represent special tables which can be accessed with
   * luax_insistregistry and luax_getregistry.
   **/
  enum Registry
  {
    REGISTRY_MODULES,
    REGISTRY_KNOTS
  };

  /**
   * A Module with Lua wrapper functions and other data.
   */
  struct WrappedModule
  {
    // The module containing the func.
    Module *module;

    const char *name;

    // The type of this module.
    Type *type;

    // The functions of the module (last element {0,0}).
    const luaL_Reg *functions;

    // A list of functions which expose the types of the modules (last element 0).
    const lua_CFunction *types;

  };


  /**
   * Returns a reference to the top stack element (-1) if the value
   * is of the specified type. If the value is incorrect, zero is returned.
   *
   * In any case, the top stack element is popped, regardless of its type.
   * @param L
   * @param type
   * @return
   */
  Reference *luax_refif(lua_State *L, int type);

  /**
   * Prints the currents contents of the stack. [DEBUG]
   * @param L
   */
  void luax_printstack(lua_State *L);


  /**
   * Traceback function for use with lua_pcall. Calls debug.traceback.
   * @param L
   * @return
   */
  int luax_traceback(lua_State *L);

  /**
   * Gets weather the value at index is an array of tables.
   * @param L
   * @param index
   * @return
   */
  bool luax_isarrayoftables(lua_State *L, int index);

  /**
   * Converts the value at idx to a bool. It follow the same rules
   *  as lua_toboolean, but returns a bool instead of an int.
   * @param L The Lua state.
   * @param index The index on the Lua stack.
   * @return True if the value evaluates to true, false otherwise.
   */
  bool luax_toboolean(lua_State *L, int index);

  /**
   * Returns the boolean value at idx. Causes a Lua error if the value is not
   * a boolean.
   **/
  bool luax_checkboolean(lua_State *L, int idx);

  /**
   * Pushes a bool onto the stack. It's the same as lua_pushboolean,
   * but with bool instead of int.
   * @param L The Lua state.
   * @param b The bool to push.
   **/
  void luax_pushboolean(lua_State *L, bool b);

  /**
   * Converts the value at idx to a bool, or if not present, b is returned.
   * @param L The Lua state.
   * @param idx The index of the Lua stack.
   * @param b The value to return if no value exist at the specified index.
   * @return True if the value evaluates to true, false otherwise.
   **/
  bool luax_optboolean(lua_State *L, int idx, bool b);

  /**
    * Converts the value at idx to a std::string. It takes care of the string
    * size and possible embedded nulls.
    * @param L The Lua state.
    * @param idx The index on the Lua stack.
    * @return Copy of the string at the specified index.
    **/
  std::string luax_tostring(lua_State *L, int idx);

  /**
   * Converts the value at idx to a std::string. It takes care of the string
   * size and possible embedded nulls.
   * @param L The Lua state.
   * @param idx The index on the Lua stack.
   * @return Copy of the string at the specified index.
   **/
  std::string luax_checkstring(lua_State *L, int idx);

  /**
   * Pushes a std::string onto the stack. It uses the length of the string
   * for lua_pushlstring's len argument.
   * @param L The Lua state.
   * @param str The string to push.
   **/
  void luax_pushstring(lua_State *L, const std::string &str);

  /**
   * Pushes a pointer onto the stack as a string (i.e. a new string with a length
   * of 4 or 8 will be created, containing the given address in its bytes).
   * This is a workaround for lua_pushlightuserdata not working on systems which
   * use more than the lower 47 bits of address space, when LuaJIT is used.
   **/
  void luax_pushpointerasstring(lua_State *L, const void *pointer);


  /**
   * Flags retrieval functions.
   */
  bool luax_boolflag(lua_State *L, int table_index, const char *key, bool defaultValue);
  int luax_intflag(lua_State *L, int table_index, const char *key, int defaultValue);
  double luax_numberflag(lua_State *L, int table_index, const char *key, double defaultValue);
  bool luax_checkboolflag(lua_State *L, int table_index, const char *key);
  int luax_checkintflag(lua_State *L, int table_index, const char *key);


  /**
   * Gets whether the value at idx is an array of tables.
   **/
  bool luax_isarrayoftables(lua_State *L, int index);

}

#endif
