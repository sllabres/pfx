
#pragma once

#include "libraryincludes.h"
#include "audio/audiocontroller.h"
#include "core/idtag.h"
#include "core/endian.h"
#include "core/matrix2.h"
#include "core/memorystream.h"
#include "core/pingpong.h"
#include "events/eventcontroller.h"
#include "filesys/filesystem.h"
#include "input/inputcontroller.h"
#include "network/downloadcontroller.h"
#include "network/networkcontroller.h"
#include "primitives/ellipses.h"
#include "primitives/polygon.h"
#include "primitives/rect.h"
#include "scripting/scriptcontroller.h"
#include "stages/stagecontroller.h"
#include "ui/plane_ui.h"
#include "video/videocontroller.h"

#define FX	PFx::FxInst

class FrameRateControlMethods
{
	public:
		enum FrameRateControlMethod
		{
			DropFrames,
			SlowGame
		};
};

class PFx
{

	private:
		bool shutdown;
		int framespersecond;
		FrameRateControlMethods::FrameRateControlMethod framecontrol;
		int framestoprocess;
		int frametimerid;

#ifdef ALLEGRO
		int timernextid;
		List<IDTag<ALLEGRO_TIMER*>*> timers;
#endif // ALLEGRO

	public:
		static PFx* FxInst;

		AudioController audio;
		EventController events;
		InputController input;
		NetworkController network;
		DownloadController downloads;
		StageController stages;
		VideoController video;

		PFx();
		~PFx();

		bool InitaliseLibraries();
		void ShutdownLibraries();

		void Execute(Stage* BootStage);
		void PumpEvents();

		void Shutdown();
		bool IsShuttingDown();

		FrameRateControlMethods::FrameRateControlMethod GetFrameControl();
		void SetFrameControl(FrameRateControlMethods::FrameRateControlMethod NewMethod);
		int GetFrameRate();
		void SetFrameRate(int NewRate);

		void SetApplicationName(std::string Name);

		int CreateTimer(float IntervalSec);
		void DeleteTimer(int ID);

#ifdef ALLEGRO
		int TimerToID(ALLEGRO_TIMER* What);
#endif // ALLEGRO

		void WriteLog(std::string* FunctionName, std::string* Message);
};
