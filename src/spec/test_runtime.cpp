#include "../libs/utest.h"
#include "../common/runtime.h"


UTEST(LuaxToBoolean, TrueAndFalseCases) {
    lua_State *L = luaL_newstate();

    // Lua true
    lua_pushboolean(L, 1);
    ASSERT_TRUE(opti::luax_toboolean(L, -1));
    lua_pop(L, 1);

    // Lua false
    lua_pushboolean(L, 0);
    ASSERT_FALSE(opti::luax_toboolean(L, -1));
    lua_pop(L, 1);

    // Lua nil
    lua_pushnil(L);
    ASSERT_FALSE(opti::luax_toboolean(L, -1));
    lua_pop(L, 1);
}