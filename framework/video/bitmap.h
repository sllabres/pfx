
#pragma once

#include "../libraryincludes.h"
#include "../primitives/rect.h"
#include "../primitives/size.h"
#include "../primitives/angle.h"
#include "../primitives/ellipses.h"
#include "../core/colour.h"
#include <string>

class Bitmap
{

	private:
		Size<int> lockedarea;

	protected:
		bool pixelaccess;
		bool fromexistingsource;

#ifdef ALLEGRO
		typedef struct PackedARGB
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		} PackedARGB;

		ALLEGRO_BITMAP* image;
		ALLEGRO_LOCKED_REGION* pixeldata;
#endif // ALLEGRO

	public:
		Bitmap(int Width, int Height);
		Bitmap(std::string Filename);
#ifdef ALLEGRO
		Bitmap(ALLEGRO_BITMAP* Source);
#endif // ALLEGRO

		~Bitmap();

		void Render(Point<int> At, bool FlipHorizontal, bool FlipVertical);
		void RenderRotated(Point<int> At, Point<int> RotationOrigin, Angle Rotation, bool FlipHorizontal, bool FlipVertical);
		void RenderPortion(Point<int> At, Rect<int> Region, bool FlipHorizontal, bool FlipVertical);
		void RenderPortion(Point<int> At, Rect<int> Region, bool FlipHorizontal, bool FlipVertical, unsigned char Alpha);
		void RenderPortionRotated(Point<int> At, Rect<int> Region, Point<int> RotationOrigin, Angle Rotation, bool FlipHorizontal, bool FlipVertical);

		void Render(Point<int> At, Size<float> Scale);
		void Render(Point<int> At, Size<float> Scale, unsigned char Alpha);
		void RenderRotated(Point<int> At, Point<int> RotationOrigin, Angle Rotation, Size<float> Scale);
		void RenderRotated(Point<int> At, Point<int> RotationOrigin, Angle Rotation, Size<float> Scale, unsigned char Alpha);
		void RenderPortion(Point<int> At, Rect<int> Region, Size<float> Scale);
		void RenderPortion(Point<int> At, Rect<int> Region, Size<float> Scale, unsigned char Alpha);
		void RenderPortionRotated(Point<int> At, Rect<int> Region, Point<int> RotationOrigin, Angle Rotation, Size<float> Scale);
		void RenderPortionRotated(Point<int> At, Rect<int> Region, Point<int> RotationOrigin, Angle Rotation, Size<float> Scale, unsigned char Alpha);

		Size<int> GetDimensions();

		void EnablePixelAccess(bool ReadAccess, bool WriteAccess);
		void EnablePixelAccess(bool ReadAccess, bool WriteAccess, Rect<int> Region);
		void DisablePixelAccess();
		void SetPixel(Point<int> At, Colour NewColour);
		void SetPixel(int AtX, int AtY, Colour NewColour);
		Colour GetPixel(Point<int> At);
		Colour GetPixel(int AtX, int AtY);
		void ReplaceColour(Colour OldColour, Colour NewColour);

		void DrawRectangle(Rect<int> What, Colour DrawColour, int LineWidth);
		void Draw3DRectangle(Rect<int> What, Colour HighlightColour, Colour LowlightColour, int LineWidth, bool Raised);
		void FillRectangle(Rect<int> What, Colour FillColour);
		void DrawLine(Line<int> What, Colour DrawColour, int LineWidth);
		void DrawEllipses(Ellipses<int> What, Colour DrawColour, int LineWidth);
		void FillEllipses(Ellipses<int> What, Colour FillColour);

		void SetAsRenderTarget();

		void Save(std::string Filename);

};
