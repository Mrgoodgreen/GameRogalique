#include "DeveloperLevel.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "RenderSystem.h"
#include "Logger.h"

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		Logger::Log(LogLevel::INFO, "DeveloperLevel starting...");

		camera = GameWorld::Instance()->CreateGameObject("Camera");
		auto camComp = camera->AddComponent<CameraComponent>();
		XYZ_ASSERT(camComp != nullptr, "CameraComponent could not be added!");

		camComp->SetWindow(&RenderSystem::Instance()->GetMainWindow());
		camComp->SetBaseResolution(1280, 720);
		camera->GetComponent<TransformComponent>()->SetWorldPosition(0.0f, 0.0f);

		// 30x30 area
		for(int x = -10; x <= 10; ++x)
		{
			for(int y = -10; y <= 10; ++y)
			{
				if (x == -10 || x == 10 || y == -10 || y == 10)
				{
					auto wall = std::make_shared<Wall>();
					wall->GetGameObject()->GetComponent<TransformComponent>()->SetWorldPosition(x * 32.0f, y * 32.0f);
					walls.push_back(wall);
				}
				else
				{
					auto floor = std::make_shared<Floor>();
					floor->GetGameObject()->GetComponent<TransformComponent>()->SetWorldPosition(x * 32.0f, y * 32.0f);
					floors.push_back(floor);
				}
			}
		}

		player = std::make_shared<Player>();
		player->GetGameObject()->GetComponent<TransformComponent>()->SetWorldPosition(0.0f, 0.0f);

		enemy = std::make_shared<Enemy>();
		enemy->GetGameObject()->GetComponent<TransformComponent>()->SetWorldPosition(128.0f, 128.0f);

		Logger::Log(LogLevel::TRACE, "DeveloperLevel start complete.");
	}
	void DeveloperLevel::Restart()
	{
		Logger::Log(LogLevel::INFO, "DeveloperLevel restarting...");
		Stop();
		Start();
	}
	void DeveloperLevel::Stop() 
	{
		Logger::Log(LogLevel::INFO, "DeveloperLevel stopping...");
		GameWorld::Instance()->Clear();
		walls.clear();
		floors.clear();
		player.reset();
		enemy.reset();
		camera = nullptr;
	}
}