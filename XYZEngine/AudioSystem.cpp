#include "pch.h"
#include "AudioSystem.h"
#include "ResourceSystem.h"
#include <iostream>

namespace XYZEngine
{
	AudioSystem* AudioSystem::Instance()
	{
		static AudioSystem instance;
		return &instance;
	}

	AudioSystem::AudioSystem()
		: soundVolume(100.f), musicVolume(100.f)
	{
	}

	void AudioSystem::PlaySound(const std::string& name)
	{
		const sf::SoundBuffer* buffer = ResourceSystem::Instance()->GetSoundBufferShared(name);
		if (buffer)
		{
			auto sound = std::make_unique<sf::Sound>();
			sound->setBuffer(*buffer);
			sound->setVolume(soundVolume);
			sound->play();
			activeSounds.push_back(std::move(sound));
		}
	}

	void AudioSystem::PlayMusic(const std::string& name, bool loop)
	{
		if (activeMusic)
		{
			activeMusic->stop();
		}

		activeMusic = std::make_unique<sf::Music>();
		if (activeMusic->openFromFile(name))
		{
			activeMusic->setLoop(loop);
			activeMusic->setVolume(musicVolume);
			activeMusic->play();
		}
		else
		{
			std::cerr << "WARNING: Could not open music file " << name << "!" << std::endl;
		}
	}

	void AudioSystem::StopMusic()
	{
		if (activeMusic)
		{
			activeMusic->stop();
		}
	}

	void AudioSystem::SetSoundVolume(float volume)
	{
		soundVolume = volume;
		for (auto& sound : activeSounds)
		{
			sound->setVolume(soundVolume);
		}
	}

	void AudioSystem::SetMusicVolume(float volume)
	{
		musicVolume = volume;
		if (activeMusic)
		{
			activeMusic->setVolume(musicVolume);
		}
	}

	void AudioSystem::Update()
	{
		activeSounds.erase(std::remove_if(activeSounds.begin(), activeSounds.end(),
			[](const std::unique_ptr<sf::Sound>& sound) {
				return sound->getStatus() == sf::Sound::Stopped;
			}), activeSounds.end());
	}
}
