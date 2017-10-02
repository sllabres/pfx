
#include "scriptcontroller.h"

ScriptController::ScriptController()
{
	vm = luaL_newstate();
	luaL_openlibs(vm);
	luaopen_base(vm);
	luaopen_io(vm);
	luaopen_string(vm);
}

ScriptController::~ScriptController()
{
	lua_close( vm );
}

void ScriptController::Update()
{
}
