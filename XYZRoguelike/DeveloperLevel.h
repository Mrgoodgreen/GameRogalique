#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Floor.h"
#include "GameWorld.h"
#include <memory>
#include <vector>

namespace XYZRoguelike
{
	class DeveloperLevel
	{
	public:
		void Start();
		void Restart();
		void Stop();

	private:
		XYZEngine::GameObject* camera;
		std::shared_ptr<Player> player;
		std::shared_ptr<Enemy> enemy;
		std::vector<std::shared_ptr<Wall>> walls;
		std::vector<std::shared_ptr<Floor>> floors;
	};
}