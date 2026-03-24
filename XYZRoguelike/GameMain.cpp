// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"
#include "AudioSystem.h"

using namespace XYZRoguelike;

int main()
{
	XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "XYZRoguelike"));

	XYZEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ball.png");
	XYZEngine::ResourceSystem::Instance()->LoadTexture("wall", "Resources/Textures/wall.png");
	XYZEngine::ResourceSystem::Instance()->LoadTexture("floor", "Resources/Textures/floor.png");

	XYZEngine::AudioSystem::Instance()->PlayMusic("Resources/Audio/music.ogg", true);

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	XYZEngine::Engine::Instance()->Run();

	return 0;
}
