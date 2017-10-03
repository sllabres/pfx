
#include "../framework/pfx.h"
#include "boot.h"
#include <Windows.h>

int main( int argc, char* argv[] )
{
	FreeConsole();
	PFx* framework = new PFx();

	framework->Execute( new BootUp() );

	return 0;
}
