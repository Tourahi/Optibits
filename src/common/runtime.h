
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
   * Like luax_tofloat, but checks that the value is a number.
   *
   * @see luax_tofloat
   */
  inline float luax_checkfloat(lua_State *L, int idx)
  {
    return static_cast<float>(luaL_checknumber(L, idx));
  }

  inline int luax_toint(lua_State *L, int idx)
  {
    return static_cast<int>(lua_tointeger(L, idx));
  }

  inline int luax_checkint(lua_State *L, int idx)
  {
    return static_cast<int>(luaL_checkinteger(L, idx));
  }

  inline int luax_optint(lua_State *L, int idx, int def)
  {
    return static_cast<int>(luaL_optinteger(L, idx, def));
  }

  inline lua_Number luax_checknumberclamped(lua_State *L, int idx, double minv, double maxv)
  {
    return std::min(std::max(luaL_checknumber(L, idx), minv), maxv);
  }

  inline lua_Number luax_optnumberclamped(lua_State *L, int idx, double minv, double maxv, double def)
  {
    return std::min(std::max(luaL_optnumber(L, idx, def), minv), maxv);
  }

  inline lua_Number luax_checknumberclamped01(lua_State *L, int idx)
  {
    return std::min(std::max(luaL_checknumber(L, idx), 0.0), 1.0);
  }

  inline lua_Number luax_optnumberclamped01(lua_State *L, int idx, double def)
  {
    return std::min(std::max(luaL_optnumber(L, idx, def), 0.0), 1.0);
  }


  /**
   * Require at least 'min' number of items on the stack.
   * @param L The Lua state.
   * @param min The minimum number of items on the stack.
   * @return Zero if conditions are met, otherwise a Lua error (longjmp).
   **/
  int luax_assert_argc(lua_State *L, int min);

  /**
   * Require at least 'min', but more than 'max' items on the stack.
   * @param L The Lua state.
   * @param min The minimum number of items on the stack.
   * @param max The maximum number of items on the stack.
   * @return Zero if conditions are met, otherwise a Lua error (longjmp).
   **/
  int luax_assert_argc(lua_State *L, int min, int max);

  /**
   * Require that the value at idx is a function.
   * @param L The Lua state.
   *@param idx The index on the stack.
   **/
  int luax_assert_function(lua_State *L, int idx);

  /**
   * Require that the value at idx is not nil. If it is, the function throws an
   * error using an optional error string at idx+1.
   * @param L The Lua state.
   * @param idx The index on the stack.
   **/
  int luax_assert_nilerror(lua_State *L, int idx);

  /**
   * Registers all functions in the array l (see luaL_Reg) into the table at the
   * top of the stack.
   * Similar to Lua 5.2's luaL_setfuncs without the upvalues, and to Lua 5.1's
   * luaL_register without the library name.
   **/
  void luax_setfuncs(lua_State *L, const luaL_Reg *l);

  /**
   * Loads a Lua module using the 'require' function. Leaves the return result on
   * the stack.
   * @param name The name of the module to require.
   **/
  int luax_require(lua_State *L, const char *name);

  /**
   * Register a module in the opti table. The opti table will be created if it does not exist.
   * NOTE: The module-object is expected to have a +1 reference count before calling
   * this function, as it doesn't retain the object itself but Lua will release it
   * upon garbage collection.
   * @param L The Lua state.
   **/
  int luax_register_module(lua_State *L, const WrappedModule &m);

  /**
   * Inserts a module with 'name' into the package.preloaded table.
   * @param f The function to be called when the module is opened.
   * @param name The name of the module, with 'opti'-prefix, for instance 'opti.graphics'.
   **/
  int luax_preload(lua_State *L, lua_CFunction f, const char *name);

  /**
   * Register a new type.
   * NOTE: The type is passed by pointer instead of reference because calling va_start
   * on a reference is undefined behaviour.
   * @param type The type.
   * @param ... The list of lists of member functions for the type. (of type luaL_Reg*)
   **/
  int luax_register_type(lua_State *L, Type *type, ...);

  /**
   * Pushes the metatable of the specified type onto the stack.
  **/
  void luax_gettypemetatable(lua_State *L, const Type &type);

  /**
   * Do a table.insert from C
   * @param L the state
   * @param tindex the stack index of the table
   * @param vindex the stack index of the value
   * @param pos the position to insert it in
   **/
  int luax_table_insert(lua_State *L, int tindex, int vindex, int pos = -1);

  /**
   * Register a new searcher function for package.loaders. This can for instance enable
   * loading of files through opti.filesystem using standard require.
   * @param L The Lua state.
   * @param f The searcher function.
   * @param pos The position to insert the loader in.
   **/
  int luax_register_searcher(lua_State *L, lua_CFunction f, int pos = -1);


  /**
   ****************
   * insist       *
   ****************
   ** /


  /**
   * 'Insist' that a table 'k' exists in the table at idx. Insistence involves that the
   * table (k) is created if it does not exist in the table at idx. The table at idx must
   * pre-exist, however. Also note that if a non-table value exists at the specified
   * location, it will be overwritten with a new table. The insisted table, and only the
   * insisted table, will be placed on top of the stack.
   *
   * @param idx The index on the stack containing a table.
   * @param k The name of the table we are insisting exist.
   **/
  int luax_insist(lua_State *L, int idx, const char *k);


  /**
   * Insist that a global table 'k' exists. See luax_insist.
   * @param k The name of the table we are insisting exist.
   **/
  int luax_insistglobal(lua_State *L, const char *k);

  /**
   * Insists that a table 'k' exists inside the 'opti' table. See luax_insist.
   * @param k The name of the table we are insisting exist.
   **/
  int luax_insistopti(lua_State *L, const char *k);

  /**
   * Pushes the table 'k' in the opti table onto the stack. Pushes nil if the
   * table doesn't exist.
   * @param k The name of the table we want to get.
   **/
  int luax_getopti(lua_State *L, const char *k);

  /**
   * Gets (creates if needed) the specified Registry, and pushes it into the
   * stack.
   * @param L The Lua state.
   * @param r The Registry to get.
   **/
  int luax_insistregistry(lua_State *L, Registry r);

  /**
   * Gets the specified Registry, and pushes it onto the stack. Pushes nil if the
   * registry hasn't been created (see luax_insistregistry.)
   * @param L The Lua state.
   * @param r The Registry to get.
   **/
  int luax_getregistry(lua_State *L, Registry r);


  /**
   * Gets whether the value at idx is an array of tables.
   **/
  bool luax_isarrayoftables(lua_State *L, int index);

}

#endif
