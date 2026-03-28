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
	class Level3
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
						auto wall = std::make_shared<Wall>("wall3");
						wall->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(x * 32.0f, (30 + y) * 32.0f);
						walls.push_back(wall);
					}
					else if (y > 0 && y < 20)
					{
						auto floor = std::make_shared<Floor>("floor3");
						floor->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(x * 32.0f, (30 + y) * 32.0f);
						floors.push_back(floor);
					}
				}
			}

			auto e1 = std::make_shared<Enemy>();
			e1->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(-100.0f, 40 * 32.0f);
			enemies.push_back(e1);

			auto e2 = std::make_shared<Enemy>();
			e2->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(0.0f, 45 * 32.0f);
			enemies.push_back(e2);

			auto e3 = std::make_shared<Enemy>();
			e3->GetGameObject()->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(100.0f, 40 * 32.0f);
			enemies.push_back(e3);
		}

		void Update()
		{
			for (auto it = enemies.begin(); it != enemies.end(); )
			{
				auto& e = *it;
				if (e && e->GetGameObject()->GetComponent<HealthComponent>()->IsDead())
				{
					XYZEngine::GameWorld::Instance()->DestroyGameObject(e->GetGameObject());
					it = enemies.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		bool IsCleared() const
		{
			return enemies.empty();
		}

	private:
		std::vector<std::shared_ptr<Enemy>> enemies;
		std::vector<std::shared_ptr<Wall>> walls;
		std::vector<std::shared_ptr<Floor>> floors;
	};
}