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


UTEST(LuaxIsArrayOfTables, BasicCases) {
    lua_State *L = luaL_newstate();

    // Not a table
    lua_pushnumber(L, 42);
    ASSERT_FALSE(opti::luax_isarrayoftables(L, -1));
    lua_pop(L, 1);

    // Table, but first element is not a table
    lua_newtable(L);
    lua_pushnumber(L, 123);
    lua_rawseti(L, -2, 1);
    ASSERT_FALSE(opti::luax_isarrayoftables(L, -1));
    lua_pop(L, 1);

    // Table, first element is a table
    lua_newtable(L);
    lua_newtable(L); // nested table
    lua_rawseti(L, -2, 1);
    ASSERT_TRUE(opti::luax_isarrayoftables(L, -1));
    lua_pop(L, 1);
}


UTEST(LuaxIntFlag, BasicCases) {
    lua_State *L = luaL_newstate();

    lua_newtable(L);

    ASSERT_EQ(opti::luax_intflag(L, -1, "missing", 42), 42);

    lua_pushinteger(L, 123);
    lua_setfield(L, -2, "intkey");
    ASSERT_EQ(opti::luax_intflag(L, -1, "intkey", 0), 1);

    lua_pushinteger(L, 0);
    lua_setfield(L, -2, "zerokey");
    ASSERT_EQ(opti::luax_intflag(L, -1, "zerokey", 99), 0);

    lua_pushnil(L);
    lua_setfield(L, -2, "nilkey");
    ASSERT_EQ(opti::luax_intflag(L, -1, "nilkey", 7), 7);
}