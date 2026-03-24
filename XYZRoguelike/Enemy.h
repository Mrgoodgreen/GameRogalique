#pragma once

namespace XYZEngine { class GameObject; }

namespace XYZRoguelike
{
	class Enemy
	{
	public:
		Enemy();
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}