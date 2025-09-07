//
// Created by light on 7/19/25.
//

#include "Reference.h"
#include "runtime.h"
#include "../../ref/love/src/common/runtime.h"


namespace opti
{

    const char REFERENCE_TABLE_NAME[] = "opti-references";

    Reference::Reference()
        : pinnedL(nullptr)
        , idx(LUA_REFNIL)
    {
    }

    Reference::Reference(lua_State *L)
        : pinnedL(L)
        , idx(LUA_REFNIL)
    {
        ref(L);
    }

    Reference::~Reference()
    {}

    void Reference::ref(lua_State *L)
    {
    }



}
