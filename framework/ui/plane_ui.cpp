
#include "plane_ui.h"

UIPlane::UIPlane(Display* Owner) : Plane( Owner )
{
	Owner->SetMouseCursorVisible( true );
}

void UIPlane::EventOccured(Event* What)
{
	for( int f = 0; f < forms.Count(); f++ )
	{
		forms.At( f )->EventOccured( What );
	}
}

void UIPlane::Update()
{
	for( int f = 0; f < forms.Count(); f++ )
	{
		forms.At( f )->Update();
	}
}

void UIPlane::Render()
{
	for( int f = 0; f < forms.Count(); f++ )
	{
		forms.At( f )->Render();
	}
}

