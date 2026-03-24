#include "EnemyAIComponent.h"
#include <iostream>
#include "HealthComponent.h"
#include "Logger.h"

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

				if (attackCooldown > 0.0f)
					attackCooldown -= deltaTime;

				if (length > 0 && length <= detectionRadius)
				{
					if (length <= attackRange)
					{
						// Attack player if in range
						if (body) body->SetLinearVelocity({0.f, 0.f}); // Stop moving
						
						if (attackCooldown <= 0.0f)
						{
							auto healthComp = target->GetComponent<HealthComponent>();
							if (healthComp && !healthComp->IsDead())
							{
								XYZEngine::Logger::Log(XYZEngine::LogLevel::INFO, "Enemy attacks Player!");
								healthComp->TakeDamage(10.0f);
								attackCooldown = 1.0f; // Attack once per second
							}
						}
					}
					else
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