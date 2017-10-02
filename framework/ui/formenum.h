
#pragma once

#define UI_COLOURS_CONTROL_LO	Colour( 64, 64, 64 )
#define UI_COLOURS_CONTROL_HI	Colour( 220, 220, 220 )
#define UI_COLOURS_CONTROL	Colour( 192, 192, 192 )
#define UI_COLOURS_CONTROL_TEXT	Colour( 0, 0, 0 )
#define UI_COLOURS_EDIT	Colour( 220, 220, 220 )
#define UI_COLOURS_EDIT_TEXT	Colour( 0, 0, 0 )

enum class FormEventType
{
	GotFocus,
	LostFocus,
	MouseEnter,
	MouseLeave,
	MouseDown,
	MouseUp,
	MouseMove,
	MouseClick,
	KeyDown,
	KeyPress,
	KeyUp,

	ButtonClick,
	CheckBoxChange,
	ScrollBarChange,
	TextChanged,
	TextEditFinish
};

enum class HorizontalAlignment
{
	Left,
	Centre,
	Right
};

enum class VerticalAlignment
{
	Top,
	Centre,
	Bottom
};

enum class BorderStyle
{
	None,
	Flat,
	Depressed,
	Raised
};
