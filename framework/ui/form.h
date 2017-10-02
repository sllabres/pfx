
#pragma once

#include "control.h"

class Form : public Control
{

	private:
		Control* activecontrol;
		List<Control*> focusablecontrols;

		void GenerateFocusList(Control* Parent);

	protected:
		void OnRender() override;

	public:
		Form();
		~Form() override;

		void SetFocus(Control* Item);
		void FocusNext();
		void FocusPrevious();
		Control* GetFocusedControl();

		void EventOccured(Event* What) override;
		void Update() override;

};
