
#include "audiocontroller.h"
#include "../pfx.h"
#include "soundfx.h"

void AudioController::ClearPlaylist()
{
	for( int i = 0; i < tracklist.Count(); i++ )
	{
		delete tracklist.At(i);
	}
	tracklist.Clear();
}

void AudioController::AddTrack(std::string Filename)
{
	tracklist.Add( new std::string( Filename ) );
}

#ifdef ALLEGRO

void AudioController::Initalise()
{
	soundfxvolume = 1.0f;
	musicvolume = 1.0f;
	crossfadesec = 3;
	audiostream = nullptr;
	audiocrossstream = nullptr;
	looptracks = true;
	playingtrack = false;

	al_reserve_samples( 20 );
	audiovoice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	if( audiovoice == nullptr )
	{
		FX->events.PushEvent( Event::ErrorEvent( "AudioController::Initialise", "Could not create Voice", false ) );
	}
	audiomixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	if( audiovoice == nullptr )
	{
		al_destroy_voice( audiovoice );
		audiovoice = nullptr;
		FX->events.PushEvent( Event::ErrorEvent( "AudioController::Initialise", "Could not create Mixer", false ) );
	}

	if( !al_attach_mixer_to_voice( audiomixer, audiovoice ) )
	{
		al_destroy_mixer( audiomixer );
		audiomixer = nullptr;
		al_destroy_voice( audiovoice );
		audiovoice = nullptr;
		FX->events.PushEvent( Event::ErrorEvent( "AudioController::Initialise", "Could not attach Mixer to Voice", false ) );
	}


	eventqueue = al_create_event_queue();
}

void AudioController::Shutdown()
{
	StopTrack();
	al_destroy_event_queue( eventqueue );
}

void AudioController::Update()
{
	ALLEGRO_EVENT ae;
	Event* fxe;

	while( al_get_next_event( eventqueue, &ae ) )
	{
		fxe = nullptr;

		switch( ae.type )
		{
			case ALLEGRO_EVENT_AUDIO_STREAM_FINISHED:
				StopTrack( false );
				if( tracklist.Count() == 0 )
				{
					fxe = new Event();
					fxe->type = EventTypes::EVENT_AUDIO_PLAYLIST_EMPTY;
					fxe->data.audio.reserved = 0;
				}
				if( crossfadesec <= 0 && tracklist.Count() > 0 )
				{
					fxe = new Event();
					fxe->type = EventTypes::EVENT_AUDIO_PLAYLIST_NEXT;
					fxe->data.audio.reserved = 0;
					PlayNextTrack();
				}
				break;

			default:
				break;
		}

		if( fxe != nullptr )
		{
			FX->events.PushEvent( fxe );
		}
	}

	UpdateCrossFadeVolumes();
}

void AudioController::UpdateCrossFadeVolumes()
{
	if( crossfadesec <= 0 )
	{
		return;
	}

	if( audiostream != nullptr )
	{
		double pos = al_get_audio_stream_position_secs( audiostream );
		double len = al_get_audio_stream_length_secs( audiostream );
		float trackvol = musicvolume;
		if( pos < crossfadesec )
		{
			trackvol = musicvolume * (pos / crossfadesec);
		} else if( pos >= len - crossfadesec ) {
			trackvol = musicvolume * ((len - pos) / crossfadesec);

			if( audiocrossstream == nullptr && tracklist.Count() > 0 )
			{
				Event* fxe = new Event();
				fxe->type = EventTypes::EVENT_AUDIO_PLAYLIST_NEXT;
				fxe->data.audio.reserved = 0;
				FX->events.PushEvent( fxe );
				PlayNextTrack( true );
			}

		}
		al_set_audio_stream_gain( audiostream, trackvol );
	}
	if( audiocrossstream != nullptr )
	{
		double pos = al_get_audio_stream_position_secs( audiocrossstream );
		double len = al_get_audio_stream_length_secs( audiocrossstream );
		float trackvol = musicvolume;
		if( pos < crossfadesec )
		{
			trackvol = musicvolume * (pos / crossfadesec);
		} else if( pos >= len - crossfadesec ) {
			trackvol = musicvolume * ((len - pos) / crossfadesec);
		}
		al_set_audio_stream_gain( audiocrossstream, trackvol );
	}

}

void AudioController::PlaySoundFX(SoundFX* Sound)
{
	al_play_sample( Sound->sfx, soundfxvolume, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr );
}

void AudioController::StopTrack()
{
	StopTrack( true );
}

void AudioController::StopTrack(bool StopAll)
{
	for( int i = 1; i <= (StopAll ? 2 : 1); i++ )
	{
		if( audiostream != nullptr )
		{
			al_unregister_event_source( eventqueue, al_get_audio_stream_event_source( audiostream ) );
			al_set_audio_stream_playing( audiostream, false );
			al_destroy_audio_stream( audiostream );
			audiostream = audiocrossstream; // nullptr;
			audiocrossstream = nullptr;
		}
	}
	playingtrack = false;
}

void AudioController::PlayNextTrack()
{
	PlayNextTrack( false );
}

void AudioController::PlayNextTrack(bool UsingSecondStream)
{
	if( !UsingSecondStream && audiostream != nullptr )
	{
		StopTrack();
	}

	if( tracklist.Count() == 0 )
	{
		return;
	}

	std::string* nexttrack = tracklist.At( 0 );
	tracklist.DeleteAt( 0 );

	ALLEGRO_AUDIO_STREAM* astream;

	astream = al_load_audio_stream( nexttrack->c_str(), 4, 2048 );
	if( astream == nullptr )
	{
		FX->events.PushEvent( Event::ErrorEvent( "AudioController::Initialise", "Could not play track: " + *nexttrack, false ) );
		return;
	}

	if( UsingSecondStream )
	{
		audiocrossstream = astream;
	} else {
		audiostream = astream;
	}

	al_attach_audio_stream_to_mixer( astream, audiomixer );
	al_set_audio_stream_playmode( astream, ALLEGRO_PLAYMODE_ONCE );
	al_register_event_source( eventqueue, al_get_audio_stream_event_source( astream ) );
	al_set_audio_stream_gain( astream, musicvolume );
	al_set_audio_stream_playing( astream, true );

	playingtrack = true;
	if( looptracks )
	{
		tracklist.Add( nexttrack );
	} else {
		delete nexttrack;
	}
}

void AudioController::ApplyVolume()
{
	if( audiostream != nullptr )
	{
		al_set_audio_stream_gain( audiostream, musicvolume );
	}
}

#endif // ALLEGRO
