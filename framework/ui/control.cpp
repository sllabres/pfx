
#include "control.h"
#include "form.h"
#include "../pfx.h"

Control::Control(Control* Parent)
{
	InitParameters();
	parent = Parent;
	if( parent != nullptr )
	{
		parent->controls.Add( this );
	}
}

Control::Control(Control* Parent, Point<int> Position, Size<int> Dimensions)
{
	InitParameters();
	parent = Parent;
	if( parent != nullptr )
	{
		parent->controls.Add( this );
	}
	position = Position;
	size = Dimensions;
	ResolveLocation();
}

Control::~Control()
{
	for( int i = 0; i < controls.Count(); i++ )
	{
		delete controls.At( i );
	}
	controls.Clear();
}

void Control::InitParameters()
{
	mouseinside = false;
	mousedepressed = false;
	acceptstab = false;
	backgroundcolour = UI_COLOURS_CONTROL;
	border = BorderStyle::None;
	canfocus = false;
	enabled = true;
	font = nullptr;
	foregroundcolour = UI_COLOURS_CONTROL_TEXT;
	name = "Control";
	parent = nullptr;
	size = Size<int>( 10, 10 );
	position = Point<int>( 0, 0 );
	cachedrender = nullptr;
}

void Control::Focus()
{
	Control* c = GetRootControl();
	if( c != nullptr && canfocus )
	{
		Form* f = dynamic_cast<Form*>(c);
		if( f != nullptr )
		{
			f->SetFocus( this );
		}
	}
}

bool Control::IsFocused()
{
	Control* c = GetRootControl();
	if( c != nullptr )
	{
		Form* f = dynamic_cast<Form*>(c);
		if( f != nullptr )
		{
			return (f->GetFocusedControl() == this);
		}
	}
	return false;
}

