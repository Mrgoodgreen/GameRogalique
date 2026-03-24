#pragma once

namespace XYZEngine { class GameObject; }

namespace XYZRoguelike
{
	class Wall
	{
	public:
		Wall();
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}