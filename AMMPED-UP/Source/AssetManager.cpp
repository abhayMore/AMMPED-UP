#include "../Header Files/AssetManager.h"

am::AssetManager::AssetManager()
{
}

am::AssetManager::~AssetManager()
{
}

void am::AssetManager::addTextures(int id, const std::string& filePath, bool wantRepeated)
{
	auto texture = std::make_unique<sf::Texture>();

	if (texture->loadFromFile(filePath))
	{
		texture->setRepeated(wantRepeated);
		m_textures[id] = std::move(texture);
	}
}

void am::AssetManager::addFont(int id, const std::string& filePath)
{
	auto font = std::make_unique<sf::Font>();

	if (font->loadFromFile(filePath))
	{
		m_fonts[id] = std::move(font);
	}
}

void am::AssetManager::addSoundTrack(int id, const std::string& filePath, bool wantLooping)
{
	auto soundTrack = std::make_unique<sf::Music>();

	if (soundTrack->openFromFile(filePath))
	{
		soundTrack->setLoop(wantLooping);
		m_soundTracks[id] = std::move(soundTrack);
	}
}

void am::AssetManager::addSoundEffects(int id, const std::string& filePath)
{
	auto soundBuffer = std::make_unique<sf::SoundBuffer>();
	if (soundBuffer->loadFromFile(filePath))
	{
		m_soundEffects[id] = std::move(soundBuffer);
	}
}



const sf::Texture& am::AssetManager::getTexture(int id) const
{
	// TODO: insert return statement here
	return *(m_textures.at(id).get());
}

const sf::Font& am::AssetManager::getFont(int id) const
{
	// TODO: insert return statement here
	return *(m_fonts.at(id).get());

}

sf::Music& am::AssetManager::getSoundTrack(int id)
{
	// TODO: insert return statement here
	return *(m_soundTracks.at(id).get());
}

const sf::SoundBuffer& am::AssetManager::getSoundEffect(int id) const
{
	// TODO: insert return statement here
	return *(m_soundEffects.at(id).get());
}
