#include "DXUT.h"
#include "dx2dxStruct.h"

USING_NS_DX2DX;


//--------------------------------Point start--------------------------------
Point::Point()
{
	x = y = 0.0f;
}

Point::Point(const Point &pos)
{
	x = pos.x;
	y = pos.y;
}

Point Point::operator + (const Point &point) const
{
	return Point(x + point.x, y + point.y);
}

Point Point::operator += (const Point &point)
{
	x += point.x;
	y += point.y;
	return *this;
}

D3DXVECTOR3 Point::GetVector3() const
{
	return D3DXVECTOR3(x, y, 0.0f);
}

const Point Point::ZERO = Point(0.0f, 0.0f);
const Point Point::ANCHOR_MIDDLE = Point(0.5f, 0.5f);
const Point Point::ANCHOR_BOTTOM_LEFT = Point(0.0f, 1.0f);
const Point Point::ANCHOR_TOP_LEFT = Point(0.0f, 0.0f);
const Point Point::ANCHOR_BOTTOM_RIGHT = Point(1.0f, 1.0f);
const Point Point::ANCHOR_TOP_RIGHT = Point(1.0f, 0.0f);
const Point Point::ANCHOR_MIDDLE_RIGHT = Point(1.0f, 0.5f);
const Point Point::ANCHOR_MIDDLE_LEFT = Point(0.0f, 0.5f);
const Point Point::ANCHOR_MIDDLE_TOP = Point(0.5f, 0.0f);
const Point Point::ANCHOR_MIDDLE_BOTTOM = Point(0.5f, 1.0f);
//--------------------------------Point end----------------------------------










//--------------------------------Size start---------------------------------
Size::Size()
{
	width = height = 0.0f;
}

Size::Size(const Size &size)
{
	width = size.width;
	height = size.height;
}

Size::Size(float x, float y)
{
	this->width = x;
	this->height = y;
}

bool Size::operator== (const Size &size) const
{
	return (width == size.width && height == size.height);
}

const Size Size::ZERO = Size(0, 0);
//--------------------------------Size end-----------------------------------


//--------------------------------Rect start---------------------------------
Rect::Rect()
{
	left = top = width = height = 0.0f;
}

Rect::Rect(float left, float top, float width, float height)
{
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
}

Rect::Rect(const Rect &rect)
{
	left = rect.left;
	top = rect.top;
	width = rect.width;
	height = rect.height;
}

void Rect::Offset(const Point &pos)
{
	left = pos.x;
	top = pos.y;
}

void Rect::Offset(float x, float y)
{
	left = x;
	top = y;
}

Rect Rect::GetOffsetBox(const Point &pos) const
{
	Rect rect(left, top, width, height);
	rect.Offset(pos);
	return rect;
}

Rect Rect::GetOffsetBox(float x, float y) const
{
	Rect rect(left, top, width, height);
	rect.Offset(x, y);
	return rect;
}

bool Rect::ContainsPoint(const Point &pos) const
{
	if (left <= pos.x && pos.x <= left + width &&
		top <= pos.y && pos.y <= top + height)
		return true;

	return false;
}

bool Rect::IntersectRect(const Rect &rect) const
{
	if (left <= rect.left + rect.width && left + width >= rect.left &&
		top <= rect.top + rect.height && top + height >= rect.top)
		return true;

	return false;
}

Rect Rect::GetOverlapBox(const Rect &rect) const
{
	auto overlapBox = Rect(0, 0, 0, 0);
	if (this->IntersectRect(rect))
	{
		if (left >= rect.left) overlapBox.left = left;
		else overlapBox.left = rect.left;

		if (top >= rect.top) overlapBox.top = top;
		else overlapBox.top = rect.top;

		if (left + width <= rect.left + rect.width) overlapBox.width = left + width - rect.left;
		else overlapBox.width = rect.left + rect.width - left;

		if (top + height <= rect.top + rect.height) overlapBox.height = top + height - rect.top;
		else overlapBox.height = rect.top + rect.height - top;
	}

	return overlapBox;
}

float Rect::GetMinX() const
{
	return left;
}

float Rect::GetMinY() const
{
	return top;
}

float Rect::GetMidX() const
{
	return left + (width / 2);
}

float Rect::GetMidY() const
{
	return top + (height / 2);
}

float Rect::GetMaxX() const
{
	return left + width;
}

float Rect::GetMaxY() const
{
	return top + height;
}
//--------------------------------Rect end-----------------------------------


//--------------------------------AnimData start-----------------------------
AnimData::AnimData(int wFrame, int hFrame, float cutWidth, float cutHeight, clock_t animateTime, int frameCnt)
{
	this->wFrame = wFrame;
	this->hFrame = hFrame;
	this->cutWidth = cutWidth;
	this->cutHeight = cutHeight;
	this->animateTime = animateTime;
	this->frameCnt = frameCnt;
}
//--------------------------------AnimData end-------------------------------


//Color4F
const Color4F Color4F::WHITE = Color4F(255.0f, 255.0f, 255.0f, 255.0f);
const Color4F Color4F::BLACK = Color4F(0.0f, 0.0f, 0.0f, 255.0f);
const Color4F Color4F::RED = Color4F(255.0f, 0.0f, 0.0f, 255.0f);
const Color4F Color4F::GREEN = Color4F(0.0f, 255.0f, 0.0f, 255.0f);
const Color4F Color4F::BLUE = Color4F(0.0f, 0.0f, 255.0f, 255.0f);
const Color4F Color4F::INVISIBLE = Color4F(255.0f, 255.0f, 255.0f, 0.0f);