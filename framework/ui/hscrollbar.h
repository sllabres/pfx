
#pragma once

#include "control.h"
#include "button.h"

class HScrollbar : public Control
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

		HScrollbar(Control* Parent);
		HScrollbar(Control* Parent, Point<int> Position, Size<int> Dimensions);
		~HScrollbar() override;

		void EventOccured(Event* What) override;
		void Update() override;


};
