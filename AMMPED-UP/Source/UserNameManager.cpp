#include "../Header Files/UserNameManager.h"

UserNameManager* UserNameManager::m_instance = nullptr;
UserNameManager* UserNameManager::getInstance()
{
	if (!m_instance)
	{
		m_instance = new UserNameManager();
	}
	return m_instance;
}

void UserNameManager::setUsername(const std::string& name)
{
	m_username = name;
}

std::string UserNameManager::getUsername() const
{
	return m_username;
}
