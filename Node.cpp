#include "DXUT.h"
#include "Node.h"
#include "AutoReleasePool.h"
#include <algorithm>
#include "ActionManager.h"
#include <math.h>

USING_NS_DX2DX;

Node::Node() :
_Zorder(0),
_pParent(nullptr),
_Pos(Point::ZERO),
_AnchorPoint(Point::ANCHOR_MIDDLE),
_Center(Point::ZERO),
_Scale(Point(1, 1)),
_CollisionRect(Rect(0, 0, 0, 0)),
_Size(Size::ZERO),
_Color4F(Color4F(254, 254, 254, 254)),
_d3dColor(D3DCOLOR_RGBA(254,254,254,254)),
_RotAngle(0),
_Visible(true),
_IsRunningAction(false)
{
	_ChildPool.reserve(5);
}


Node::~Node()
{
	if (_pParent)
	{
		auto me = std::find(_pParent->_ChildPool.begin(), _pParent->_ChildPool.end(), this);

		ASSERT(me != _pParent->_ChildPool.end(), "부모의 자식풀로부터 나를 찾지못함.")

		_pParent->_ChildPool.erase(me);
	}

	for (auto& child : _ChildPool)
	{
		child->_pParent = nullptr;
		child->Release();
	}
}

Node* Node::Create()
{
	auto node = new Node;
	node->AutoRelease();
	return node;
}

void Node::SetZorder(int zOrder)
{
	_Zorder = zOrder;
	_pParent->ZorderSort();
}

int Node::GetZorder() const
{
	return _Zorder;
}

Node* Node::GetParent() const
{
	return _pParent;
}

void Node::AddChild(Node* const child)
{
	if (child->_pParent)
	{
		ASSERT(false, "이미 지정된 부모가 있어서 AddChild할수 없습니다!");
		return;
	}
	child->_pParent = this;
	child->Retain();
	_ChildPool.push_back(child);

	ZorderSort();
}

void Node::AddChild(Node* const child, int zOrder)
{
	AddChild(child);
	child->SetZorder(zOrder);
}

void Node::ZorderSort()
{
	std::stable_sort(_ChildPool.begin(), _ChildPool.end(), [](Node *first, Node *second) -> bool
															{
																return first->_Zorder < second->_Zorder;
															});
}

void Node::SetPosition(const Point &pos)
{
	_Pos = pos;
}

void Node::SetPosition(float x, float y)
{
	_Pos.x = x;	_Pos.y = y;
}

void Node::SetPositionX(float x)
{
	_Pos.x = x;
}

void Node::SetPositionY(float y)
{
	_Pos.y = y;
}


Point Node::GetPosition() const
{
	return _Pos;
}

float Node::GetPositionX() const
{
	return _Pos.x;
}

float Node::GetPositionY() const
{
	return _Pos.y;
}

Point Node::GetWorldPosition() const
{
	if (!_pParent) return _Pos;

	auto parentBox = _pParent->GetBoundingBox();

	return _Pos + Point(parentBox.left, parentBox.top);
}

float Node::GetWorldPositionX() const
{
	return GetWorldPosition().x;
}

float Node::GetWorldPositionY() const
{
	return GetWorldPosition().y;
}

void Node::SetAnchorPoint(const Point &pos)
{
	_Center = Point(pos.x * _Size.width, pos.y * _Size.height);

	//if (_AnchorPoint != pos)
	//{
		_AnchorPoint = pos;
		SetBoundingBox();
	//}
}

void Node::SetAnchorPoint(float x, float y)
{
	_Center = Point(x * _Size.width, y * _Size.height);

	//if (_AnchorPoint.x != x && _AnchorPoint.y != y)
	//{

		_AnchorPoint.x = x;
		_AnchorPoint.y = y;
		SetBoundingBox();
	//}
}

void Node::SetAnchorPoint(float anchorPos)
{
	_Center = Point(anchorPos * _Size.width, anchorPos * _Size.height);

	//if (_AnchorPoint.x != anchorPos && _AnchorPoint.y != anchorPos)
	//{
		_AnchorPoint.x = _AnchorPoint.y = anchorPos;
		SetBoundingBox();
	//}
}

