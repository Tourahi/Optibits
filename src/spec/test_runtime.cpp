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

UTEST(LuaxPinnedThread, InsistAndGet) {
    lua_State *L = luaL_newstate();

    // First call should pin the main thread
    lua_State *thread1 = opti::luax_insistpinnedthread(L);
    ASSERT_EQ(thread1, L);

    // Get should return the same thread
    lua_State *thread2 = opti::luax_getpinnedthread(L);
    ASSERT_EQ(thread2, L);

    // Insist again should still return the same thread
    lua_State *thread3 = opti::luax_insistpinnedthread(L);
    ASSERT_EQ(thread3, L);

    lua_close(L);
}


UTEST(LuaxIsType, BasicCases) {
    lua_State *L = luaL_newstate();

    // Case 1: Not userdata
    lua_pushnumber(L, 42);
    opti::Type dummyType("type1", nullptr);
    ASSERT_FALSE(opti::luax_istype(L, -1, dummyType));
    lua_pop(L, 1);

    // Case 2: Userdata with matching type
    opti::Type typeA("typeA", nullptr), typeB("typeB", nullptr);
    opti::Type typeC("typeC", &typeA);

    typeA.init();
    typeB.init();
    typeC.init();

    void *ud = lua_newuserdata(L, sizeof(opti::Proxy));
    opti::Proxy *p = static_cast<opti::Proxy *>(ud);
    p->type = &typeA;

    // typeA is-a typeA
    ASSERT_TRUE(opti::luax_istype(L, -1, typeA));
    // typeA is not typeB
    ASSERT_FALSE(opti::luax_istype(L, -1, typeB));

    p->type = &typeC;
    // typeC is-a typeA
    ASSERT_TRUE(opti::luax_istype(L, -1, typeA));

    lua_pop(L, 1);

    // Case 3: Userdata with null type pointer
    ud = lua_newuserdata(L, sizeof(opti::Proxy));
    p = static_cast<opti::Proxy *>(ud);
    p->type = nullptr;
    ASSERT_FALSE(opti::luax_istype(L, -1, typeA));
    lua_pop(L, 1);

    lua_close(L);
}


UTEST(LuaxPushVariant, BasicCases) {
    lua_State *L = luaL_newstate();

    // Boolean
    opti::Variant v_bool(true);
    opti::luax_pushvariant(L, v_bool);
    ASSERT_TRUE(lua_isboolean(L, -1));
    ASSERT_EQ(static_cast<int>(lua_toboolean(L, -1)), 1);
    lua_pop(L, 1);

    // Number
    opti::Variant v_number((double) 1999);
    opti::luax_pushvariant(L, v_number);
    ASSERT_TRUE(lua_isnumber(L, -1));
    ASSERT_EQ((double)lua_tonumber(L, -1), 1999);
    lua_pop(L, 1);

    lua_close(L);
}

UTEST(LuaxConvKnot, SingleIndex) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Create dummy opti.mod.fn in Lua
    lua_newtable(L); // opti
    lua_newtable(L); // mod
    lua_pushcfunction(L, [](lua_State *L) -> int {
        // Return the string "converted" and no error
        lua_pushstring(L, "converted");
        lua_pushnil(L);
        return 2;
    });
    lua_setfield(L, -2, "fn");
    lua_setfield(L, -2, "mod");
    lua_setglobal(L, "opti");

    lua_pushstring(L, "input");
    int idx = lua_gettop(L);

    int ret = opti::luax_convknot(L, idx, "mod", "fn");
    ASSERT_EQ(ret, 0);
    ASSERT_TRUE(lua_isstring(L, idx));
    ASSERT_STREQ(lua_tostring(L, idx), "converted");

    lua_close(L);
}
