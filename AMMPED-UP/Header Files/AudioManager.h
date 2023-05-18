#pragma once
#include "SFML/Audio/Music.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <functional>

enum SFX_ID
{
	DAMAGE_SFX_SOUND = 0,
	BLAST_SFX_SOUND,
	COIN_EAT_SFX_SOUND,
	ENEMY_DEATH_SFX_SOUND
};
class AudioManager
{
private:
	sf::Music& m_mainMenuMusic;
	sf::Music& m_inGameMusic;
	sf::Sound* m_damageSFX;
	sf::Sound* m_blastSFX;
	sf::Sound* m_coinEatSfx;
	sf::Sound* m_enemyDeathSFX;
	
	bool m_isMuted;
	float m_overallVolume;
	float m_inGameVolume;
	float m_sfxVolume;
	static AudioManager* m_instance;

	AudioManager(sf::Music& mainMenuMusic, 
				sf::Music& gameMusic, 
				const sf::SoundBuffer& damageSFX, 
				const sf::SoundBuffer& blastSFX,
				const sf::SoundBuffer& coinEatSfx,
				const sf::SoundBuffer& enemyDeathSFX):
		m_mainMenuMusic(mainMenuMusic),
		m_inGameMusic(gameMusic),
		m_damageSFX(new sf::Sound()),
		m_blastSFX(new sf::Sound()),
		m_coinEatSfx(new sf::Sound()),
		m_enemyDeathSFX(new sf::Sound()),
		m_overallVolume(50.0f), 
		m_inGameVolume(100.0f),
		m_sfxVolume(100.0f),
		m_isMuted(false)
	{
		m_damageSFX->setBuffer(damageSFX);
		m_blastSFX->setBuffer(blastSFX);
		m_coinEatSfx->setBuffer(coinEatSfx);
		m_enemyDeathSFX->setBuffer(enemyDeathSFX);

		m_mainMenuMusic.setLoop(true);
		m_inGameMusic.setLoop(true);
		updateMusicVolume();
		m_mainMenuMusic.play();
	}
	void updateMusicVolume() {
		if (m_isMuted) {
			m_mainMenuMusic.setVolume(0.f);
			m_inGameMusic.setVolume(0.f);
		}
		else {
			float overallVolume = m_overallVolume * 0.01f;
			float inGameVolume = overallVolume * (m_inGameVolume * 0.01f);
			float sfxVolume = overallVolume * (m_sfxVolume * 0.01f);
			m_mainMenuMusic.setVolume(overallVolume * 100.f);
			m_inGameMusic.setVolume(inGameVolume * 100.f);
			
			m_damageSFX->setVolume(sfxVolume * 100.f);
			m_blastSFX->setVolume(sfxVolume * 100.f);
			m_coinEatSfx->setVolume(sfxVolume * 100.f);
			m_enemyDeathSFX->setVolume(sfxVolume * 100.f);
		}
	}
public:
	static AudioManager& getInstance(sf::Music& mainMenuMusic, 
									sf::Music& inGameMusic,
									const sf::SoundBuffer& damageSFX,
									const sf::SoundBuffer& blastSFX,
									const sf::SoundBuffer& coinEatSfx,
									const sf::SoundBuffer& enemyDeathSFX
		);
	void setOverallVolume(float volume);
	void setInGameVolume(float volume);
	void setSFXVolume(float volume);
	float getOverallVolume();	
	float getInGameVolume() const;
	float getSFXVolume() const;

	void mute();	
	bool isMuted();	
	void unmute();
	void startMainMenuMusic();
	void stopMainMenuMusic();
	void startInGameMusic();
	void stopInGameMusic();
	void startSFXMusic(SFX_ID id);
	void stopSFXMusic(SFX_ID id);
	void pauseInGameMusic();
	sf::SoundStream::Status isMenuMusicPlaying();
	sf::SoundStream::Status isInGameMusicPlaying();
	sf::SoundStream::Status isSFXPlaying();
	
};

