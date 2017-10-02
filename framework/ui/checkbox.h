
#pragma once

#include "control.h"

class CheckBox : public Control
{

	private:
		bool depressed;

	protected:
		void OnRender() override;

	public:
		bool checked;

		CheckBox(Control* Parent);
		CheckBox(Control* Parent, Point<int> Position, Size<int> Dimensions);
		~CheckBox() override;

		void EventOccured(Event* What) override;
		void Update() override;


};
