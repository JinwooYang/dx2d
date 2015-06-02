#pragma once
#include "dx2dxMacros.h"
#include <time.h>

NS_DX2DX
{
	struct Point
	: public D3DXVECTOR2
	{
		Point();

		Point(const Point &pos);

		Point operator + (const Point &point) const;
		Point operator += (const Point &point);


		Point(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		D3DXVECTOR3 GetVector3() const;

		static const Point ZERO;
		static const Point ANCHOR_MIDDLE;
		static const Point ANCHOR_BOTTOM_LEFT;
		static const Point ANCHOR_TOP_LEFT;
		static const Point ANCHOR_BOTTOM_RIGHT;
		static const Point ANCHOR_TOP_RIGHT;
		static const Point ANCHOR_MIDDLE_RIGHT;
		static const Point ANCHOR_MIDDLE_LEFT;
		static const Point ANCHOR_MIDDLE_TOP;
		static const Point ANCHOR_MIDDLE_BOTTOM;
	};

	typedef Point Vec2;

	struct Size
	{
		Size();

		Size(const Size &size);

		Size(float x, float y);

		float width, height;

		bool operator == (const Size &size) const;

		static const Size ZERO;
	};

	struct Rect
	{
		float left, top, width, height;

		Rect();

		Rect(float left, float top, float width, float height);

		Rect(const Rect &rect);

		void Offset(const Point &pos);

		void Offset(float x, float y);

		Rect GetOffsetBox(const Point &pos) const;

		Rect GetOffsetBox(float x, float y) const;

		bool ContainsPoint(const Point &pos) const;

		bool IntersectRect(const Rect &rect) const;

		Rect GetOverlapBox(const Rect &rect) const;

		float GetMinX() const;

		float GetMinY() const;

		float GetMidX() const;

		float GetMidY() const;

		float GetMaxX() const;

		float GetMaxY() const;
	};

	struct AnimData
	{
		AnimData(int wFrame, int hFrame, float cutWidth, float cutHeight, clock_t animateTime, int frameCnt);

		int wFrame, hFrame;
		float cutWidth, cutHeight;
		clock_t animateTime;
		int frameCnt;
	};

	struct Color4F
	{
		float r, g, b, a;

		Color4F()
		{
			r = g = b = a = 254.0f;
		}
		Color4F(float r, float g, float b, float a)
		{
			if (a > 254.0f)
				a = 254.0f;
			if (r > 254.0f)
				r = 254.0f;
			if (g > 254.0f)
				g = 254.0f;
			if (b > 254.0f)
				b = 254.0f;

			this->a = a;
			this->r = r;
			this->g = g;
			this->b = b;
		}

		bool operator ==(Color4F& color)
		{
			return (a == color.a && r == color.r && g == color.g && b == color.b);
		}

		Color4F operator +=(Color4F& color)
		{
			a += color.a;
			r += color.r;
			g += color.g;
			b += color.b;

			if (a > 254.0f)
				a = 254.0f;
			if (r > 254.0f)
				r = 254.0f;
			if (g > 254.0f)
				g = 254.0f;
			if (b > 254.0f)
				b = 254.0f;

			return *this;
		}

		static const Color4F WHITE;
		static const Color4F BLACK;
		static const Color4F RED;
		static const Color4F GREEN;
		static const Color4F BLUE;
		static const Color4F INVISIBLE;
	};
}