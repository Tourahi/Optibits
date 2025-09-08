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

UTEST(LuaxBoolFlag, BasicCases) {
    lua_State *L = luaL_newstate();

    lua_newtable(L);

    ASSERT_EQ(opti::luax_boolflag(L, -1, "missing", false), false);

    lua_pushinteger(L, true);
    lua_setfield(L, -2, "boolkey");
    ASSERT_EQ(opti::luax_boolflag(L, -1, "boolkey", false), true);

    lua_pushinteger(L, false);
    lua_setfield(L, -2, "falsekey");
    ASSERT_EQ(opti::luax_boolflag(L, -1, "falsekey", false), true);

    lua_pushnil(L);
    lua_setfield(L, -2, "nilkey");
    ASSERT_EQ(opti::luax_boolflag(L, -1, "nilkey", true), true);
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

UTEST(LuaxNumberFlag, BasicCases) {
    lua_State *L = luaL_newstate();

    lua_newtable(L);

    ASSERT_EQ(opti::luax_numberflag(L, -1, "missing", 3.14), 3.14);

    lua_pushnumber(L, 2.71);
    lua_setfield(L, -2, "numkey");
    ASSERT_EQ(opti::luax_numberflag(L, -1, "numkey", 0.0), 1.0);

    lua_pushnumber(L, 0.0);
    lua_setfield(L, -2, "zerokey");
    ASSERT_EQ(opti::luax_numberflag(L, -1, "zerokey", 1.0), 0.0);

    lua_pushnil(L);
    lua_setfield(L, -2, "nilkey");
    ASSERT_EQ(opti::luax_numberflag(L, -1, "nilkey", 1.618), 1.618);
}


UTEST(LuaxAssertNullError, BasicCases) {
    lua_State *L = luaL_newstate();

    lua_pushnil(L);
    lua_pushstring(L, "Error");
    lua_pushcfunction(L, [](lua_State *L) -> int {
        return opti::luax_assert_nilerror(L, 1);
    });
    lua_insert(L, 1);
    int status = lua_pcall(L, 2, 1, 0);
    if (status != 0) {
        const char *msg = lua_tostring(L, -1);
        ASSERT_STREQ(msg, "Error");
    }
    lua_close(L);
}