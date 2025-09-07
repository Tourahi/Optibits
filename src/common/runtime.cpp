
#include "config.h"
#include "runtime.h"

// OPTI
#include "Module.h"
#include "Knot.h"
#include "Reference.h"

// C++
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cstdio>
#include <cstddef>
#include <cmath>
#include <sstream>


namespace opti
{

    Reference *luax_refif(lua_State *L, int type)
    {
        Reference *ref = nullptr;

        if (lua_type(L, -1) == type)
            ref = new Reference(L);
        else
            lua_pop(L, 1);

        return ref;
    }

    void luax_printstack(lua_State *L)
    {
        for (int i = 1; i <= lua_gettop(L); i++)
            std::cout << i << " - " << luaL_typename(L, i) << std::endl;
    }

    int luax_traceback(lua_State *L)
    {
        if (!lua_isstring(L, 1))
            return 1;

        lua_getglobal(L, "debug");
        if (!lua_istable(L, -1)) {
            lua_pop(L, 2);
            return 1;
        }

        // get the function
        lua_getfield(L, -1, "traceback");
        if (!lua_isfunction(L, -1)) {
            lua_pop(L, 2);
            return 1;
        }

        // prepare function args
        lua_pushvalue(L, 1);
        lua_pushinteger(L, 2);
        // call the function <debug.traceback>
        lua_call(L, 2, 1);
        return 1;
    }

    bool luax_isarrayoftables(lua_State *L, const int index) {
        if (!lua_istable(L, index))
            return false;

        lua_rawgeti(L, index, 1);
        const bool isNested = lua_istable(L, -1);
        lua_pop(L, 1);
        return isNested;
    }

    bool luax_toboolean(lua_State *L, int idx) {
        return (lua_toboolean(L, idx) != 0);
    }

    bool luax_checknoolean(lua_State *L, int idx) {
        luaL_checktype(L, idx, LUA_TBOOLEAN);
        return lua_toboolean(L, idx);
    }

    void luax_pushboolean(lua_State *L, bool b) {
        lua_pushboolean(L, b ? 1 : 0);
    }

    bool luax_optboolean(lua_State *L, int idx, bool b) {
        if (lua_isboolean(L, idx) == 1)
            return (lua_toboolean(L, idx) == 1 ? true : false);
        return b;
    }

    std::string luax_tostring(lua_State *L, int idx) {
        size_t len;
        const char *str = lua_tolstring(L, idx, &len);
        return {str, len};
    }

    std::string luax_checkstring(lua_State *L, int idx) {
        size_t len;
        const char *str = luaL_checklstring(L, idx, &len);
        return {str, len};
    }

    void luax_pushstring(lua_State *L, const std::string &str) {
        lua_pushlstring(L, str.data(), str.size());
    }

    void luax_pushpointerasstring(lua_State *L, const void *pointer) {
        char str[sizeof(void *)];
	    memcpy(str, &pointer, sizeof(void *));
	    lua_pushlstring(L, str, sizeof(void *));
    }

}