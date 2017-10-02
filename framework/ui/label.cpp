
#include "label.h"


Label::Label(Control* Parent, std::string Text) : Control( Parent )
{
	horizontalalignment = HorizontalAlignment::Left;
	verticalalignment = VerticalAlignment::Centre;
	text = Text;
}

Label::Label(Control* Parent, Point<int> Position, Size<int> Dimensions, std::string Text) : Control( Parent, Position, Dimensions )
{
	horizontalalignment = HorizontalAlignment::Left;
	verticalalignment = VerticalAlignment::Centre;
	text = Text;
	position = Position;
	size = Dimensions;
}

Label::~Label()
{
}

void Label::EventOccured(Event* What)
{
	Control::EventOccured( What );
}

void Label::Update()
{
}

void Label::OnRender()
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
			p.x = 0;
			break;
		case HorizontalAlignment::Right:
			p.x = size.w - workfont->MeasureText( text ).w;
			break;
		case HorizontalAlignment::Centre:
			p.x = (size.w - workfont->MeasureText( text ).w) / 2;
			break;
	}
	switch( verticalalignment )
	{
		case VerticalAlignment::Top:
			p.y = 0;
			break;
		case VerticalAlignment::Bottom:
			p.y = size.h - workfont->MeasureText( text ).h;
			break;
		case VerticalAlignment::Centre:
			p.y = (size.h - workfont->MeasureText( text ).h) / 2;
			break;
	}

	workfont->RenderTextInto( cachedrender, p, text, foregroundcolour );
}
