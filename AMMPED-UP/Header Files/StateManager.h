#pragma once
#include <stack>
#include <memory>
#include "State.h"

namespace am
{
	class StateManager
	{
	private:
		std::stack<std::unique_ptr<State>> m_stateStack;
		std::unique_ptr<State> m_newState;

		bool m_add, m_replace, m_remove;

	public:
		StateManager();
		~StateManager();

		void add(std::unique_ptr<State> toAdd, bool replace = false);
		void popCurrent();
		void processStateChange();
		std::unique_ptr<State>& getCurrent();
	};
}
