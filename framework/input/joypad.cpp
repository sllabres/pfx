
#include "joypad.h"
#include "../core/maths.h"

#ifdef ALLEGRO

Joystick::Joystick(ALLEGRO_JOYSTICK* Source)
{
	joystickref = Source;

	directionstick = 0;
	directionlraxis = 0;
	directionudaxis = 1;
	facebuttoncount = 4;
	facebuttonmapping[JoystickButtonReference::SixButton_TopLeft] = 0;
	facebuttonmapping[JoystickButtonReference::SixButton_TopMiddle] = 1;
	facebuttonmapping[JoystickButtonReference::SixButton_TopRight] = 2;
	facebuttonmapping[JoystickButtonReference::SixButton_BottomLeft] = 3;
	facebuttonmapping[JoystickButtonReference::SixButton_BottomMiddle] = 4;
	facebuttonmapping[JoystickButtonReference::SixButton_BottomRight] = 5;
}

std::string Joystick::ControllerName()
{
	return std::string( al_get_joystick_name( joystickref ) );
}

int Joystick::GetStickCount()
{
	return al_get_joystick_num_sticks( joystickref );
}

int Joystick::GetAxisCount(int StickNumber)
{
	return al_get_joystick_num_axes( joystickref, StickNumber );
}

int Joystick::GetTotalButtonCount()
{
	return al_get_joystick_num_buttons( joystickref );
}

float Joystick::GetLeftDirection()
{
	ALLEGRO_JOYSTICK_STATE state;
	al_get_joystick_state( joystickref, &state );
	float lrvalue = state.stick[directionstick].axis[directionlraxis];
	if( lrvalue > 0.0f )
	{
		lrvalue = 0.0f;
	}
	return Maths::Abs( lrvalue );
}

float Joystick::GetRightDirection()
{
	ALLEGRO_JOYSTICK_STATE state;
	al_get_joystick_state( joystickref, &state );
	float lrvalue = state.stick[directionstick].axis[directionlraxis];
	if( lrvalue < 0.0f )
	{
		lrvalue = 0.0f;
	}
	return lrvalue;
}

float Joystick::GetUpDirection()
{
	ALLEGRO_JOYSTICK_STATE state;
	al_get_joystick_state( joystickref, &state );
	float udvalue = state.stick[directionstick].axis[directionudaxis];
	if( udvalue > 0.0f )
	{
		udvalue = 0.0f;
	}
	return Maths::Abs( udvalue );
}

float Joystick::GetDownDirection()
{
	ALLEGRO_JOYSTICK_STATE state;
	al_get_joystick_state( joystickref, &state );
	float udvalue = state.stick[directionstick].axis[directionudaxis];
	if( udvalue < 0.0f )
	{
		udvalue = 0.0f;
	}
	return udvalue;
}

bool Joystick::IsFaceButtonPressed(JoystickButtonReference::ReferenceCodes ButtonPosition)
{
	ALLEGRO_JOYSTICK_STATE state;
	al_get_joystick_state( joystickref, &state );
	return (facebuttonmapping[(int)ButtonPosition] > 0);
}

#endif // ALLEGRO

void Joystick::OnEvent(Event* What)
{
}

void Joystick::LoadMapping(std::string Filename)
{
}

void Joystick::SaveMapping(std::string Filename)
{
}

void Joystick::SetDirectionControls(int StickNumber, int LeftRightAxis, int UpDownAxis)
{
	directionstick = StickNumber;
	directionlraxis = LeftRightAxis;
	directionudaxis = UpDownAxis;
}

void Joystick::SetFourFaceButtonControls(int TopButtonNumber, int LeftButtonNumber, int RightButtonNumber, int BottomButtonNumber)
{
	facebuttoncount = 4;
	facebuttonmapping[JoystickButtonReference::FourButton_Top] = TopButtonNumber;
	facebuttonmapping[JoystickButtonReference::FourButton_Left] = LeftButtonNumber;
	facebuttonmapping[JoystickButtonReference::FourButton_Right] = RightButtonNumber;
	facebuttonmapping[JoystickButtonReference::FourButton_Bottom] = BottomButtonNumber;
}

void Joystick::SetSixFaceButtonControls(int TopRowLeftButtonNumber, int TopRowMiddleButtonNumber, int TopRowRightButtonNumber, int BottomRowLeftButtonNumber, int BottomRowMiddleButtonNumber, int BottomRowRightButtonNumber)
{
	facebuttoncount = 6;
	facebuttonmapping[JoystickButtonReference::SixButton_TopLeft] = TopRowLeftButtonNumber;
	facebuttonmapping[JoystickButtonReference::SixButton_TopMiddle] = TopRowMiddleButtonNumber;
	facebuttonmapping[JoystickButtonReference::SixButton_TopRight] = TopRowRightButtonNumber;
	facebuttonmapping[JoystickButtonReference::SixButton_BottomLeft] = BottomRowLeftButtonNumber;
	facebuttonmapping[JoystickButtonReference::SixButton_BottomMiddle] = BottomRowMiddleButtonNumber;
	facebuttonmapping[JoystickButtonReference::SixButton_BottomRight] = BottomRowRightButtonNumber;
}

int Joystick::GetFaceButtonCount()
{
	return facebuttoncount;
}
