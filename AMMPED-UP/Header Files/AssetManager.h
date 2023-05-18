#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

namespace am
{
	class AssetManager
	{
	private:
		std::map<int, std::unique_ptr<sf::Texture>> m_textures;
		std::map<int, std::unique_ptr<sf::Font>> m_fonts;

		std::map<int, std::unique_ptr<sf::Music>> m_soundTracks;
		std::map<int, std::unique_ptr<sf::SoundBuffer>> m_soundEffects;

	public:
		AssetManager();
		~AssetManager();

		void addTextures(int id, const std::string& filePath, bool wantRepeated = false);
		void addFont(int id, const std::string &filePath);
		void addSoundTrack(int id, const std::string& filePath, bool wantLooping = false);
		void addSoundEffects(int id, const std::string& filePath);


		const sf::Texture& getTexture(int id) const;
		const sf::Font& getFont(int id) const;

		sf::Music& getSoundTrack(int id);
		const sf::SoundBuffer& getSoundEffect(int id) const;
	};
}