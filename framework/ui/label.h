
#pragma once

#include "control.h"

class Label : public Control
{

	protected:
		void OnRender() override;

	public:
		std::string text;
		HorizontalAlignment horizontalalignment;
		VerticalAlignment verticalalignment;

		Label(Control* Parent, std::string Text);
		Label(Control* Parent, Point<int> Position, Size<int> Dimensions, std::string Text);
		~Label() override;

		void EventOccured(Event* What) override;
		void Update() override;


};
