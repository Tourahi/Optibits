//
// Created by light on 7/19/25.
//

#ifndef REFERENCE_H
#define REFERENCE_H

struct lua_State;

namespace opti
{
    /**
     * This class wraps the reference functionality built into
     * Lua, which allows C++ code to refer to Lua variables.
     */
    class Reference
    {
    public:

        /**
         * Creates the reference object, but does not create
         * the actual reference.
         */
        Reference();

        /**
         * Creates the object and a reference to the value
         * on the top of the stack.
         */
        explicit Reference(lua_State *L);

        virtual ~Reference();

        /**
         * creates a reference to the top of the stack.
         * @param L
         */
        void ref(lua_State *L);

        /**
         * unref the reference
         */
        void unref();


    private:

        // A pinned coroutine (probably the main thread) belonging to the Lua state
        // in which the reference resides.
        lua_State *pinnedL;

        // Index to the lua reference.
        int idx;
    };

} // opti

#endif //REFERENCE_H
