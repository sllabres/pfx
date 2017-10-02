
#pragma once

#include "../libraryincludes.h"
#include "../text/strings.h"

class SoundFX
{

	public:
#ifdef ALLEGRO
		ALLEGRO_SAMPLE* sfx;
#endif // ALLEGRO

		SoundFX(std::string Filename);
		~SoundFX();

};
