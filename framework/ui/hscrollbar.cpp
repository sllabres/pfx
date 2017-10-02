
#include "hscrollbar.h"
#include "../pfx.h"

HScrollbar::HScrollbar(Control* Parent) : Control( Parent )
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

HScrollbar::HScrollbar(Control* Parent, Point<int> Position, Size<int> Dimensions) : Control( Parent, Position, Dimensions )
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

HScrollbar::~HScrollbar()
{
}

void HScrollbar::ConfigureUI()
{
}

void HScrollbar::EventOccured(Event* What)
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
					case KEYCODE_LEFT:
						if( value > minimum )
						{
							value--;
							valuewaschanged = true;
						}
						break;
					case KEYCODE_RIGHT:
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
					if( What->data.ui.mouseinfo.x <= leftbutton.Right() )
					{
						value = minimum;
						valuewaschanged = true;
					} else if( What->data.ui.mouseinfo.x >= rightbutton.Left() ) {
						value = maximum;
						valuewaschanged = true;
					} else {
						int offsx = What->data.ui.mouseinfo.x - leftbutton.Right();
						int segments = (maximum - minimum) + 1;
						int workingspace = size.w - leftbutton.w - rightbutton.w;
						float segmentsize = (float)workingspace / (float)segments;
						value = (int)Maths::Min((float)maximum, Maths::Max( (float)minimum, minimum + ((float)offsx / segmentsize) ));
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
						if( What->data.ui.mouseinfo.x < sliderbutton.Left() )
						{
							if( value > minimum )
							{
								value--;
								valuewaschanged = true;
							}
						}
						if( What->data.ui.mouseinfo.x > sliderbutton.Right() )
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

void HScrollbar::Update()
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

	if( size.h < 8 )
	{
		size.h = 8;
	}
	if( size.w < size.h * 3 )
	{
		size.w = size.h / 3;
	}
	sliderbutton.h = size.h;
	sliderbutton.w = (size.w - (size.h * 2)) / (maximum - minimum);
	if( sliderbutton.w < size.h )
	{
		sliderbutton.w = size.h;
	}
	leftbutton.w = size.h;
	leftbutton.h = size.h;
	rightbutton.x = size.w - size.h;
	rightbutton.w = size.h;
	rightbutton.h = size.h;

	int workingspace = (size.w - (size.h * 2)) - sliderbutton.w;
	float sx = ((float)workingspace / (float)(maximum - minimum)) * value;
	sliderbutton.x = size.h + sx;

}

void HScrollbar::OnRender()
{
	cachedrender->Draw3DRectangle(leftbutton, UI_COLOURS_CONTROL_HI, UI_COLOURS_CONTROL_LO, 1, (buttoninside == 1 ? false : true));
	cachedrender->Draw3DRectangle(rightbutton, UI_COLOURS_CONTROL_HI, UI_COLOURS_CONTROL_LO, 1, (buttoninside == 2 ? false : true));
	cachedrender->Draw3DRectangle(sliderbutton, UI_COLOURS_CONTROL_HI, UI_COLOURS_CONTROL_LO, 1, true);
}