void Control::EventOccured(Event* What)
{
	for( int c = controls.Count() - 1; c >= 0; c-- )
	{
		controls.At( c )->EventOccured( What );
		if( What->handled )
		{
			return;
		}
	}

	Event* e = nullptr;
	Rect<int> r( resolvedlocation.x, resolvedlocation.y, size.w, size.h );

	switch( What->type )
	{

		case EventTypes::EVENT_INPUT_MOUSE_MOVE:			
			if( MouseInsideControl( What->data.input.mouse.x, What->data.input.mouse.y ) )
			{
				if( !mouseinside )
				{
					e = new Event();
					e->type = EventTypes::EVENT_UI_INTERACTION;
					e->data.ui.eventtype = FormEventType::MouseEnter;
					e->data.ui.source = this;
					memset( (void*)&e->data.ui.keyinfo, 0, sizeof( EventDataInputKeyboard ) );
					memcpy( (void*)&e->data.ui.mouseinfo, (void*)&What->data.input.mouse, sizeof( EventDataInputMouse ) );
					e->data.ui.mouseinfo.x -= resolvedlocation.x;
					e->data.ui.mouseinfo.y -= resolvedlocation.y;
					e->data.ui.additionaldata = nullptr;
					FX->events.PushEvent( e );
					mouseinside = true;
				}
				e = new Event();
				e->type = EventTypes::EVENT_UI_INTERACTION;
				e->data.ui.eventtype = FormEventType::MouseMove;
				e->data.ui.source = this;
				memset( (void*)&e->data.ui.keyinfo, 0, sizeof( EventDataInputKeyboard ) );
				memcpy( (void*)&e->data.ui.mouseinfo, (void*)&What->data.input.mouse, sizeof( EventDataInputMouse ) );
				e->data.ui.mouseinfo.x -= resolvedlocation.x;
				e->data.ui.mouseinfo.y -= resolvedlocation.y;
				e->data.ui.additionaldata = nullptr;
				FX->events.PushEvent( e );
				What->handled = true;
			} else {
				if( mouseinside )
				{
					e = new Event();
					e->type = EventTypes::EVENT_UI_INTERACTION;
					e->data.ui.eventtype = FormEventType::MouseLeave;
					e->data.ui.source = this;
					memset( (void*)&e->data.ui.keyinfo, 0, sizeof( EventDataInputKeyboard ) );
					memcpy( (void*)&e->data.ui.mouseinfo, (void*)&What->data.input.mouse, sizeof( EventDataInputMouse ) );
					e->data.ui.mouseinfo.x -= resolvedlocation.x;
					e->data.ui.mouseinfo.y -= resolvedlocation.y;
					e->data.ui.additionaldata = nullptr;
					FX->events.PushEvent( e );
					mouseinside = false;
				}
			}
			break;

		case EventTypes::EVENT_INPUT_MOUSE_BUTTONDOWN:
			if( mouseinside )
			{
				e = new Event();
				e->type = EventTypes::EVENT_UI_INTERACTION;
				e->data.ui.eventtype = FormEventType::MouseDown;
				e->data.ui.source = this;
				memset( (void*)&e->data.ui.keyinfo, 0, sizeof( EventDataInputKeyboard ) );
				memcpy( (void*)&e->data.ui.mouseinfo, (void*)&What->data.input.mouse, sizeof( EventDataInputMouse ) );
				e->data.ui.mouseinfo.x -= resolvedlocation.x;
				e->data.ui.mouseinfo.y -= resolvedlocation.y;
				e->data.ui.additionaldata = nullptr;
				FX->events.PushEvent( e );
				mousedepressed = true;
				What->handled = true;
				this->Focus();
			}
			break;

		case EventTypes::EVENT_INPUT_MOUSE_BUTTONUP:
			if( mouseinside )
			{
				e = new Event();
				e->type = EventTypes::EVENT_UI_INTERACTION;
				e->data.ui.eventtype = FormEventType::MouseUp;
				e->data.ui.source = this;
				memset( (void*)&e->data.ui.keyinfo, 0, sizeof( EventDataInputKeyboard ) );
				memcpy( (void*)&e->data.ui.mouseinfo, (void*)&What->data.input.mouse, sizeof( EventDataInputMouse ) );
				e->data.ui.mouseinfo.x -= resolvedlocation.x;
				e->data.ui.mouseinfo.y -= resolvedlocation.y;
				e->data.ui.additionaldata = nullptr;
				FX->events.PushEvent( e );
				if( mouseinside )
				{
					e = new Event();
					e->type = EventTypes::EVENT_UI_INTERACTION;
					e->data.ui.eventtype = FormEventType::MouseClick;
					e->data.ui.source = this;
					memset( (void*)&e->data.ui.keyinfo, 0, sizeof( EventDataInputKeyboard ) );
					memcpy( (void*)&e->data.ui.mouseinfo, (void*)&What->data.input.mouse, sizeof( EventDataInputMouse ) );
					e->data.ui.mouseinfo.x -= resolvedlocation.x;
					e->data.ui.mouseinfo.y -= resolvedlocation.y;
					e->data.ui.additionaldata = nullptr;
					FX->events.PushEvent( e );
				}
				What->handled = true;
			}
			mousedepressed = false;
			break;

		case EventTypes::EVENT_INPUT_KEYBOARD_KEYDOWN:
		case EventTypes::EVENT_INPUT_KEYBOARD_KEYUP:
			if( IsFocused() )
			{
				e = new Event();
				e->type = EventTypes::EVENT_UI_INTERACTION;
				e->data.ui.eventtype = (What->type == EventTypes::EVENT_INPUT_KEYBOARD_KEYUP ? FormEventType::KeyUp : FormEventType::KeyDown);
				e->data.ui.source = this;
				memcpy( (void*)&e->data.ui.keyinfo, (void*)&What->data.input.keyboard, sizeof( EventDataInputKeyboard ) );
				memset( (void*)&e->data.ui.mouseinfo, 0, sizeof( EventDataInputMouse ) );
				e->data.ui.additionaldata = nullptr;
				FX->events.PushEvent( e );
				What->handled = true;
			}
			break;

		case EventTypes::EVENT_INPUT_KEYBOARD_KEYPRESS:
			if( IsFocused() )
			{
				if( What->data.input.keyboard.keycode == KEYCODE_TAB && !acceptstab )
				{
					Form* f = GetForm();
					if( f != nullptr )
					{
						if( (What->data.input.keyboard.modifiers & KEYMOD_SHIFT) == KEYMOD_SHIFT )
						{
							f->FocusPrevious();
							What->handled = true;
							return;
						} else {
							f->FocusNext();
							What->handled = true;
							return;
						}
					}
				}

				e = new Event();
				e->type = EventTypes::EVENT_UI_INTERACTION;
				e->data.ui.eventtype = FormEventType::KeyPress;
				e->data.ui.source = this;
				memcpy( (void*)&e->data.ui.keyinfo, (void*)&What->data.input.keyboard, sizeof( EventDataInputKeyboard ) );
				memset( (void*)&e->data.ui.mouseinfo, 0, sizeof( EventDataInputMouse ) );
				e->data.ui.additionaldata = nullptr;
				FX->events.PushEvent( e );
				What->handled = true;
			}
			break;

	}

}

