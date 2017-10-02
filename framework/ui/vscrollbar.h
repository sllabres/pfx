
#pragma once

#include "control.h"
#include "button.h"

class VScrollbar : public Control
{

	private:
		Rect<int> leftbutton;
		Rect<int> rightbutton;
		Rect<int> sliderbutton;
		int buttoninside;
		int buttondragx;

		void ConfigureUI();

	protected:
		void OnRender() override;

	public:
		int minimum;
		int maximum;
		int value;

		VScrollbar(Control* Parent);
		VScrollbar(Control* Parent, Point<int> Position, Size<int> Dimensions);
		~VScrollbar() override;

		void EventOccured(Event* What) override;
		void Update() override;


};
