
#pragma once

#include "./lua/lua.hpp"
#include "./lua/lauxlib.h"
#include "./lua/lualib.h"

class ScriptController
{

	private:
		lua_State* vm;

	public:
		ScriptController();
		~ScriptController();

		void Update();

};
