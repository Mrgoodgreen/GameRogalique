#pragma once

#include <string>

namespace XYZEngine { class GameObject; }

namespace XYZRoguelike
{
	class Floor
	{
	public:
		Floor(const std::string& textureName = "floor");
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}