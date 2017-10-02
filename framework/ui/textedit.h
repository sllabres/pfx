
#pragma once

#include "control.h"

class TextEdit : public Control
{

	private:
		std::string previoustext;

	protected:
		int caretdrawtimer;
		bool editing;

		void OnRender() override;

	public:
		bool drawcaret;
		int selectionstart;
		int selectionlength;

		std::string text;
		HorizontalAlignment horizontalalignment;
		VerticalAlignment verticalalignment;

		TextEdit(Control* Parent, std::string Text);
		TextEdit(Control* Parent, Point<int> Position, Size<int> Dimensions, std::string Text);
		~TextEdit() override;

		void EventOccured(Event* What) override;
		void Update() override;

};
