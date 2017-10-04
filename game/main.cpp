
#include "../framework/pfx.h"
#include "title.h"
#include <Windows.h>

int main( int argc, char* argv[] )
{
	FreeConsole();
	PFx* framework = new PFx();
	framework->Execute( new Title() );
	return 0;
}
