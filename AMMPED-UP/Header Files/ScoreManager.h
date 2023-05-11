#pragma once

class ScoreManager {
private:
	int m_score;
	static ScoreManager* m_instance;
	ScoreManager() {
		m_score = 0;
	}
public:
	static ScoreManager* getInstance();
	void setScore(int newScore);
	int getScore() const;
};