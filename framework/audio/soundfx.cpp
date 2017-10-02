
#include "soundfx.h"

SoundFX::SoundFX(std::string Filename)
{
	sfx = al_load_sample( Filename.c_str() );
}

SoundFX::~SoundFX()
{
	al_destroy_sample( sfx );
}
