#pragma once

#include <string>

namespace XYZEngine { class GameObject; }

namespace XYZRoguelike
{
	class Wall
	{
	public:
		Wall(const std::string& textureName = "wall");
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}