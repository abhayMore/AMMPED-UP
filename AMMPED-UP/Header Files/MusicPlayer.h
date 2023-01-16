/*#pragma once
#include "SFML/Audio/Music.hpp"
#include "Game.h"
#include <map>

namespace am {
	class MusicPlayer
	{
	public:
		MusicPlayer();
		void play(MusicID theme);
		void stop();
		void setPaused(bool paused);
		void setVolume(float volume);

	private:
		sf::Music m_music;
		std::map<MusicID, std::string> m_filenames;
		float m_volume;
	};
}*/

