#pragma once

namespace XYZEngine { class GameObject; }

namespace XYZRoguelike
{
	class Floor
	{
	public:
		Floor();
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}