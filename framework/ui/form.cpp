
#include "form.h"
#include "../pfx.h"

Form::Form() : Control( nullptr )
{
	activecontrol = nullptr;
	border = BorderStyle::Raised;
}

Form::~Form()
{
}

void Form::SetFocus(Control* Item)
{
	Event* e = nullptr;

	if( activecontrol == Item )
	{
		return;
	}

	if( activecontrol != nullptr )
	{
		e = new Event();
		e->type = EventTypes::EVENT_UI_INTERACTION;
		e->data.ui.eventtype = FormEventType::LostFocus;
		e->data.ui.source = activecontrol;
		memset( (void*)&e->data.ui.keyinfo, 0, sizeof( EventDataInputKeyboard ) );
		memset( (void*)&e->data.ui.mouseinfo, 0, sizeof( EventDataInputMouse ) );
		e->data.ui.additionaldata = nullptr;
		FX->events.PushEvent( e );
		FX->PumpEvents();
	}
	activecontrol = Item;
	if( activecontrol != nullptr )
	{
		e = new Event();
		e->type = EventTypes::EVENT_UI_INTERACTION;
		e->data.ui.eventtype = FormEventType::GotFocus;
		e->data.ui.source = activecontrol;
		memset( (void*)&e->data.ui.keyinfo, 0, sizeof( EventDataInputKeyboard ) );
		memset( (void*)&e->data.ui.mouseinfo, 0, sizeof( EventDataInputMouse ) );
		e->data.ui.additionaldata = nullptr;
		FX->events.PushEvent( e );
	}

}

void Form::FocusNext()
{
	GenerateFocusList( this );
	for( int c = 0; c < focusablecontrols.Count(); c++ )
	{
		if( focusablecontrols.At( c ) == activecontrol )
		{
			int idx = (c + 1) % focusablecontrols.Count();
			SetFocus( focusablecontrols.At( idx ) );
			return;
		}
	}
}

void Form::FocusPrevious()
{
	GenerateFocusList( this );
	for( int c = 0; c < focusablecontrols.Count(); c++ )
	{
		if( focusablecontrols.At( c ) == activecontrol )
		{
			int idx = (c + focusablecontrols.Count() - 1) % focusablecontrols.Count();
			SetFocus( focusablecontrols.At( idx ) );
			return;
		}
	}
}

Control* Form::GetFocusedControl()
{
	return activecontrol;
}

void Form::EventOccured(Event* What)
{
	Control::EventOccured( What );
}

void Form::Update()
{
	Control::Update();
	ResolveLocation();
}

void Form::GenerateFocusList(Control* Parent)
{
	if( Parent == this )
	{
		focusablecontrols.Clear();
	}

	for( int c = 0; c < controls.Count(); c++ )
	{
		Control* ctl = controls.At( c );
		if( ctl->canfocus )
		{
			focusablecontrols.Add( ctl );
		}
		if( ctl->controls.Count() > 0 )
		{
			GenerateFocusList( ctl );
		}
	}
}

void Form::OnRender()
{
}
