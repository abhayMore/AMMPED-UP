#include "../Header Files/StateManager.h"

am::StateManager::StateManager() : m_add(false), m_replace(false), m_remove(false)
{

}

am::StateManager::~StateManager()
{

}

void am::StateManager::add(std::unique_ptr<State> toAdd, bool replace)
{
	m_add = true;

	m_newState = std::move(toAdd);
	m_replace = replace;
}

void am::StateManager::popCurrent()
{
	m_remove = true;
}

void am::StateManager::processStateChange()
{
	if (m_remove && (!m_stateStack.empty()))
	{
		m_stateStack.pop();
		if (!m_stateStack.empty())
			m_stateStack.top()->start();
		m_remove = false;
	}
	if (m_add)
	{
		if (m_replace && (!m_stateStack.empty()))
		{
			m_stateStack.pop();
			m_replace = false;
		}
		if (!m_stateStack.empty())
		{
			m_stateStack.top()->pause();
		}
		m_stateStack.push(std::move(m_newState));
		m_stateStack.top()->init();
		m_stateStack.top()->start();

		m_add = false;
	}

}

std::unique_ptr<am::State>& am::StateManager::getCurrent()
{
	// TODO: insert return statement here
	return m_stateStack.top();
}
