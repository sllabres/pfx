
#pragma once

#include "formenum.h"
#include "../core/colour.h"
#include "../core/list.h"
#include "../events/event.h"
#include "../primitives/point.h"
#include "../primitives/size.h"
#include "../video/bitmap.h"
#include "../video/font.h"

#ifndef Form
class Form;
#endif

class Control
{

	private:
		void PreRender();
		void PostRender();

	protected:
		Bitmap* cachedrender;
		Control* parent;
		bool mouseinside;
		bool mousedepressed;
		Point<int> resolvedlocation;

		void InitParameters();
		virtual void OnRender();
		void ResolveLocation();

		Font* ResolveFont();

	public:
		bool acceptstab;
		Colour backgroundcolour;
		BorderStyle border;
		bool canfocus;
		List<Control*> controls;
		bool enabled;
		Font* font;
		Colour foregroundcolour;
		std::string name;
		Point<int> position;
		Size<int> size;
		bool visible;
		
		Control(Control* Parent);
		Control(Control* Parent, Point<int> Position, Size<int> Dimensions);
		virtual ~Control();

		void Focus();
		bool IsFocused();

		virtual void EventOccured(Event* What);
		void Render();
		virtual void Update();

		Control* FindControl(std::string Name);
		bool MouseInsideControl(int x, int y);

		Control* GetParent();
		Control* GetRootControl();
		Form* GetForm();
};
