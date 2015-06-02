#pragma once
#include "Ref.h"
#include "dx2dxStruct.h"
#include <vector>

NS_DX2DX
{
	class Action;

	class Node
		: public Ref
	{
		friend class Director;
		friend class ActionManager;
	private:
		DISALLOW_COPY_AND_ASSIGN(Node);

	protected:
		Node();
		virtual ~Node();

	public:
		static Node* Create();

	protected:
		std::vector<Node*> _ChildPool;

	private:
		int _Zorder;
		Node* _pParent;
		Point _Pos;
		Point _AnchorPoint;
		Point _Center;
		Point _Scale;
		Rect _CollisionRect;
		Size _Size;
		Color4F _Color4F;
		D3DCOLOR _d3dColor;
		float _RotAngle;

		bool _Visible;

		bool _IsRunningAction;

	public:
		void SetZorder(int zOrder);
		int GetZorder() const;
		Node* GetParent() const;
		
		void AddChild(Node* const child);
		void AddChild(Node* const child, int zOrder);

	private:
		void ZorderSort();

	public:
		virtual void SetPosition(const Point &pos);
		virtual void SetPosition(float x, float y);
		virtual void SetPositionX(float x);
		virtual void SetPositionY(float y);

		Point GetPosition() const;
		float GetPositionX() const;
		float GetPositionY() const;

		Point GetWorldPosition() const;
		float GetWorldPositionX() const;
		float GetWorldPositionY() const;

		virtual void SetAnchorPoint(const Point &pos);
		virtual void SetAnchorPoint(float x, float y);
		virtual void SetAnchorPoint(float anchorPos);

		Point GetAnchorPoint() const;
		float GetAnchorPointX() const;
		float GetAnchorPointY() const;

		Point GetCenterPoint() const;
		float GetCenterPointX() const;
		float GetCenterPointY() const;

		virtual void SetScale(const Point &scale);
		virtual void SetScale(float scaleX, float scaleY);
		virtual void SetScale(float scaleFactor);
		virtual void SetScaleX(float scaleX);
		virtual void SetScaleY(float scaleY);

		Point GetScale() const;
		float GetScaleX() const;
		float GetScaleY() const;

		virtual void SetSize(const Size &size);
		virtual void SetSize(float width, float height);
		virtual void SetSizeWidth(float width);
		virtual void SetSizeHeight(float height);

		Size GetSize() const;
		float GetSizeWidth() const;
		float GetSizeHeight() const;

		void SetRotAngle(float degree);
		float GetRotAngle() const;

		void SetVisible(bool visible);
		bool IsVisible() const;

	public:
		virtual void MoveBy(const Point &pos);
		virtual void MoveBy(float x, float y);
		virtual void MoveByAngle(float angle, float dist);

		virtual void RotateBy(float degree);

	protected:
		void SetBoundingBox();
	public:
		Rect GetBoundingBox() const;

	protected:
		virtual void Draw(LPD3DXSPRITE d3dxSprite);

	private:
		void SetD3DColor();

	public:
		virtual void SetColor(Color4F color);
		virtual void SetColor(float r, float g, float b, float a = 255);
		virtual void SetColorA(float a);
		virtual void SetColorR(float r);
		virtual void SetColorG(float g);
		virtual void SetColorB(float b);


		Color4F GetColor() const;
		float GetColorR() const;
		float GetColorG() const;
		float GetColorB() const;
		float GetColorA() const;

		D3DCOLOR GetD3DColor() const;

		void TintBy(Color4F color);
		//void TintBy(float r, float g, float b, float a = 254);

	public:
		//virtual void Init() {};

		// * Scene에서의 Update호출시 가장 먼저 호출됨
		// * 이 함수를 재정의할경우 자식들에게 EarlyUpdate를 호출할거라면 Node::EarlyUpdate()를 재정의한 함수의 맨 마지막 줄에 넣어야 한다.
		virtual void EarlyUpdate()
		{
			for (auto child : _ChildPool)
			{
				child->EarlyUpdate();
			}
		}

		//virtual void OnExit() {};

	public:
		void RunAction(Action *act);
		bool IsRunningAction() { return _IsRunningAction; }
		void StopAction();
	private:
		void ActionFinish() { _IsRunningAction = false; }
	};
}
