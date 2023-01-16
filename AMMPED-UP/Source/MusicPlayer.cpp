/*#include "../Header Files/MusicPlayer.h"

am::MusicPlayer::MusicPlayer() : m_music(), m_filenames(), m_volume(100.0f)
{
	m_filenames[MusicID::MenuTheme] = "Resources/assets/music/forest.wav";
	m_filenames[MusicID::MissionTheme] = "Resources/assets/music/Snake Baron.ogg";

}

void am::MusicPlayer::play(MusicID theme)
{
	std::string filename = m_filenames[theme];
	if (!m_music.openFromFile(filename))
	{
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	}

	m_music.setVolume(m_volume);
	m_music.setLoop(true);
	m_music.play();

}

void am::MusicPlayer::stop()
{
	m_music.stop();
}

void am::MusicPlayer::setPaused(bool paused)
{
	if (paused)
		m_music.pause();
	else
		m_music.play();
}

void am::MusicPlayer::setVolume(float volume)
{
	m_volume = volume;
}
*/