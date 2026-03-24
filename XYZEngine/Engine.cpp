#include "pch.h"
#include "Engine.h"
#include <iostream>
#include "GameWorld.h"
#include "RenderSystem.h"
#include "AudioSystem.h"
#include "Logger.h"

namespace XYZEngine
{
	Engine* Engine::Instance()
	{
		static Engine instance;
		return &instance;
	}

	Engine::Engine()
	{
		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);
		Logger::Init();
		Logger::Log(LogLevel::TRACE, "Engine constructor called.");
	}

	void Engine::Run()
	{
		Logger::Log(LogLevel::INFO, "Engine is running.");
		sf::Clock gameClock;
		sf::Event event;
		
		while (RenderSystem::Instance()->GetMainWindow().isOpen())
		{
			try 
			{
				sf::Time dt = gameClock.restart();
				float deltaTime = dt.asSeconds();

				while (RenderSystem::Instance()->GetMainWindow().pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						RenderSystem::Instance()->GetMainWindow().close();
					}
				}

				if (!RenderSystem::Instance()->GetMainWindow().isOpen())
				{
					break;
				}

				RenderSystem::Instance()->GetMainWindow().clear();

				GameWorld::Instance()->Update(deltaTime);
				GameWorld::Instance()->FixedUpdate(deltaTime);
				GameWorld::Instance()->Render();
				GameWorld::Instance()->LateUpdate();
				AudioSystem::Instance()->Update();

				RenderSystem::Instance()->GetMainWindow().display();
			}
			catch (const std::exception& e)
			{
				// Перехватываем критическую ситуацию, чтобы игра не "крашилась", а продолжала работу
				Logger::Log(LogLevel::ERR, std::string("Engine recovered from exception: ") + e.what());
				
				// Подстраховка таймера, чтобы следующий кадр не "прыгнул" из-за времени потраченного на ошибку
				gameClock.restart();
			}
		}

		Logger::Log(LogLevel::INFO, "Engine shut down smoothly.");
	}
}