
#pragma once

#include "../events/event.h"
#include "../libraryincludes.h"

class JoystickButtonReference
{
	public:
		enum ReferenceCodes
		{
			FourButton_Top = 1,
			FourButton_Left = 0,
			FourButton_Right = 4,
			FourButton_Bottom = 3,
			SixButton_TopLeft = 0,
			SixButton_TopMiddle = 1,
			SixButton_TopRight = 2,
			SixButton_BottomLeft = 3,
			SixButton_BottomMiddle = 4,
			SixButton_BottomRight = 5

		};
};

class Joystick
{

	private:
		int directionstick;
		int directionlraxis;
		int directionudaxis;
		int facebuttoncount;
		int facebuttonmapping[6];

	public:
#ifdef ALLEGRO
		ALLEGRO_JOYSTICK* joystickref;

		Joystick(ALLEGRO_JOYSTICK* Source);
#endif // ALLEGRO

		void OnEvent(Event* What);

		std::string ControllerName();

		int GetStickCount();
		int GetAxisCount(int StickNumber);
		int GetTotalButtonCount();

		void LoadMapping(std::string Filename);
		void SaveMapping(std::string Filename);
		void SetDirectionControls(int StickNumber, int LeftRightAxis, int UpDownAxis);
		void SetFourFaceButtonControls(int TopButtonNumber, int LeftButtonNumber, int RightButtonNumber, int BottomButtonNumber);
		void SetSixFaceButtonControls(int TopRowLeftButtonNumber, int TopRowMiddleButtonNumber, int TopRowRightButtonNumber, int BottomRowLeftButtonNumber, int BottomRowMiddleButtonNumber, int BottomRowRightButtonNumber);

		float GetLeftDirection();
		float GetRightDirection();
		float GetUpDirection();
		float GetDownDirection();

		int GetFaceButtonCount();
		bool IsFaceButtonPressed(JoystickButtonReference::ReferenceCodes ButtonPosition);


};
