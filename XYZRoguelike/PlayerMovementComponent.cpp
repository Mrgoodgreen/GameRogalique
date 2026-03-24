#include "PlayerMovementComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include <cmath>

namespace XYZRoguelike
{
	PlayerMovementComponent::PlayerMovementComponent(XYZEngine::GameObject* gameObject)
		: XYZEngine::Component(gameObject)
	{
	}

	void PlayerMovementComponent::Update(float deltaTime)
	{
		if (!input)
		{
			input = gameObject->GetComponent<XYZEngine::InputComponent>();
		}
		if (!rb)
		{
			rb = gameObject->GetComponent<XYZEngine::RigidbodyComponent>();
		}

		if (input && rb)
		{
			float h = input->GetHorizontalAxis();
			float v = input->GetVerticalAxis(); // Be careful with sign: in XYZEngine, W often gives +1 but SFML y-axis is inverted (down is +). 
			// Let's check InputComponent: W gives +1. If up is negative y, we should invert this.
			// Currently: W -> +1, S -> -1 
			
			// We'll normalize the vector so diagonal movement isn't faster
			float len = std::sqrt(h * h + v * v);
			if (len > 0.0f)
			{
				h /= len;
				v /= len;
			}

			// In most 2D engines, negative Y is UP. W returns +1. 
			// We already have correct axis from input, just need to set it without negating if it's inversed.
			rb->SetLinearVelocity({ h * speed, v * speed });
		}

		if (attackCooldown > 0.0f)
			attackCooldown -= deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && attackCooldown <= 0.0f)
		{
			AttackEnemies();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
		{
			// Искусственное создание критической ситуации
			XYZ_ASSERT(false, "Artificially created critical situation! Player pressed F9.");
		}
	}

	void PlayerMovementComponent::AttackEnemies()
	{
		attackCooldown = 0.5f; // Attack twice a second
		auto myTransform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		auto& objects = XYZEngine::GameWorld::Instance()->GetGameObjects();

		for (auto& obj : objects)
		{
			if (obj && obj->GetName() == "Enemy")
			{
				auto targetTransform = obj->GetComponent<XYZEngine::TransformComponent>();
				auto healthComp = obj->GetComponent<HealthComponent>();

				if (targetTransform && healthComp && !healthComp->IsDead())
				{
					auto pos = myTransform->GetWorldPosition();
					auto targetPos = targetTransform->GetWorldPosition();
					float dist = std::sqrt(std::pow(targetPos.x - pos.x, 2) + std::pow(targetPos.y - pos.y, 2));

					if (dist <= attackRange)
					{
						XYZEngine::Logger::Log(XYZEngine::LogLevel::INFO, "Player attacks Enemy!");
						healthComp->TakeDamage(25.0f);
						
						if (healthComp->IsDead())
						{
							XYZEngine::GameWorld::Instance()->DestroyGameObject(obj);
						}
					}
				}
			}
		}
	}

	void PlayerMovementComponent::Render()
	{
	}
}