void Control::Render()
{
	if( size.w < 0 || size.h < 0 )
	{
		return;
	}

	if( cachedrender == nullptr )
	{
		cachedrender = new Bitmap( size.w, size.h );
	} else if( cachedrender->GetDimensions() != size ) {
		delete cachedrender;
		cachedrender = new Bitmap( size.w, size.h );
	}

	Bitmap* prevtarget = FX->video.GetCurrentRenderTargetBitmap();
	cachedrender->SetAsRenderTarget();

	PreRender();
	OnRender();
	PostRender();

	prevtarget->SetAsRenderTarget();
	cachedrender->Render( position, false, false );
}

void Control::Update()
{
	for( int c = 0; c < controls.Count(); c++ )
	{
		controls.At( c )->Update();
	}
}

Control* Control::FindControl(std::string Name)
{
	for( int c = 0; c < controls.Count(); c++ )
	{
		if( controls.At( c )->name == Name )
		{
			return controls.At( c );
		}
	}
	return nullptr;
}

bool Control::MouseInsideControl(int x, int y)
{
	bool result = false;
	Rect<int> r( resolvedlocation.x, resolvedlocation.y, size.w, size.h );
	if( r.IsPointInside( Point<int>(x, y) ) )
	{
		Control* p = GetParent();
		if( p == nullptr )
		{
			result = true;
		} else {
			result = p->MouseInsideControl( x, y );
		}
	} else {
		result = false;
	}
	return result;
}

Control* Control::GetParent()
{
	return parent;
}

Control* Control::GetRootControl()
{
	if( parent != nullptr )
	{
		return parent->GetRootControl();
	}
	return this;
}

Form* Control::GetForm()
{
	Control* c = GetRootControl();
	Form* f = dynamic_cast<Form*>(c);
	return f;
}

void Control::PreRender()
{
	Size<int> s = cachedrender->GetDimensions();
	cachedrender->FillRectangle( Rect<int>( 0, 0, s.w, s.h ), backgroundcolour );
}

void Control::PostRender()
{
	switch( border )
	{
		case BorderStyle::Flat:
			cachedrender->DrawLine( Line<int>( 0, 0, size.w - 1, 0 ), UI_COLOURS_CONTROL_LO, 1 );
			cachedrender->DrawLine( Line<int>( 0, 0, 0, size.h - 1 ), UI_COLOURS_CONTROL_LO, 1 );
			cachedrender->DrawLine( Line<int>( size.w - 1, 1, size.w - 1, size.h - 1 ), UI_COLOURS_CONTROL_LO, 1 );
			cachedrender->DrawLine( Line<int>( 0, size.h - 1, size.w - 1, size.h - 1 ), UI_COLOURS_CONTROL_LO, 1 );
			break;
		case BorderStyle::Raised:
			cachedrender->DrawLine( Line<int>( 0, 0, size.w - 1, 0 ), UI_COLOURS_CONTROL_HI, 1 );
			cachedrender->DrawLine( Line<int>( 0, 0, 0, size.h - 1 ), UI_COLOURS_CONTROL_HI, 1 );
			cachedrender->DrawLine( Line<int>( size.w - 1, 1, size.w - 1, size.h - 1 ), UI_COLOURS_CONTROL_LO, 1 );
			cachedrender->DrawLine( Line<int>( 0, size.h - 1, size.w - 1, size.h - 1 ), UI_COLOURS_CONTROL_LO, 1 );
			break;
		case BorderStyle::Depressed:
			cachedrender->DrawLine( Line<int>( 0, 0, size.w - 1, 0 ), UI_COLOURS_CONTROL_LO, 1 );
			cachedrender->DrawLine( Line<int>( 0, 0, 0, size.h - 1 ), UI_COLOURS_CONTROL_LO, 1 );
			cachedrender->DrawLine( Line<int>( size.w - 1, 1, size.w - 1, size.h - 1 ), UI_COLOURS_CONTROL_HI, 1 );
			cachedrender->DrawLine( Line<int>( 0, size.h - 1, size.w - 1, size.h - 1 ), UI_COLOURS_CONTROL_HI, 1 );
			break;
	}


	for( int c = 0; c < controls.Count(); c++ )
	{
		controls.At( c )->Render();
	}
}

void Control::OnRender()
{
}

void Control::ResolveLocation()
{
	if( parent == nullptr )
	{
		resolvedlocation.x = position.x;
		resolvedlocation.y = position.y;
	} else {
		resolvedlocation.x = position.x + parent->resolvedlocation.x;
		resolvedlocation.y = position.y + parent->resolvedlocation.y;
	}
	for( int c = 0; c < controls.Count(); c++ )
	{
		controls.At( c )->ResolveLocation();
	}
}

Font* Control::ResolveFont()
{
	Control* c = this;
	while( c != nullptr )
	{
		if( c->font != nullptr )
		{
			return c->font;
		}
		c = c->parent;
	}
	return nullptr;
}
