#pragma once

#include "Component.h"
#include "InputComponent.h"
#include "RigidbodyComponent.h"
#include "HealthComponent.h"
#include <vector>

namespace XYZRoguelike
{
	class PlayerMovementComponent : public XYZEngine::Component
	{
	public:
		PlayerMovementComponent(XYZEngine::GameObject* gameObject);
		~PlayerMovementComponent() override = default;

		void Update(float deltaTime) override;
		void Render() override;

	private:
		void AttackEnemies();

		XYZEngine::InputComponent* input = nullptr;
		XYZEngine::RigidbodyComponent* rb = nullptr;
		float speed = 0.2f;
		float attackCooldown = 0.f;
		float attackRange = 60.f;
	};
}