#include "EnemyAIComponent.h"
#include <iostream>

namespace XYZRoguelike
{
	EnemyAIComponent::EnemyAIComponent(XYZEngine::GameObject* gameObject)
		: XYZEngine::Component(gameObject)
	{
	}

	void EnemyAIComponent::Update(float deltaTime)
	{
		if (!target)
		{
			target = XYZEngine::GameWorld::Instance()->FindGameObject("Player");
		}
		
		if (target)
		{
			auto myTransform = gameObject->GetComponent<XYZEngine::TransformComponent>();
			auto targetTransform = target->GetComponent<XYZEngine::TransformComponent>();

			if (myTransform && targetTransform)
			{
				auto pos = myTransform->GetWorldPosition();
				auto targetPos = targetTransform->GetWorldPosition();

				float dx = targetPos.x - pos.x;
				float dy = targetPos.y - pos.y;
				float length = std::sqrt(dx * dx + dy * dy);

				auto body = gameObject->GetComponent<XYZEngine::RigidbodyComponent>();

				if (length > 0 && length <= detectionRadius)
				{
					dx /= length;
					dy /= length;

					if (body)
					{
						body->SetLinearVelocity({dx * speed, dy * speed});
					}
					else
					{
						myTransform->SetWorldPosition(pos.x + dx * speed * deltaTime, pos.y + dy * speed * deltaTime);
					}
				}
				else
				{
					if (body)
					{
						body->SetLinearVelocity({0.f, 0.f});
					}
				}
			}
		}
	}

	void EnemyAIComponent::Render()
	{
	}
}