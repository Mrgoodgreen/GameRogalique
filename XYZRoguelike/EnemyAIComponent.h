#pragma once

#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "GameWorld.h"

namespace XYZRoguelike
{
	class EnemyAIComponent : public XYZEngine::Component
	{
	public:
		EnemyAIComponent(XYZEngine::GameObject* gameObject);
		~EnemyAIComponent() override = default;

		void Update(float deltaTime) override;
		void Render() override;

		void SetTarget(XYZEngine::GameObject* newTarget) { target = newTarget; }

	private:
		XYZEngine::GameObject* target = nullptr;
		float speed = 0.14f;
		float detectionRadius = 150.0f; // Chase within this distance
	};
}