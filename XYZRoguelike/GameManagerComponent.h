#pragma once
#include "Component.h"
#include "Enemy.h"
#include "Wall.h"
#include "Floor.h"
#include "GameWorld.h"
#include <vector>
#include <memory>
#include "TransformComponent.h"
#include "HealthComponent.h"
#include "Level2.h"
#include "Level3.h"

namespace XYZRoguelike
{
	class GameManagerComponent : public XYZEngine::Component
	{
	public:
		GameManagerComponent(XYZEngine::GameObject* gameObject) 
			: XYZEngine::Component(gameObject), currentLevel(1) {}

		~GameManagerComponent() override = default;

		void Update(float deltaTime) override
		{
			if (currentLevel == 1)
			{
				if (enemy1 && enemy1->GetGameObject()->GetComponent<HealthComponent>()->IsDead())
				{
					XYZEngine::GameWorld::Instance()->DestroyGameObject(enemy1->GetGameObject());
					enemy1.reset();

					for (auto& d : doors1) {
						if (d) {
							XYZEngine::GameWorld::Instance()->DestroyGameObject(d->GetGameObject());
						}
					}
					doors1.clear();
					
					level2 = std::make_unique<Level2>();
					level2->Load();
					
					// Move player to top so it's drawn above Level2
					auto player = XYZEngine::GameWorld::Instance()->FindGameObject("Player");
					if (player) {
						XYZEngine::GameWorld::Instance()->MoveToTop(player);
					}

					currentLevel = 2;
				}
			}
			else if (currentLevel == 2)
			{
				if (level2)
				{
					level2->Update();
					if (level2->IsCleared() && !level2->IsDoorOpened())
					{
						level2->OpenDoor();
						level3 = std::make_unique<Level3>();
						level3->Load();

						// Move player to top so it's drawn above Level3
						auto player = XYZEngine::GameWorld::Instance()->FindGameObject("Player");
						if (player) {
							XYZEngine::GameWorld::Instance()->MoveToTop(player);
						}

						currentLevel = 3;
					}
				}
			}
			else if (currentLevel == 3)
			{
				if (level3)
				{
					level3->Update();
				}
			}
		}

		void Render() override {}

		void SetLevel1Data(std::shared_ptr<Enemy> e, const std::vector<std::shared_ptr<Wall>>& d)
		{
			enemy1 = e;
			doors1 = d;
			currentLevel = 1;
		}

	private:
		int currentLevel;
		std::shared_ptr<Enemy> enemy1;
		std::vector<std::shared_ptr<Wall>> doors1;

		std::unique_ptr<Level2> level2;
		std::unique_ptr<Level3> level3;
	};
}
