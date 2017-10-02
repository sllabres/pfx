
#include "button.h"
#include "../pfx.h"

Button::Button(Control* Parent, std::string Text) : Control( Parent )
{
	horizontalalignment = HorizontalAlignment::Centre;
	verticalalignment = VerticalAlignment::Centre;
	image = nullptr;
	text = Text;
	border = BorderStyle::Raised;
	border_standard = BorderStyle::Raised;
	border_depressed = BorderStyle::Depressed;
	canfocus = true;
	depressed = false;
}

Button::Button(Control* Parent, Point<int> Position, Size<int> Dimensions, std::string Text) : Control( Parent, Position, Dimensions )
{
	horizontalalignment = HorizontalAlignment::Centre;
	verticalalignment = VerticalAlignment::Centre;
	image = nullptr;
	text = Text;
	position = Position;
	size = Dimensions;
	border = BorderStyle::Raised;
	border_standard = BorderStyle::Raised;
	border_depressed = BorderStyle::Depressed;
	canfocus = true;
	depressed = false;
}

Button::~Button()
{
}

void Button::EventOccured(Event* What)
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
			case FormEventType::MouseLeave:
				if( depressed )
				{
					border = border_standard;
					depressed = false;
				}
				break;
			case FormEventType::KeyDown:
				switch( What->data.ui.keyinfo.keycode )
				{
					case KEYCODE_SPACE:
					case KEYCODE_ENTER:
						depressed = true;
						border = border_depressed;
						break;
				}
				break;
			case FormEventType::KeyUp:
				switch( What->data.ui.keyinfo.keycode )
				{
					case KEYCODE_SPACE:
					case KEYCODE_ENTER:
						if( depressed )
						{
							depressed = false;
							border = border_standard;
							e = new Event();
							e->type = EventTypes::EVENT_UI_INTERACTION;
							e->data.ui.source = this;
							e->data.ui.eventtype = FormEventType::ButtonClick;
							FX->events.PushEvent( e );
						}
						break;
				}
				break;
			case FormEventType::MouseDown:
				if( What->data.ui.mouseinfo.button == 1 )
				{
					depressed = true;
					border = border_depressed;
				}
				break;
			case FormEventType::MouseUp:
				if( What->data.ui.mouseinfo.button == 1 && depressed )
				{
					e = new Event();
					e->type = EventTypes::EVENT_UI_INTERACTION;
					e->data.ui.source = this;
					e->data.ui.eventtype = FormEventType::ButtonClick;
					FX->events.PushEvent( e );
				}
				depressed = false;
				border = border_standard;
				break;
		}
		What->handled = true;
	}
}

void Button::Update()
{
}

void Button::OnRender()
{
	Point<int> p;
	Font* workfont = ResolveFont();
	if( workfont == nullptr )
	{
		return;
	}

	switch( horizontalalignment )
	{
		case HorizontalAlignment::Left:
			p.x = 2;
			break;
		case HorizontalAlignment::Right:
			p.x = size.w - 2 - workfont->MeasureText( text ).w;
			break;
		case HorizontalAlignment::Centre:
			p.x = (size.w - 2 - workfont->MeasureText( text ).w) / 2;
			break;
	}
	switch( verticalalignment )
	{
		case VerticalAlignment::Top:
			p.y = 2;
			break;
		case VerticalAlignment::Bottom:
			p.y = size.h - 2 - workfont->MeasureText( text ).h;
			break;
		case VerticalAlignment::Centre:
			p.y = (size.h - 2 - workfont->MeasureText( text ).h) / 2;
			break;
	}

	workfont->RenderTextInto( cachedrender, p, text, foregroundcolour );

}

