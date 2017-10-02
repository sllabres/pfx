
#pragma once

#include "sprite.h"
#include "font.h"

class TextSprite : public Sprite
{
	private:
		std::string prevtext;

	public:
		Font* font;
		std::string text;
		Colour colour;
		int borderwidth;
		Colour bordercolour;

		TextSprite(std::string Text, Font* TextFont, Colour TextColour);
		TextSprite(std::string Text, Font* TextFont, Colour TextColour, int BorderWidth, Colour BorderColour);

		void Update() override;
		void Render() override;
};
