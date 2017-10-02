
#pragma once

#include "../core/memory.h"
#include "../text/strings.h"
#include "../ui/formenum.h"

#ifndef Playlist
class Playlist;
#endif // Playlist

#ifndef ScriptController
class ScriptController;
#endif // ScriptController

#ifndef Display
class Display;
#endif // Display

#ifndef Plane
class Plane;
#endif // Plane

#ifndef Joystick
class Joystick;
#endif // Joystick

#ifndef Control
class Control;
#endif // Control

class EventTypes
{
	public:
		enum EventTypeCodes
		{
			EVENT_QUIT,
			EVENT_LOG,
			EVENT_ERROR,
			EVENT_VIDEO_ACTIVATE,
			EVENT_VIDEO_DEACTIVATE,
			EVENT_VIDEO_RESIZED,
			EVENT_VIDEO_MANAGER,
			EVENT_VIDEO_CLOSE,
			EVENT_AUDIO_PLAYLIST_NEXT,
			EVENT_AUDIO_PLAYLIST_EMPTY,
			EVENT_INPUT_KEYBOARD_KEYDOWN,
			EVENT_INPUT_KEYBOARD_KEYUP,
			EVENT_INPUT_KEYBOARD_KEYPRESS,
			EVENT_INPUT_MOUSE_BUTTONDOWN,
			EVENT_INPUT_MOUSE_BUTTONUP,
			EVENT_INPUT_MOUSE_MOVE,
			EVENT_INPUT_JOYSTICK_BUTTONDOWN,
			EVENT_INPUT_JOYSTICK_BUTTONUP,
			EVENT_INPUT_JOYSTICK_AXIS,
			EVENT_INPUT_JOYSTICK_HAT,
			EVENT_INPUT_JOYSTICK_BALL,
			EVENT_TIMER_TICK,
			EVENT_NETWORK_CONNECTIONREQUEST,
			EVENT_NETWORK_CONNECTED,
			EVENT_NETWORK_PACKETRECEIVED,
			EVENT_NETWORK_DISCONNECTED,
			EVENT_DOWNLOAD_STARTING,
			EVENT_DOWNLOAD_PROGRESS,
			EVENT_DOWNLOAD_COMPLETE,
			EVENT_UI_INTERACTION,
			EVENT_SCRIPT_COMPLETE,
			EVENT_UNDEFINED,
			EVENT_USER
		};
};

typedef struct EventDataLog
{
	std::string* message;
	std::string* functionname;
} EventDataLog;

typedef struct EventDataError
{
	std::string* message;
	std::string* functionname;
	bool critical;
} EventDataError;

typedef struct EventDataVideo
{
	Display* display;
	Plane* plane;
	bool active;
	int x;
	int y;
	int width;
	int height;
} EventDataVideo;

typedef struct EventDataAudio
{
	int reserved;
} EventDataAudio;

typedef struct EventDataInputKeyboard
{
	unsigned int keycode;
	unsigned int mappedkeyid;
	std::string* character;
	unsigned int modifiers;
} EventDataInputKeyboard;

typedef struct EventDataInputMouse
{
	int x;
	int y;
	int wheelvertical;
	int wheelhorizontal;
	int deltax;
	int deltay;
	int button;
	Display* display;
} EventDataInputMouse;

typedef struct EventDataInputJoystick
{
	Joystick* joystick;
	int hat;
	int axis;
	float position;
	int button;
} EventDataInputJoystick;

typedef union EventDataInput
{
	EventDataInputKeyboard keyboard;
	EventDataInputMouse mouse;
	EventDataInputJoystick joystick;
} EventDataInput;

typedef struct EventDataTimer
{
	int id;
	unsigned long ticks;
} EventDataTimer;

typedef struct EventDataNetwork
{
	bool isserver;
	unsigned int clientid;
	Memory* packet;
} EventDataNetwork;

typedef struct EventDataDownload
{
	std::string* url;
	Memory* data;
	unsigned long downloadedbytes;
	unsigned long uploadedbytes;
	unsigned long totalbytes;
} EventDataDownload;

typedef struct EventDataUI
{
	FormEventType eventtype;
	Control* source;
	EventDataInputKeyboard keyinfo;
	EventDataInputMouse mouseinfo;
	Memory* additionaldata;
} EventDataUI;

typedef struct EventDataScript
{
	ScriptController* source;
} EventDataScript;

typedef union EventData
{
	EventDataLog log;
	EventDataError error;
	EventDataVideo video;
	EventDataAudio audio;
	EventDataInput input;
	EventDataTimer timer;
	EventDataNetwork network;
	EventDataDownload download;
	EventDataUI ui;
	EventDataScript script;
} EventData;

class Event
{

	public:
		bool handled;
		EventTypes::EventTypeCodes type;
		EventData data;

		Event() { handled = false; };

		static Event* LogEvent(std::string FunctionName, std::string Message)
		{
			Event* fxe = new Event();
			fxe->type = EventTypes::EVENT_LOG;
			fxe->data.log.functionname = new std::string(FunctionName);
			fxe->data.log.message = new std::string(Message);
			fxe->handled = false;
			return fxe;
		};

		static Event* ErrorEvent(std::string FunctionName, std::string Message, bool Critical)
		{
			Event* fxe = new Event();
			fxe->type = EventTypes::EVENT_ERROR;
			fxe->data.error.functionname = new std::string(FunctionName);
			fxe->data.error.message = new std::string(Message);
			fxe->data.error.critical = Critical;
			fxe->handled = false;
			return fxe;
		};

};
