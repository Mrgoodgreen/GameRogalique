#pragma once

#include "GameObject.h"
#include "PhysicsSystem.h"

namespace XYZEngine
{
	class GameWorld
	{
	public:
		static GameWorld* Instance();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		void LateUpdate();

		GameObject* CreateGameObject();
		GameObject* CreateGameObject(std::string name);
		GameObject* FindGameObject(const std::string& name) const;
		const std::vector<GameObject*>& GetGameObjects() const { return gameObjects; }
		void DestroyGameObject(GameObject* gameObject);
		void Clear();

		void MoveToTop(GameObject* gameObject)
		{
			auto it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
			if (it != gameObjects.end())
			{
				gameObjects.erase(it);
				gameObjects.push_back(gameObject);
			}
		}

		void Print() const;
	private:
		GameWorld() {}
		~GameWorld() {}

		GameWorld(GameWorld const&) = delete;
		GameWorld& operator= (GameWorld const&) = delete;

		float fixedCounter = 0.f;

		std::vector<GameObject*> gameObjects = {};
		std::vector<GameObject*> markedToDestroyGameObjects = {};

		void DestroyGameObjectImmediate(GameObject* gameObject);
	};
}