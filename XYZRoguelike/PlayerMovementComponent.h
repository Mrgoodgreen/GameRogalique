#pragma once

#include "Component.h"
#include "InputComponent.h"
#include "RigidbodyComponent.h"

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
		XYZEngine::InputComponent* input = nullptr;
		XYZEngine::RigidbodyComponent* rb = nullptr;
		float speed = 0.2f;
	};
}