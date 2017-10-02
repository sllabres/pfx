
#pragma once

#include "control.h"
#include "../core/list.h"
#include "vscrollbar.h"

class ListBox : public Control
{

	private:
		List<Control*> listitems;
		VScrollbar* scroller;

	protected:
		void OnRender() override;

	public:
		ListBox(Control* Parent);
		ListBox(Control* Parent, Point<int> Position, Size<int> Dimensions);
		~ListBox() override;

		void EventOccured(Event* What) override;
		void Update() override;


};
