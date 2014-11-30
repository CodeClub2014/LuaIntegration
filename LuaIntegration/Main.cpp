#include <cstdio>

#include <string>

// Extern "c" because the library is written in C, not C++
extern "C"
{
	#include <lua/lua.h>
	#include <lua/lauxlib.h>
	#include <lua/lualib.h>
}

int luaPrint(lua_State *state)
{
	// 'state' contains the information about the vm that called the function, including arguments.

	// Check that the first argument is string, not something else
	if (lua_type(state, 1) != LUA_TSTRING)
	{
		printf("luaPrint requires a string to print something!");
		return 0; // Return error code!
	}

	// Argument has been checked to be good, lets get the string out from it
	std::string argument = lua_tostring(state, 1);

	// Regular c++ functionality
	printf("%s\n", argument);

	return 1; // All ok tell vm that the call was good and executed
}

int main()
{
	// Creating the lua state
	lua_State *state = luaL_newstate();

	// load the default lua stuff into the vm
	luaL_openlibs(state);

	// Bind a C++ function to be used in lua.
	// Args: 1) state to be used
	//       2) function name in lua
	//       3) function pointer for the c++ function to be called
	lua_register(state, "luaprint", &luaPrint);

	// Load the file to be used into vm
	luaL_loadfile(state, "helloworld.lua");

	// Execute contents in the lua, basically loads the function in .lua main so that we can then call them.
	lua_pcall(state, 0, LUA_MULTRET, 0);

	// LUA INITIALIZATION DONE!

	// get the function that should be called
	lua_getglobal(state, "hello");

	// lua_push<type> to push arguments, but thats not needed here because hello() doesn't have arguments

	// Call the function that was just set, with 0 argument and 0 results
	lua_call(state, 0, 0);

	return 0;
}