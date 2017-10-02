
#pragma once

template <typename T>
class Size
{
	public:
		T w;
		T h;

		static Size<T> Empth() { return Size<T>(); };

		Size() { w = 0; h = 0; };
		Size(T W, T H) { w = W; h = H; };

		bool operator==(Size<T> Cmp) { return (w == Cmp.w) && (h == Cmp.h); };
		bool operator!=(Size<T> Cmp) { return (w != Cmp.w) || (h != Cmp.h); };
		Size<T> operator=(Size<T> Val) { w = Val.w; h = Val.h; return *this; };
		Size<T> operator+=(Size<T> Val) { w = w + Val.w; h = h + Val.h; return *this; };
		Size<T> operator-=(Size<T> Val) { w = w - Val.w; h = h - Val.h; return *this; };
		Size<T> operator*=(Size<T> Val) { w = w * Val.w; h = h * Val.h; return *this; };
		Size<T> operator*=(T Val) { w = w * Val; h = h * Val; return *this; };
		Size<T> operator/=(Size<T> Val) { w = w / Val.w; h = h / Val.h; return *this; };
		Size<T> operator/=(T Val) { w = w / Val; h = h / Val; return *this; };
		Size<T> operator-(Size<T> Val) { return Size<T>( w - Val.w, h - Val.h ); };

		float DotProduct(Size<T> With) { return (w * With.w) + (h * With.h); };

		void Normalise() { float m = sqrt( (w*w) + (h*h) ); w /= m; h /= m; };
};
