
#include "checkbox.h"
#include "../pfx.h"

CheckBox::CheckBox(Control* Parent) : Control( Parent )
{
	border = BorderStyle::Depressed;
	canfocus = true;
	checked = false;
	depressed = false;
	backgroundcolour = UI_COLOURS_EDIT;
	foregroundcolour = UI_COLOURS_EDIT_TEXT;
}

CheckBox::CheckBox(Control* Parent, Point<int> Position, Size<int> Dimensions) : Control( Parent, Position, Dimensions )
{
	position = Position;
	size = Dimensions;
	border = BorderStyle::Depressed;
	canfocus = true;
	checked = false;
	depressed = false;
	backgroundcolour = UI_COLOURS_EDIT;
	foregroundcolour = UI_COLOURS_EDIT_TEXT;
}

CheckBox::~CheckBox()
{
}

void CheckBox::EventOccured(Event* What)
{
	Event* e;

	Control::EventOccured( What );
	if( What->handled )
	{
		return;
	}

	if( What->type == EventTypes::EVENT_UI_INTERACTION && What->data.ui.source == this )
	{
		switch( What->data.ui.eventtype )
		{
			case FormEventType::GotFocus:
				break;
			case FormEventType::LostFocus:
				break;
			case FormEventType::KeyPress:
				switch( What->data.ui.keyinfo.keycode )
				{
					case KEYCODE_SPACE:
					case KEYCODE_ENTER:
						checked = !checked;
						e = new Event();
						e->type = EventTypes::EVENT_UI_INTERACTION;
						e->data.ui.source = this;
						e->data.ui.eventtype = FormEventType::CheckBoxChange;
						FX->events.PushEvent( e );
						break;
				}
				break;
			case FormEventType::MouseDown:
				if( What->data.ui.mouseinfo.button == 1 )
				{
					depressed = true;
				}
				break;
			case FormEventType::MouseUp:
				if( What->data.ui.mouseinfo.button == 1 && depressed )
				{
					depressed = false;
					checked = !checked;
					e = new Event();
					e->type = EventTypes::EVENT_UI_INTERACTION;
					e->data.ui.source = this;
					e->data.ui.eventtype = FormEventType::CheckBoxChange;
					FX->events.PushEvent( e );
				}
				break;
		}
		What->handled = true;
	}
}

void CheckBox::Update()
{
	if( size.w < 8 )
	{
		size.w = 8;
	}
	if( size.h < 8 )
	{
		size.h = 8;
	}
}

void CheckBox::OnRender()
{
	if( checked )
	{
		cachedrender->FillRectangle( Rect<int>( 2, 2, size.w - 4, size.h - 4 ), foregroundcolour );
	}
}