Point Node::GetAnchorPoint() const
{
	return _AnchorPoint;
}

float Node::GetAnchorPointX() const
{
	return _AnchorPoint.x;
}

float Node::GetAnchorPointY() const
{
	return _AnchorPoint.y;
}

Point Node::GetCenterPoint() const
{
	return _Center;
}

float Node::GetCenterPointX() const
{
	return _Center.x;
}

float Node::GetCenterPointY() const
{
	return _Center.y;
}

void Node::SetScale(const Point &scale)
{
	//if (_Scale == scale) return;

	_Scale = scale;
	SetBoundingBox();
}

void Node::SetScale(float scaleWidth, float scaleHeight)
{
	//if (_Scale.x == scaleWidth && _Scale.y == scaleHeight) return;

	_Scale.x = scaleWidth;
	_Scale.y = scaleHeight;
	SetBoundingBox();
}

void Node::SetScale(float scaleFactor)
{
	//if (_Scale.x == scaleFactor && _Scale.y == scaleFactor) return;

	_Scale.x = _Scale.y = scaleFactor;
	SetBoundingBox();
}

void Node::SetScaleX(float scaleX)
{
	//if (_Scale.x == scaleX) return;

	_Scale.x = scaleX;
	SetBoundingBox();
}

void Node::SetScaleY(float scaleY)
{
	//if (_Scale.y == scaleY) return;

	_Scale.y = scaleY;
	SetBoundingBox();
}

Point Node::GetScale() const
{
	return _Scale;
}

float Node::GetScaleX() const
{
	return _Scale.x;
}

float Node::GetScaleY() const
{
	return _Scale.y;
}

void Node::SetSize(const Size &size)
{
	//if (_Size == size) return;

	_Size = size;
	SetBoundingBox();
}

void Node::SetSize(float width, float height)
{
	//if (_Size.width == width && _Size.height == height) return;

	_Size.width = width;
	_Size.height = height;
	SetBoundingBox();
}

void Node::SetSizeWidth(float width)
{
	//if (_Size.width == width) return;

	_Size.width = width;
	SetBoundingBox();
}

void Node::SetSizeHeight(float height)
{
	//if (_Size.height == height) return;

	_Size.height = height;
	SetBoundingBox();
}

Size Node::GetSize() const
{
	return _Size;
}

float Node::GetSizeWidth() const
{
	return _Size.width;
}

float Node::GetSizeHeight() const
{
	return _Size.height;
}

void Node::SetRotAngle(float degree)
{
	if (360.0f < degree)
		degree -= 360.0f;
	if (-360.0f > degree)
		degree += 360.0f;

	_RotAngle = degree;

	SetBoundingBox();
}

float Node::GetRotAngle() const
{
	return _RotAngle;
}

void Node::SetVisible(bool visible)
{
	_Visible = visible;
}

bool Node::IsVisible() const
{
	return _Visible;
}

void Node::MoveBy(const Point &pos)
{
	_Pos += pos;
}

void Node::MoveBy(float x, float y)
{
	_Pos.x += x;
	_Pos.y += y;
}

void Node::MoveByAngle(float angle, float dist)
{
	float dist_X = cos(D3DXToRadian(angle)) * dist;
	float dist_Y = sin(D3DXToRadian(angle)) * dist;

	MoveBy(dist_X, dist_Y);
}

void Node::RotateBy(float degree)
{
	_RotAngle += degree;
	if (_RotAngle > 360.f)
	{
		_RotAngle -= 360.0f;
	}
	SetBoundingBox();
}

