#include "../Header Files/AudioManager.h"

AudioManager* AudioManager::m_instance = nullptr;

AudioManager& AudioManager::getInstance(sf::Music& mainMenuMusic, 
										sf::Music& inGameMusic, 
										const sf::SoundBuffer& damageSFX,
										const sf::SoundBuffer& blastSFX,
										const sf::SoundBuffer& coinEatSfx,
										const sf::SoundBuffer& enemyDeathSFX
	)
{
	if (m_instance == nullptr) {
		m_instance = new AudioManager(	mainMenuMusic, 
										inGameMusic, 
										damageSFX,
										blastSFX,
										coinEatSfx,
										enemyDeathSFX
		);
	}
	return *m_instance;
}

void AudioManager::setOverallVolume(float volume)
{
	m_overallVolume = volume;
	updateMusicVolume();
}

void AudioManager::setInGameVolume(float volume)
{
	m_inGameVolume = volume;
	updateMusicVolume();
}

void AudioManager::setSFXVolume(float volume)
{
	m_sfxVolume = volume;
	updateMusicVolume();
}

float AudioManager::getOverallVolume()
{
	return m_overallVolume;
}

float AudioManager::getInGameVolume() const
{
	return m_inGameVolume;
}

float AudioManager::getSFXVolume() const
{
	return m_sfxVolume;
}

void AudioManager::mute()
{
	m_isMuted = true;
	updateMusicVolume();
}

bool AudioManager::isMuted()
{
	return m_isMuted;
}

void AudioManager::unmute()
{
	m_isMuted = false;
	updateMusicVolume();
}

void AudioManager::startMainMenuMusic()
{
	m_mainMenuMusic.play();
}

void AudioManager::stopMainMenuMusic()
{
	m_mainMenuMusic.stop();
}

void AudioManager::startInGameMusic()
{
	m_inGameMusic.play();

}

void AudioManager::stopInGameMusic()
{
	m_inGameMusic.stop();
}

void AudioManager::startSFXMusic(SFX_ID id)
{
	if(id == DAMAGE_SFX_SOUND)
		m_damageSFX->play();
	if(id == BLAST_SFX_SOUND)
		m_blastSFX->play();
	if(id == COIN_EAT_SFX_SOUND)
		m_coinEatSfx->play();
	if(id == ENEMY_DEATH_SFX_SOUND)
		m_enemyDeathSFX->play();
}

void AudioManager::stopSFXMusic(SFX_ID id)
{
	if (id == DAMAGE_SFX_SOUND)
		m_damageSFX->stop();
	if (id == BLAST_SFX_SOUND)
		m_blastSFX->stop();
	if (id == COIN_EAT_SFX_SOUND)
		m_coinEatSfx->stop();
	if (id == ENEMY_DEATH_SFX_SOUND)
		m_enemyDeathSFX->stop();
}

void AudioManager::pauseInGameMusic()
{
	m_inGameMusic.pause();
}

sf::SoundStream::Status AudioManager::isMenuMusicPlaying()
{
	if (m_mainMenuMusic.getStatus() == sf::SoundStream::Playing)
	{
		return sf::SoundStream::Playing;
	}
	
}

sf::SoundStream::Status AudioManager::isInGameMusicPlaying()
{
	if (m_inGameMusic.getStatus() == sf::SoundStream::Playing)
	{
		return sf::SoundStream::Playing;
	}
}

sf::SoundStream::Status AudioManager::isSFXPlaying()
{
	if ((m_damageSFX->getStatus() == sf::SoundStream::Playing) &&
		(m_blastSFX->getStatus() == sf::SoundStream::Playing) &&
		(m_coinEatSfx->getStatus() == sf::SoundStream::Playing) &&
		(m_enemyDeathSFX->getStatus() == sf::SoundStream::Playing)
		)
	{
		return sf::SoundStream::Playing;
	}
}
