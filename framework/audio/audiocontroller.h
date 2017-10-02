
#pragma once

#include "../libraryincludes.h"
#include "../text/strings.h"
#include "soundfx.h"

class AudioController
{

	private:
		List<std::string*> tracklist;


#ifdef ALLEGRO
		ALLEGRO_EVENT_QUEUE* eventqueue;
		ALLEGRO_VOICE* audiovoice;
		ALLEGRO_MIXER* audiomixer;
		ALLEGRO_AUDIO_STREAM* audiostream;
		ALLEGRO_AUDIO_STREAM* audiocrossstream;

#endif // ALLEGRO

		void UpdateCrossFadeVolumes();

	public:
		float soundfxvolume;
		float musicvolume;
		float crossfadesec;
		bool looptracks;
		bool playingtrack;

		void Initalise();
		void Shutdown();

		void Update();

		void PlaySoundFX(SoundFX* Sound);

		void ClearPlaylist();
		void AddTrack(std::string Filename);
		void StopTrack();
		void StopTrack(bool StopAll);
		void PlayNextTrack();
		void PlayNextTrack(bool UsingSecondStream);

		void ApplyVolume();

};
