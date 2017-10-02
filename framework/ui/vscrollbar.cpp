
#include "vscrollbar.h"
#include "../pfx.h"

VScrollbar::VScrollbar(Control* Parent) : Control( Parent )
{
	buttondragx = 0;
	buttoninside = 0;
	border = BorderStyle::None;
	canfocus = true;
	minimum = 0;
	maximum = 10;
	value = 0;
	ConfigureUI();
}

VScrollbar::VScrollbar(Control* Parent, Point<int> Position, Size<int> Dimensions) : Control( Parent, Position, Dimensions )
{
	buttondragx = 0;
	buttoninside = 0;
	position = Position;
	size = Dimensions;
	border = BorderStyle::None;
	canfocus = true;
	minimum = 0;
	maximum = 10;
	value = 0;
	ConfigureUI();
}

VScrollbar::~VScrollbar()
{
}

void VScrollbar::ConfigureUI()
{
}

void VScrollbar::EventOccured(Event* What)
{
	Event* e;
	bool valuewaschanged = false;

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
					case KEYCODE_UP:
						if( value > minimum )
						{
							value--;
							valuewaschanged = true;
						}
						break;
					case KEYCODE_DOWN:
						if( value < maximum )
						{
							value++;
							valuewaschanged = true;
						}
						break;
				}
				break;
			case FormEventType::MouseDown:
				if( What->data.ui.mouseinfo.button == 1 )
				{
					Point<int> mousept = Point<int>(What->data.ui.mouseinfo.x, What->data.ui.mouseinfo.y);
					if( leftbutton.IsPointInside(mousept) )
					{
						buttoninside = 1;
					} else if( rightbutton.IsPointInside(mousept) ) {
						buttoninside = 2;
					} else if( sliderbutton.IsPointInside(mousept) ) {
						buttondragx = mousept.x;
						buttoninside = 3;
					} else {
						buttoninside = 4;
					}
				}
				break;
			case FormEventType::MouseUp:
				break;
			case FormEventType::MouseMove:
				if( buttoninside == 3 )
				{
					if( What->data.ui.mouseinfo.y <= leftbutton.Bottom() )
					{
						value = minimum;
						valuewaschanged = true;
					} else if( What->data.ui.mouseinfo.y >= rightbutton.Top() ) {
						value = maximum;
						valuewaschanged = true;
					} else {
						int offsy = What->data.ui.mouseinfo.y - leftbutton.Bottom();
						int segments = (maximum - minimum) + 1;
						int workingspace = size.h - leftbutton.h - rightbutton.h;
						float segmentsize = (float)workingspace / (float)segments;
						value = (int)Maths::Min((float)maximum, Maths::Max( (float)minimum, minimum + ((float)offsy / segmentsize) ));
						valuewaschanged = true;
					}
				}
				break;
			case FormEventType::MouseLeave:
				if( buttoninside != 3 )
				{
					buttoninside = 0;
				}
				break;
			case FormEventType::MouseClick:
				switch( buttoninside )
				{
					case 1:
						if( value > minimum )
						{
							value--;
							valuewaschanged = true;
						}
						break;
					case 2:
						if( value < maximum )
						{
							value++;
							valuewaschanged = true;
						}
						break;
					case 4:
						if( What->data.ui.mouseinfo.y < sliderbutton.Left() )
						{
							if( value > minimum )
							{
								value--;
								valuewaschanged = true;
							}
						}
						if( What->data.ui.mouseinfo.y > sliderbutton.Right() )
						{
							if( value < maximum )
							{
								value++;
								valuewaschanged = true;
							}
						}
						break;
				}
				buttoninside = 0;
				break;

		}
		What->handled = true;
	}

	if( valuewaschanged )
	{
		e = new Event();
		e->type = EventTypes::EVENT_UI_INTERACTION;
		e->data.ui.source = this;
		e->data.ui.eventtype = FormEventType::ScrollBarChange;
		FX->events.PushEvent( e );
	}
}

void VScrollbar::Update()
{
	if( maximum < minimum )
	{
		maximum = minimum;
	}
	if( value > maximum )
	{
		value = maximum;
	}
	if( value < minimum )
	{
		value = minimum;
	}

	if( size.w < 8 )
	{
		size.w = 8;
	}
	if( size.h < size.w * 3 )
	{
		size.h = size.w / 3;
	}
	sliderbutton.w = size.w;
	sliderbutton.h = (size.h - (size.w * 2)) / (maximum - minimum);
	if( sliderbutton.h < size.w )
	{
		sliderbutton.h = size.w;
	}
	leftbutton.h = size.w;
	leftbutton.w = size.w;
	rightbutton.y = size.h - size.w;
	rightbutton.h = size.w;
	rightbutton.w = size.w;

	int workingspace = (size.h - (size.w * 2)) - sliderbutton.h;
	float sx = ((float)workingspace / (float)(maximum - minimum)) * value;
	sliderbutton.y = size.w + sx;

}

void VScrollbar::OnRender()
{
	cachedrender->Draw3DRectangle(leftbutton, UI_COLOURS_CONTROL_HI, UI_COLOURS_CONTROL_LO, 1, (buttoninside == 1 ? false : true));
	cachedrender->Draw3DRectangle(rightbutton, UI_COLOURS_CONTROL_HI, UI_COLOURS_CONTROL_LO, 1, (buttoninside == 2 ? false : true));
	cachedrender->Draw3DRectangle(sliderbutton, UI_COLOURS_CONTROL_HI, UI_COLOURS_CONTROL_LO, 1, true);
}

