#include "./lua/lua.hpp"
#include "./lua/lauxlib.h"
#include "./lua/lualib.h"

int xpos = 0;
int ypos = 0;

int setcoords(lua_State* lua);

int main( int argc, char* argv[] )
{
	int iErr = 0;
	lua_State *lua = luaL_newstate();  // Open Lua
	luaL_openlibs(lua);
	luaopen_base(lua);
	luaopen_io(lua);              // Load io library
	luaopen_string(lua);
	if ((iErr = luaL_loadfile(lua, "0.lua")) == 0)
	{
		// Call main...
		if ((iErr = lua_pcall(lua, 0, 0, 0)) == 0)
		{
			// Test function call
			iErr = lua_getglobal(lua, "f");
			iErr = lua_pcall(lua, 0, 0, 0);
			printf( "\n" );

			// Returns a string
			iErr = lua_getglobal(lua, "getName");
			if( lua_pcall(lua, 0, 1, 0) == 0 )
			{
				printf( "%s\n", lua_tostring( lua, -1 ) );
			}

			// Add C function to Lua script
			lua_pushcfunction(lua, setcoords);
			lua_setglobal(lua, "setcoords");
			// Call the lua version (which calls back to C)
			lua_getglobal(lua, "setxy");
			lua_pcall(lua, 0, 0, 0);
			printf("%d, %d", xpos, ypos);

		}
	}
	lua_close(lua);

}

int setcoords(lua_State* lua)
{
	xpos = lua_tonumber(lua, 1);
	ypos = lua_tonumber(lua, 2);
	return 0;
}