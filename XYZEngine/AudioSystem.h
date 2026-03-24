#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <SFML/Audio.hpp>

namespace XYZEngine
{
	class AudioSystem
	{
	public:
		static AudioSystem* Instance();

		void PlaySound(const std::string& name);
		void PlayMusic(const std::string& name, bool loop = true);
		void StopMusic();

		void SetSoundVolume(float volume);
		void SetMusicVolume(float volume);

		void Update();

	private:
		AudioSystem();
		~AudioSystem() {}

		AudioSystem(AudioSystem const&) = delete;
		AudioSystem& operator= (AudioSystem const&) = delete;

		float soundVolume;
		float musicVolume;

		std::vector<std::unique_ptr<sf::Sound>> activeSounds;
		std::unique_ptr<sf::Music> activeMusic;
	};
}
