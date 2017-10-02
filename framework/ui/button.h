
#pragma once

#include "control.h"

class Button : public Control
{

	private:
		bool depressed;

	protected:
		void OnRender() override;

	public:
		BorderStyle border_standard;
		BorderStyle border_depressed;

		Bitmap* image;
		std::string text;
		HorizontalAlignment horizontalalignment;
		VerticalAlignment verticalalignment;

		Button(Control* Parent, std::string Text);
		Button(Control* Parent, Point<int> Position, Size<int> Dimensions, std::string Text);
		~Button() override;

		void EventOccured(Event* What) override;
		void Update() override;


};
