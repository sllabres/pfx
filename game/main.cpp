
#include "../framework/pfx.h"
#include "boot.h"

int main( int argc, char* argv[] )
{
	PFx* framework = new PFx();

	framework->Execute( new BootUp() );

	return 0;
}