void Node::SetBoundingBox()
{
	Point zero = Point::ZERO;
	_CollisionRect.left = zero.x - _Size.width * _AnchorPoint.x * abs(_Scale.x);
	_CollisionRect.width = _Size.width * abs(_Scale.x);
	_CollisionRect.top = zero.y - _Size.height * _AnchorPoint.y * abs(_Scale.y);
	_CollisionRect.height = _Size.height * abs(_Scale.y);

	//if (_RotAngle == 0.f) return;

	Point center(_CollisionRect.GetMidX(), _CollisionRect.GetMidY());

	Point vertex[4] = { Point(_CollisionRect.GetMinX(), _CollisionRect.GetMinY()),
		Point(_CollisionRect.GetMaxX(), _CollisionRect.GetMinY()),
		Point(_CollisionRect.GetMinX(), _CollisionRect.GetMaxY()),
		Point(_CollisionRect.GetMaxX(), _CollisionRect.GetMaxY()) };

	float left, right, top, bottom;

	for (int i = 0; i < 4; ++i)
	{
		float dist = hypot(vertex[i].x - center.x, vertex[i].y - center.y);
		float angle = atan2(vertex[i].y - center.y, vertex[i].x - center.x);

		vertex[i].x = cos(angle + D3DXToRadian(_RotAngle)) * dist;
		vertex[i].y = sin(angle + D3DXToRadian(_RotAngle)) * dist;

		if (i == 0)
		{
			left = right = vertex[i].x;
			top = bottom = vertex[i].y;
		}

		if (i > 0)
		{
			if (vertex[i].x < left)
			{
				left = vertex[i].x;
			}
			if (vertex[i].x > right)
			{
				right = vertex[i].x;
			}
			if (vertex[i].y < top)
			{
				top = vertex[i].y;
			}
			if (vertex[i].y > bottom)
			{
				bottom = vertex[i].y;
			}
		}
	}

	_CollisionRect.left = left;
	_CollisionRect.top = top;
	_CollisionRect.width = right - left;
	_CollisionRect.height = bottom - top;
}

Rect Node::GetBoundingBox() const
{
	//float disX = _Size.width * abs(_Scale.x) * _AnchorPoint.x;
	//float disY = _Size.height * abs(_Scale.y) * _AnchorPoint.y;
	//return _CollisionRect.GetOffsetBox(GetWorldPositionX() - disX,
	//							GetWorldPositionY() - disY);

	Point worldPos = GetWorldPosition();
	Rect rect = _CollisionRect;
	rect.left = worldPos.x - (rect.width * _AnchorPoint.x);
	rect.top = worldPos.y - (rect.height * _AnchorPoint.y);

	return rect;
}

void Node::Draw(LPD3DXSPRITE d3dxSprite)
{
	if (this->IsVisible())
	for (auto child : _ChildPool)
	{
		child->Draw(d3dxSprite);
	}
}

void Node::SetColor(Color4F color)
{
	_Color4F = color;
	SetD3DColor();
}

void Node::SetColor(float r, float g, float b, float a)
{
	_Color4F.a = a;
	_Color4F.r = r;
	_Color4F.g = g;
	_Color4F.b = b;
	SetD3DColor();
}

void Node::SetColorA(float a)
{
	_Color4F.a = a;
	SetD3DColor();
}

void Node::SetColorR(float r)
{
	_Color4F.r = r;
	SetD3DColor();
}

void Node::SetColorG(float g)
{
	_Color4F.g = g;
	SetD3DColor();
}

void Node::SetColorB(float b)
{
	_Color4F.b = b;
	SetD3DColor();
}

void Node::SetD3DColor()
{
	_d3dColor = D3DCOLOR_RGBA((int)_Color4F.r,
		(int)_Color4F.g,
		(int)_Color4F.b,
		(int)_Color4F.a);
}

Color4F Node::GetColor() const
{
	return _Color4F;
}

float Node::GetColorR() const
{
	return _Color4F.r;
}

float Node::GetColorG() const
{
	return _Color4F.g;
}

float Node::GetColorB() const
{
	return _Color4F.b;
}

float Node::GetColorA() const
{
	return _Color4F.a;
}

D3DCOLOR Node::GetD3DColor() const
{
	return _d3dColor;
}

void Node::TintBy(Color4F color)
{
	_Color4F += color;

	SetD3DColor();
}

void Node::RunAction(Action* act)
{
	if (!_IsRunningAction)
	{
		ActionManager::GetInstance()->AddAction(act, this);
		_IsRunningAction = true;
	}
}

void Node::StopAction()
{
	_IsRunningAction = false;
	ActionManager::GetInstance()->DeleteNodeAction(this);
}