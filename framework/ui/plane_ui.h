
#pragma once

#include "../video/plane.h"
#include "form.h"

#include "button.h"
#include "checkbox.h"
#include "hscrollbar.h"
#include "label.h"
#include "textedit.h"
#include "vscrollbar.h"

class UIPlane : public Plane
{
	public:
		List<Form*> forms;

		UIPlane(Display* Owner);

		void EventOccured(Event* What) override;
		void Update() override;
		void Render() override;
};
