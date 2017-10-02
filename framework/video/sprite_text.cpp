
#include "sprite_text.h"

TextSprite::TextSprite(std::string Text, Font* TextFont, Colour TextColour)
{
	text = Text;
	font = TextFont;
	colour = TextColour;
	borderwidth = 0;
	bordercolour = TextColour;
}

TextSprite::TextSprite(std::string Text, Font* TextFont, Colour TextColour, int BorderWidth, Colour BorderColour)
{
	text = Text;
	font = TextFont;
	colour = TextColour;
	borderwidth = BorderWidth;
	bordercolour = BorderColour;
}

void TextSprite::Update()
{
	if( prevtext != text )
	{
		if( this->image != nullptr )
		{
			delete this->image;
		}
		this->image = font->RenderText( text, colour, borderwidth, bordercolour );
		prevtext = text;
	}
}

void TextSprite::Render()
{
	this->image->Render( this->position, scale );
}
