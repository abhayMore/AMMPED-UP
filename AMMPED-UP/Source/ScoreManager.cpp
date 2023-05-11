#include "../Header Files/ScoreManager.h"

ScoreManager* ScoreManager::m_instance = nullptr;
ScoreManager* ScoreManager::getInstance()
{
	if (!m_instance)
	{
		m_instance = new ScoreManager();
	}
	return m_instance;
}

void ScoreManager::setScore(int newScore)
{
	m_score = newScore;
}

int ScoreManager::getScore() const
{
	return m_score;
}
