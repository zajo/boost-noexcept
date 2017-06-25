extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
}
#include <boost/noexcept.hpp>
#include <iostream>
#include <stdlib.h>

using namespace boost::noexcept_;

struct do_work_error { };
int do_work( lua_State * L ) noexcept;

std::shared_ptr<lua_State> init_lua_state() noexcept {  //<1>
    std::shared_ptr<lua_State> L(lua_open(),&lua_close);
    luaL_dostring( &*L, "\
\n      function call_do_work()\
\n          return do_work()\
\n      end" );
    lua_register( &*L, "do_work", &do_work );
    return L;
}

int do_work( lua_State * L ) noexcept {
    bool success=rand()%2;
    if( success )
        return lua_pushnumber(L,42), 1;  //<2>
    else
        return throw_(do_work_error()), lua_error(L);  //<3>
}

int call_lua( lua_State * L ) noexcept {  //<4>
    lua_getfield( L, LUA_GLOBALSINDEX, "call_do_work" );
    if( int err=lua_pcall(L,0,1,0) ) {
        lua_pop(L,1);
        return throw_();
    }
    else {
        int answer=lua_tonumber(L,-1);
        lua_pop(L,1);
        return answer;
    }
}

int main() {
    std::shared_ptr<lua_State> L=init_lua_state();
    for( int i=0; i!=10; ++i ) {
        if( auto r=try_(call_lua(&*L)) )
            std::cout << "do_work succeeded, answer=" << r.get() << '\n';
        else if( auto err=r.catch_<do_work_error>() )  //<5>
            std::cout << "do_work failed!\n";
    }
    return 0;
}
