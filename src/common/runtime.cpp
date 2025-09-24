
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
    // Keys
    static const char *MAIN_THREAD_KEY = "_opti_mainthread";
    typedef uint64 KnotKey;

    static int w__gc(lua_State *L) {
        Proxy *p = static_cast<Proxy *>(lua_touserdata(L, 1));
        if (p->knot != nullptr) {
            p->knot->release();
            p->knot = nullptr;
        }
        return 0;
    }

    static int w__tostring(lua_State *L) {
        Proxy *p = static_cast<Proxy *>(lua_touserdata(L, 1));
        const char *typname = lua_tostring(L, lua_upvalueindex(1));
        lua_pushfstring(L, "%s: %p", typname, p->knot);
        return 1;
    }

    static int w__type(lua_State *L) {
        lua_pushvalue(L, lua_upvalueindex(1));
        return 1;
    }

    static int w__typeOf(lua_State *L) {
        Proxy *p = static_cast<Proxy *>(lua_touserdata(L, 1));
        Type *t = luax_type(L, 2);
        if (!t)
            luax_pushboolean(L, false);
        else
            luax_pushboolean(L, p->type->isa(*t));
        return 1;
    }

    static int w__eq(lua_State *L) {
        Proxy *p1 = static_cast<Proxy *>(lua_touserdata(L, 1));
        Proxy *p2 = static_cast<Proxy *>(lua_touserdata(L, 2));
        luax_pushboolean(L, p1->knot == p2->knot && p1->knot != nullptr);
        return 1;
    }

    static KnotKey luax_computeoptiknotkey(lua_State *L, opti::Knot *knot) {
        const size_t minalign = sizeof(void*) == 8 ? alignof(std::max_align_t) : 1;
        uintptr_t key = reinterpret_cast<uintptr_t>(knot);

        if ((key & (minalign - 1)) != 0) {
            luaL_error(L, "Cannot push opti knot to Lua: unexpected alignment "
                "(pointer is %p but alignment should be %d)", knot, (int) minalign);
        }

        static const size_t shift = (size_t) log2(minalign);

        key >>= shift;

        return (KnotKey) key;
    }

    static bool luax_isfulllightuserdatasupported(lua_State *L) {
        static bool checked = false;
        static bool supported = false;

        if (sizeof(void*) == 4)
            return true;

        if (!checked) {
            lua_pushcclosure(L, [](lua_State *L) -> int {
                lua_pushlightuserdata(L, (void *) (~((size_t) 0)));
                return 1;
            }, 0);

            supported = lua_pcall(L, 0, 1, 0) == 0;
            checked = true;

            lua_pop(L, 1);
        }
        return supported;
    }

    static void luax_pushoptiknotkey(lua_State *L, KnotKey key) {
        if (luax_isfulllightuserdatasupported(L))
            lua_pushlightuserdata(L, (void *) key);
        else if (key > 0x20000000000000ULL)  // 2^53
            luaL_error(L, "Cannot push opti knot to Lua: pointer value %p is too large", key);
        else
            lua_pushnumber(L, (lua_Number) key);
    }

    static int w__release(lua_State *L) {
        Proxy *p = static_cast<Proxy *>(lua_touserdata(L, 1));
        Knot *knot = p->knot;

        if (knot != nullptr) {
            p->knot = nullptr;
            knot->release();

            luax_getregistry(L, REGISTRY_KNOTS);

            if (lua_istable(L, -1)) {
                KnotKey objectkey = luax_computeoptiknotkey(L, knot);
                luax_pushoptiknotkey(L, objectkey);
                lua_pushnil(L);
                // https://www.lua.org/manual/5.1/manual.html#lua_settable
                lua_settable(L, -3);
            }

            lua_pop(L, 1);
        }

        luax_pushboolean(L, knot != nullptr);
        return 1;
    }

    Type *luax_type(lua_State *L, int idx) {
        return Type::byName(luaL_checkstring(L, idx));
    }

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

    bool luax_boolflag(lua_State *L, int table_index, const char *key, bool defaultValue) {
        lua_getfield(L, table_index, key);

        bool result;
        if (lua_isnoneornil(L, -1))
            result = defaultValue;
        else
            result = lua_toboolean(L, -1) != 0;

        lua_pop(L, 1);
        return result;
    }


    int luax_intflag(lua_State *L, int table_index, const char *key, int defaultValue) {
        lua_getfield(L, table_index, key);

        int result;

        if (lua_isnoneornil(L, -1))
            result = defaultValue;
        else
            result = static_cast<int>(lua_tointeger(L, -1)) != 0;

        lua_pop(L, 1);
        return result;
    }


    double luax_numberflag(lua_State *L, int table_index, const char *key, double defaultValue) {
        lua_getfield(L, table_index, key);

        double result;

        if (lua_isnoneornil(L, -1))
            result = defaultValue;
        else
            result = lua_tonumber(L, -1) != 0;

        lua_pop(L, 1);
        return result;
    }

    bool luax_checkboolflag(lua_State *L, int table_index, const char *key) {
        lua_getfield(L, table_index, key);

        bool result = false;
        if (lua_type(L, -1) != LUA_TBOOLEAN) {
            std::string error = "expected boolean field '" + std::string(key) + "' in table";
            return luaL_argerror(L, table_index, error.c_str());
        }

        result = luax_toboolean(L, 1);
        lua_pop(L, 1);
        return result;
    }

    int luax_checkintflag(lua_State *L, int table_index, const char *key) {
        lua_getfield(L, table_index, key);

        int result = 0;
        if (!lua_isnumber(L, -1)) {
            std::string error = "expected integer field '" + std::string(key) + "' in table";
            return luaL_argerror(L, table_index, error.c_str());
        }

        result = static_cast<int>(luaL_checkinteger(L, 1));
        lua_pop(L, 1);
        return result;
    }

    int luax_assert_argc(lua_State *L, int min) {
        int argc  = lua_gettop(L);
        if (argc < min)
            return luaL_error(L, "Incorrect number of arguments. Got [%d], expected at least [%d]", argc, min);
        return 0;
    }

    int luax_assert_argc(lua_State *L, int min, int max) {
        int argc  = lua_gettop(L);
        if (argc < min || argc > max)
            return luaL_error(L, "Incorrect number of arguments. Got [%d], expected [%d-%d]", argc, min, max);
        return 0;
    }

    int luax_assert_function(lua_State *L, int idx) {
        if (!lua_isfunction(L, idx))
            return luaL_error(L, "Argument must be of type \"function\".");
        return 0;
    }

    int luax_assert_nilerror(lua_State *L, int idx) {
        // allows throwing a custom error if provided
        if (lua_isnoneornil(L, idx)) {
            if (lua_isstring(L, ++idx))
                return luaL_error(L, lua_tostring(L, idx));
            return luaL_error(L, "assertion failed!");
        }
        return 0;
    }

    void luax_setfuncs(lua_State *L, const luaL_Reg *l) {
        if (l == nullptr)
            return;
        for (; l->name != nullptr; l++) {
            lua_pushcfunction(L, l->func);
            lua_setfield(L, -2, l->name);
        }
    }

    int luax_require(lua_State *L, const char *name) {
        lua_getglobal(L, "require");
        lua_pushstring(L, name);
        lua_call(L, 1, 1);
        return 1;
    }

    int luax_register_module(lua_State *L, const WrappedModule &m) {
        luax_insistregistry(L, REGISTRY_KNOTS);

        Proxy *p = (Proxy *)lua_newuserdata(L, sizeof(Proxy));
        p->knot = m.module;
        p->type = m.type;

        luaL_newmetatable(L, m.module->getName());
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, w__gc);
        lua_setfield(L, -2, "__gc");

        lua_setmetatable(L, -2);
        lua_setfield(L, -2, m.name); // _modules[name] = proxy
        lua_pop(L, 1);

        luax_insistglobal(L, "opti");

        lua_newtable(L);

        if (m.functions != nullptr)
            luax_setfuncs(L, m.functions);


        if (m.types != nullptr)
        {
            for (const lua_CFunction *t = m.types; *t != nullptr; t++)
                (*t)(L);
        }

        lua_pushvalue(L, -1);
        lua_setfield(L, -3, m.name);
        lua_remove(L, -2);

        return 1;
    }

    int luax_preload(lua_State *L, lua_CFunction f, const char *name) {
        lua_getglobal(L, "package");
        lua_getfield(L, -1, "preload");
        lua_pushcfunction(L, f);
        lua_setfield(L, -2, name);
        lua_pop(L, 2);
        return 0;
    }

    int luax_register_type(lua_State *L, Type *type, ...) {
        type->init();

        luax_getregistry(L, REGISTRY_KNOTS);

        if (!lua_istable(L, -1)) {
            lua_newtable(L);
            lua_replace(L, -2);

            // Create a metatable
            lua_newtable(L);

            lua_pushliteral(L, "v");
            lua_setfield(L, -2, "__mode");

            lua_setmetatable(L, -2);

            lua_setfield(L, LUA_REGISTRYINDEX, "_optiknots");
        }
        else
            lua_pop(L, 1);

        luaL_newmetatable(L, type->getName());

        // m.__index = m
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");

        // setup gc
        lua_pushcfunction(L, w__gc);
        lua_setfield(L, -2, "__gc");

        // Add equality
        lua_pushcfunction(L, w__eq);
        lua_setfield(L, -2, "__eq");

        // Add tostring function.
        lua_pushstring(L, type->getName());
        lua_pushcclosure(L, w__tostring, 1);
        lua_setfield(L, -2, "__tostring");

        // Add type
        lua_pushstring(L, type->getName());
        lua_pushcclosure(L, w__type, 1);
        lua_setfield(L, -2, "type");

        // Add typeOf
        lua_pushcfunction(L, w__typeOf);
        lua_setfield(L, -2, "typeOf");

        // Add release
        lua_pushcfunction(L, w__release);
        lua_setfield(L, -2, "release");

        // Add __close for lua 5.4 (just calls release)
        lua_pushcfunction(L, w__release);
        lua_setfield(L, -2, "__close");

        va_list fs;
        va_start(fs, type);
        for (const luaL_Reg *f = va_arg(fs, const luaL_Reg *); f; f = va_arg(fs, const luaL_Reg *))
            luax_setfuncs(L, f);
        va_end(fs);

        lua_pop(L, 1); // Pops metatable.
        return 0;
    }

    void luax_gettypemetatable(lua_State *L, const Type &type) {
        const char *name = type.getName();
        lua_getfield(L, LUA_REGISTRYINDEX, name);
    }

    int luax_table_insert(lua_State *L, int tindex, int vindex, int pos) {
        if (tindex < 0)
            tindex = lua_gettop(L)+1+tindex;
        if (vindex < 0)
            vindex = lua_gettop(L)+1+vindex;

        if (pos == -1) {
            lua_pushvalue(L, vindex);
            lua_rawseti(L, tindex, (int) luax_objlen(L, tindex)+1);
            return 0;
        }
        else if (pos < 0)
            pos = (int) luax_objlen(L, tindex)+1+pos;

        for (int i = (int) luax_objlen(L, tindex)+1; i > pos; i--) {
            lua_rawgeti(L, tindex, i-1);
            lua_rawseti(L, tindex, i);
        }

        lua_pushvalue(L, vindex);
        lua_rawseti(L, tindex, pos);
        return 0;
    }

    int luax_insist(lua_State *L, int idx, const char *k) {

        // convert to absolut  index if necessary
        if (idx < 0 && idx > LUA_REGISTRYINDEX)
            idx += lua_gettop(L) + 1;

        lua_getfield(L, idx, k);

        // create table if necessary
        if (!lua_istable(L, -1)) {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_pushvalue(L, -1);
            lua_setfield(L, idx, k);
        }

        return 1;
    }

    int luax_insistglobal(lua_State *L, const char *k) {
        lua_getglobal(L, k);

        if (!lua_istable(L, -1)) {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_pushvalue(L, -1);
            lua_setglobal(L, k);
        }

        return 1;
    }

    int luax_insistopti(lua_State *L, const char *k) {
        luax_insistglobal(L, "opti");
        luax_insist(L, -1, k);
        lua_replace(L, -2); // replace the opti table with the insisted table
        return 1;
    }

    int luax_getopti(lua_State *L, const char *k) {
        lua_getglobal(L, "opti");

        if (!lua_isnil(L, -1)) {
            lua_getfield(L, -1, k);
            lua_replace(L, -2);
        }

        return 1;
    }

    int luax_insistregistry(lua_State *L, Registry r) {
        switch (r)
        {
        case REGISTRY_MODULES:
            return luax_insistopti(L, "_modules");
        case REGISTRY_KNOTS:
            return luax_insist(L, LUA_REGISTRYINDEX, "_optiknots");
        default:
            return luaL_error(L, "Attempted to use invalid registry.");
        }
    }

    int luax_getregistry(lua_State *L, Registry r) {
        switch (r)
        {
            case REGISTRY_MODULES:
                return luax_getopti(L, "_modules");
            case REGISTRY_KNOTS:
                lua_getfield(L, LUA_REGISTRYINDEX, "_optiknots");
                return 1;
            default:
                return luaL_error(L, "Attempted to use invalid registry.");
        }
    }

    lua_State *luax_insistpinnedthread(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, MAIN_THREAD_KEY);

        if (lua_isnoneornil(L, -1)) {
            lua_pop(L, 1);

            lua_pushthread(L);
            lua_pushvalue(L, -1);
            lua_setfield(L, LUA_REGISTRYINDEX, MAIN_THREAD_KEY);
        }

        lua_State *thread = lua_tothread(L, -1);
        lua_pop(L, 1);
        return thread;
    }

    lua_State *luax_getpinnedthread(lua_State *L) {
        lua_getfield(L, LUA_REGISTRYINDEX, MAIN_THREAD_KEY);
        lua_State *thread = lua_tothread(L, -1);
        lua_pop(L, 1);
        return thread;
    }

    void luax_rawnewtype(lua_State *L, opti::Type &type, opti::Knot *knot) {
        Proxy *u = static_cast<Proxy *>(lua_newuserdata(L, sizeof(Proxy)));

        knot->tie();

        u->knot = knot;
        u->type = &type;

        const char *name = type.getName();
        luaL_newmetatable(L, name);

        lua_getfield(L, -1, "__gc");
        bool has_gc = !lua_isnoneornil(L, -1);
        lua_pop(L, 1);

        // Make sure mt.__gc exists, so Lua states which don't have the object's
        // module loaded will still clean the object up when it's collected.
        if (!has_gc) {
            lua_pushcfunction(L, w__gc);
            lua_setfield(L, -2, "__gc");
        }

        lua_setmetatable(L, -2);
    }

    void luax_pushtype(lua_State *L, opti::Type &type, opti::Knot *knot) {
        if (knot == nullptr) {
            lua_pushnil(L);
            return;
        }

        luax_getregistry(L, REGISTRY_KNOTS);

        // The table might not exist - it should be insisted in luax_register_type.
        if (lua_isnoneornil(L, -1)) {
            lua_pop(L, 1);
            return luax_rawnewtype(L, type, knot);
        }

        KnotKey knotKey = luax_computeoptiknotkey(L, knot);

        // Get the value of optiknots[knot] on the stack.
        luax_pushoptiknotkey(L, knotKey);
        lua_gettable(L, -2);

        if (lua_type(L, -1) != LUA_TUSERDATA) {
            lua_pop(L, 1); // stack[optiknots]
            luax_rawnewtype(L, type, knot); // stack[optiknots, Proxy]
            luax_pushoptiknotkey(L, knotKey); // stack[optiknots, Proxy, knotKey]
            lua_pushvalue(L, -2); // stack[optiknots, Proxy, knotKey, Proxy]
            lua_settable(L, -4); // optiknots[knotKey] = Proxy
        }

        // Remove the optiknots table from the stack.
        lua_remove(L, -2);

        // Keep the Proxy userdata on the stack.
    }

    bool luax_istype(lua_State *L, int idx, opti::Type &type) {
        if (lua_type(L, idx) != LUA_TUSERDATA)
            return false;

        Proxy *p = static_cast<Proxy *>(lua_touserdata(L, idx));

        if (p->type != nullptr)
            return p->type->isa(type);
        else
            return false;
    }

    static Proxy *tryextractproxy(lua_State *L, int idx) {
        Proxy *u = (Proxy *)lua_touserdata(L, idx);

        if (u == nullptr || u->type == nullptr)
            return nullptr;

        if (dynamic_cast<Knot *>(u->knot) != nullptr)
            return u;

        return nullptr;
    }

    extern "C" int luax_typerror(lua_State *L, int narg, const char *tname) {
        int argtype = lua_type(L, narg);
        const char *argtname = nullptr;

        if (argtype == LUA_TUSERDATA && luaL_getmetafield(L, narg, "type") != 0) {
            lua_pushvalue(L, narg);
            if (lua_pcall(L, 1, 1, 0) == 0 && lua_type(L, narg) == LUA_TSTRING) {
                argtname = lua_tostring(L, narg);
                if (!Type::byName(argtname))
                    argtname = nullptr;
            }
        }

        if (argtname == nullptr)
            argtname = lua_typename(L, argtype);

        const char *msg = lua_pushfstring(L, "%s expected, got %s", tname, argtname);
        return luaL_argerror(L, narg, msg);
    }

    int luax_enumerror(lua_State *L, const char *enumName, const char *value) {
        return luaL_error(L, "Invalid %s: %s", enumName, value);
    }

    int luax_enumerror(lua_State *L, const char *enumName, const std::vector<std::string> &values, const char *value) {
        std::stringstream valueStream;
        bool first = true;
        for (auto value : values) {
            valueStream << (first ? "'" : ", '") << value << "'";
            first = false;
        }

        std::string valueString = valueStream.str();
        return luaL_error(L, "Invalid %s '%s', expected one of: %s", enumName, value, valueString.c_str());
    }

    size_t luax_objlen(lua_State *L, int ndx)
    {
#if LUA_VERSION_NUM == 501
        return lua_objlen(L, ndx);
#else
        return lua_rawlen(L, ndx);
#endif
    }

    Variant luax_checkvariant(lua_State *L, int n, bool allowuserdata, std::set<const void*> *tableSet) {
        size_t len;
        const char *str;
        Proxy *p = nullptr;

        if (n < 0)
            n += lua_gettop(L) + 1; // Fix the stack position

        switch (lua_type(L, n))
        {
        case LUA_TBOOLEAN:
            return Variant(luax_toboolean(L, n));
        case LUA_TNUMBER:
            return Variant(lua_tonumber(L, n));
        case LUA_TSTRING:
            str = lua_tolstring(L, n, &len);
            return Variant(str, len);
        case LUA_TLIGHTUSERDATA:
            return Variant(lua_touserdata(L, n));
        case LUA_TUSERDATA:
            if (!allowuserdata) {
                luax_typerror(L, n, "copyable value");
                return Variant();
            }
            p = tryextractproxy(L, n);
            if (p != nullptr)
                return Variant(p->type, p->knot);
            else {
                luax_typerror(L, n, "optibits type");
                return Variant();
            }
        case LUA_TNIL:
            return Variant();
        case LUA_TTABLE:
            {
                bool success = true;
                std::set<const void *> topTableSet;

                if (tableSet == nullptr)
                    tableSet = &topTableSet;

                const void *tablePointer = lua_topointer(L, n);
                {
                    auto result = tableSet->insert(tablePointer);
                    if (!result.second)
                        throw opti::Exception("Cycle detected in table");
                }

                Variant::SharedTable *table = new Variant::SharedTable();

                size_t len = luax_objlen(L, n);
                if (len > 0)
                    table->pairs.reserve(len);

                lua_pushnil(L);

                while (lua_next(L, n)) {
                    table->pairs.emplace_back(
                        luax_checkvariant(L, -2, allowuserdata, tableSet),
                        luax_checkvariant(L, -1, allowuserdata, tableSet)
                    );
                    lua_pop(L, 1); // pop the value

                    const auto &p = table->pairs.back();
                    if (p.first.getType() == Variant::UNKNOWN || p.second.getType() == Variant::UNKNOWN) {
                        success = false;
                        break;
                    }
                }

                tableSet->erase(tablePointer);

                if (success)
                    return Variant(table);
                else
                    table->release();
            }
            break;
        }

        return Variant::unknown();
    }

    void luax_pushvariant(lua_State *L, const Variant &v) {
        const Variant::Data &data = v.getData();

        switch (v.getType())
        {
        case Variant::BOOLEAN:
            lua_pushboolean(L, data.boolean);
            break;
        case Variant::NUMBER:
            lua_pushnumber(L, data.number);
            break;
        case Variant::STRING:
            lua_pushlstring(L, data.string->str, data.string->len);
            break;
        case Variant::SMALLSTRING:
            lua_pushlstring(L, data.smallstring.str, data.smallstring.len);
            break;
        case Variant::LUSERDATA:
            lua_pushlightuserdata(L, data.userdata);
            break;
        case Variant::OPTIKNOT:
            luax_pushtype(L, *data.knotproxy.type, data.knotproxy.knot);
            break;
        case Variant::TABLE:
        {
            std::vector<std::pair<Variant, Variant>> &table = data.table->pairs;
            int tsize = (int) table.size();

            lua_createtable(L, 0, tsize);

            for (int i = 0; i < tsize; ++i)
            {
                std::pair<Variant, Variant> &kv = table[i];
                luax_pushvariant(L, kv.first);
                luax_pushvariant(L, kv.second);
                lua_settable(L, -3);
            }

            break;
        }
        case Variant::NIL:
        default:
            lua_pushnil(L);
            break;
        }
    }

    int luax_getfunc(lua_State *L, const char *mod, const char *fn) {
        lua_getglobal(L, "opti");
        if (lua_isnil(L, -1)) return luaL_error(L, "Could not find global opti!");
        lua_getfield(L, -1, mod);
        if (lua_isnil(L, -1)) return luaL_error(L, "Could not find opti.%s!", mod);
        lua_getfield(L, -1, fn);
        if (lua_isnil(L, -1)) return luaL_error(L, "Could not find opti.%s.%s!", mod, fn);

        lua_remove(L, -2);
        lua_remove(L, -2);
        return 0;
    }

    int luax_convknot(lua_State *L, int idx, const char *mod, const char *fn) {
        if (idx < 0 && idx > LUA_REGISTRYINDEX)
            idx += lua_gettop(L) + 1;

        luax_getfunc(L, mod, fn);
        lua_pushvalue(L, idx);
        lua_call(L, 1, 2);
        luax_assert_nilerror(L, -2);
        lua_pop(L, 1);
        lua_replace(L, idx);
        return 0;
    }

    int luax_convknot(lua_State *L, const int idxs[], int n, const char *mod, const char *fn) {
        luax_getfunc(L, mod, fn);
        for (int i = 0; i < n; i++)
            lua_pushvalue(L, idxs[i]);
        lua_call(L, n, 2);
        luax_assert_nilerror(L, -2);
        lua_pop(L, 1);
        if (n > 0)
            lua_replace(L, idxs[0]);
        return 0;
    }

    int luax_convknot(lua_State *L, const std::vector<int>& idxs, const char *module, const char *function) {
        const int *idxPtr = idxs.size() > 0 ? &idxs[0] : nullptr;
        return luax_convknot(L, idxPtr, (int) idxs.size(), module, function);
    }

    // protected mode
    int luax_pconvknot(lua_State *L, int idx, const char *mod, const char *fn) {
        luax_getfunc(L, mod, fn);
        lua_pushvalue(L, idx);
        int ret = lua_pcall(L, 1, 1, 0);
        if (ret == 0)
            lua_replace(L, idx);
        return ret;
    }

    int luax_pconvobj(lua_State *L, const int idxs[], int n, const char *mod, const char *fn) {
        luax_getfunc(L, mod, fn);
        for (int i = 0; i < n; i++)
            lua_pushvalue(L, idxs[i]);

        int ret = lua_pcall(L, n, 1, 0);
        if (ret == 0)
            lua_replace(L, idxs[0]);
        return ret;
    }

    int luax_pconvobj(lua_State *L, const std::vector<int>& idxs, const char *module, const char *function)
    {
        const int *idxPtr = idxs.size() > 0 ? &idxs[0] : nullptr;
        return luax_pconvobj(L, idxPtr, (int) idxs.size(), module, function);
    }



}