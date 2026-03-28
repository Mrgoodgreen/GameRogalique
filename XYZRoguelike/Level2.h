#pragma once
#include <memory>
#include <vector>
#include "Enemy.h"
#include "Wall.h"
#include "Floor.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "HealthComponent.h"

namespace XYZRoguelike
{
	class Level2
	{
	public:
		void Load()
		{
			for (int x = -10; x <= 10; ++x)
			{
				for (int y = 0; y <= 20; ++y)
				{
					if (y == 0 && (x >= -2 && x <= 2)) continue; // door gap
					if (x == -10 || x == 10 || y == 20)
					{
						if (y == 20 && x >= -2 && x <= 2)
						{
							auto floor = std::make_shared<Floor>("floor2");
							floor->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(x * 32.0f, (10 + y) * 32.0f);
							floors.push_back(floor);

							auto wall = std::make_shared<Wall>("wall2");
							wall->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(x * 32.0f, (10 + y) * 32.0f);
							doors.push_back(wall);
						}
						else
						{
							auto wall = std::make_shared<Wall>("wall2");
							wall->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(x * 32.0f, (10 + y) * 32.0f);
							walls.push_back(wall);
						}
					}
					else if (y > 0 && y < 20)
					{
						auto floor = std::make_shared<Floor>("floor2");
						floor->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(x * 32.0f, (10 + y) * 32.0f);
						floors.push_back(floor);
					}
				}
			}

			enemy1 = std::make_shared<Enemy>();
			enemy1->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(-100.0f, 15 * 32.0f);

			enemy2 = std::make_shared<Enemy>();
			enemy2->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(100.0f, 15 * 32.0f);
		}

		void Update()
		{
			if (enemy1 && enemy1->GetGameObject()->GetComponent<HealthComponent>()->IsDead())
			{
				XYZEngine::GameWorld::Instance()->DestroyGameObject(enemy1->GetGameObject());
				enemy1.reset();
			}
			if (enemy2 && enemy2->GetGameObject()->GetComponent<HealthComponent>()->IsDead())
			{
				XYZEngine::GameWorld::Instance()->DestroyGameObject(enemy2->GetGameObject());
				enemy2.reset();
			}
		}

		bool IsCleared() const
		{
			return !enemy1 && !enemy2;
		}

		void OpenDoor()
		{
			for (auto& d : doors) {
				if (d) {
					XYZEngine::GameWorld::Instance()->DestroyGameObject(d->GetGameObject());
				}
			}
			doors.clear();
			doorOpened = true;
		}

		bool IsDoorOpened() const { return doorOpened; }

	private:
		std::shared_ptr<Enemy> enemy1;
		std::shared_ptr<Enemy> enemy2;
		std::vector<std::shared_ptr<Wall>> doors;
		std::vector<std::shared_ptr<Wall>> walls;
		std::vector<std::shared_ptr<Floor>> floors;
		bool doorOpened = false;
	};
}