
#pragma once

#include "keycodes/pfxkeys.h"
#include "../events/event.h"
#include "../primitives/point.h"

// USB keyboards support 6 usually, not sure if that include the modifier keys as well though
// but 20 should be more than enough without wasting too much space
#define PFX_MAX_CONCURRENT_KEYS 20

class Keyboard
{

	private:
		unsigned int keycodesdepressed[PFX_MAX_CONCURRENT_KEYS];
		unsigned int keycodesdepressedcount;
		List<Point<unsigned int>*> keymapping;

	public:
		Keyboard();

		void OnEvent(Event* What);

		bool IsKeyDown(unsigned int PFxKeyCode);

		void LoadMapping(std::string Filename);
		void SaveMapping(std::string Filename);
		bool IsMappedKeyDown(unsigned int KeyID);
		void SetKeyMap(unsigned int KeyID, unsigned int PFxKeyCode);
		unsigned int GetMappedKeyID(unsigned int PFxKeyCode);

};
