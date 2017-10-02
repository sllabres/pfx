
#include "textedit.h"
#include "../pfx.h"

TextEdit::TextEdit(Control* Parent, std::string Text) : Control( Parent )
{
	horizontalalignment = HorizontalAlignment::Left;
	verticalalignment = VerticalAlignment::Centre;
	text = Text;
	previoustext = text;
	selectionstart = text.length();
	selectionlength = 0;
	caretdrawtimer = FX->CreateTimer(0.5f);
	border = BorderStyle::Depressed;
	editing = false;
	canfocus = true;
	backgroundcolour = UI_COLOURS_EDIT;
	foregroundcolour = UI_COLOURS_EDIT_TEXT;
}

TextEdit::TextEdit(Control* Parent, Point<int> Position, Size<int> Dimensions, std::string Text) : Control( Parent, Position, Dimensions )
{
	horizontalalignment = HorizontalAlignment::Left;
	verticalalignment = VerticalAlignment::Centre;
	text = Text;
	previoustext = text;
	position = Position;
	size = Dimensions;
	selectionstart = text.length();
	selectionlength = 0;
	caretdrawtimer = FX->CreateTimer(0.5f);
	border = BorderStyle::Depressed;
	editing = false;
	canfocus = true;
	backgroundcolour = UI_COLOURS_EDIT;
	foregroundcolour = UI_COLOURS_EDIT_TEXT;
}

TextEdit::~TextEdit()
{
	FX->DeleteTimer(caretdrawtimer);
}

void TextEdit::EventOccured(Event* What)
{
	Control::EventOccured( What );
	if( What->handled )
	{
		return;
	}

	if( What->type == EventTypes::EVENT_TIMER_TICK && What->data.timer.id == caretdrawtimer )
	{
		drawcaret = !drawcaret;
	}
	if( What->type == EventTypes::EVENT_UI_INTERACTION && What->data.ui.source == this )
	{
		switch( What->data.ui.eventtype )
		{
			case FormEventType::GotFocus:
				editing = true;
				break;
			case FormEventType::LostFocus:
				editing = false;
				break;
			case FormEventType::KeyPress:
				switch( What->data.ui.keyinfo.keycode )
				{
					case KEYCODE_TAB:
						if( acceptstab )
						{
							text += "\t";
						}
						break;
					case KEYCODE_HOME:
						selectionstart = 0;
						break;
					case KEYCODE_END:
						selectionstart = text.length();
						break;
					case KEYCODE_LEFT:
						selectionstart = Maths::Max( selectionstart - 1, 0 );
						break;
					case KEYCODE_RIGHT:
						selectionstart = Maths::Min( selectionstart + 1, text.length() );
						break;
					case KEYCODE_DELETE:
						if( selectionstart < text.length() )
						{
							text.erase( text.begin() + selectionstart, text.begin() + selectionstart + 1 );
						}
						break;
					case KEYCODE_BACKSPACE:
						if( selectionstart > 0 )
						{
							text.erase( text.begin() + selectionstart - 1, text.begin() + selectionstart );
							selectionstart--;
						}
						break;
					default:
						if( What->data.ui.keyinfo.character != nullptr )
						{
							text.insert( selectionstart, What->data.ui.keyinfo.character->c_str() );
							selectionstart++;
						}
						break;
				}
				break;
		}
		What->handled = true;
	}
}

void TextEdit::Update()
{
	if( previoustext != text )
	{
		Event* e = new Event();
		e->type = EventTypes::EVENT_UI_INTERACTION;
		e->data.ui.source = this;
		e->data.ui.eventtype = FormEventType::TextChanged;
		previoustext = text;
		FX->events.PushEvent( e );
	}
}

void TextEdit::OnRender()
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

	if( editing && drawcaret )
	{
		int caretoffset = workfont->MeasureText( text.substr(0, selectionstart) ).w;
		int caretheight = Maths::Min( size.h, workfont->MeasureText( text ).h );
		cachedrender->DrawLine( Line<int>(p.x + caretoffset, p.y, p.x + caretoffset, p.y + caretheight), foregroundcolour, 1 );
	}
}

