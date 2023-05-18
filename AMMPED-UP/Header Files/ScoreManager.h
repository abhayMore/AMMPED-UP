#pragma once

class ScoreManager {
private:
	int m_score;

	//Show Score in leaderboard only when game is won and over
	bool gameOverFlag;
	static ScoreManager* m_instance;
	ScoreManager() {
		m_score = 0;
		gameOverFlag = false; 
	}
public:
	static ScoreManager* getInstance();
	void setScore(int newScore);
	int getScore() const;
	
	void setGameOverFlag(bool flag);
	bool getGameOverFlag() const;
};