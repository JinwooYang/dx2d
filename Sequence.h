#pragma once
#include "Action.h"
#include <vector>

NS_DX2DX
{
	class Sequence
		: public dx2dx::Action
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Sequence);
		Sequence();
		~Sequence();


	private:
		std::vector<Action*> _ActionVec;
		int _CurSeq;

		void Init(std::initializer_list<Action*> list);
		void Init(std::vector<Action*> actionVec);

	public:
		static Sequence* Create(std::initializer_list<Action*> list);
		static Sequence* Create(std::vector<Action*> actionVec);

		virtual void OnStartWithTarget(Node* const node) override;
		virtual void Run(Node* const node) override;

		virtual Action* Clone() const override;
		virtual Action* Reverse() const override;
	};
}