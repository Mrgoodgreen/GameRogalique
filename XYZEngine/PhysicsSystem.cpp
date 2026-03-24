#include "pch.h"
#include "PhysicsSystem.h"

namespace XYZEngine
{
	PhysicsSystem* PhysicsSystem::Instance()
	{
		static PhysicsSystem physicsSystem;
		return &physicsSystem;
	}

	float PhysicsSystem::GetFixedDeltaTime() const
	{
		return fixedDeltaTime;
	}

	void PhysicsSystem::Update()
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			auto body = colliders[i]->GetGameObject()->GetComponent<RigidbodyComponent>();
			if (body->GetKinematic())
			{
				continue;
			}

			for (int j = 0; j < colliders.size(); j++)
			{
				if (j == i)
				{
					continue;
				}

				sf::FloatRect intersection;
				if (colliders[i]->bounds.intersects(colliders[j]->bounds, intersection))
				{
					if (colliders[i]->isTrigger != colliders[j]->isTrigger)
					{
						if (triggersEnteredPair.find(colliders[i]) == triggersEnteredPair.end() && triggersEnteredPair.find(colliders[j]) == triggersEnteredPair.end())
						{
							auto trigger = new Trigger(colliders[i], colliders[j]);
							colliders[i]->OnTriggerEnter(*trigger);
							colliders[j]->OnTriggerEnter(*trigger);

							triggersEnteredPair.emplace(colliders[i], colliders[j]);
						}
					}
					else if (!colliders[i]->isTrigger)
					{
						float intersectionWidth = intersection.width;
						float intersectionHeight = intersection.height;

						Vector2Df aPosition = { colliders[i]->bounds.left + 0.5f * colliders[i]->bounds.width,  colliders[i]->bounds.top + 0.5f * colliders[i]->bounds.height };
						Vector2Df bPosition = { colliders[j]->bounds.left + 0.5f * colliders[j]->bounds.width,  colliders[j]->bounds.top + 0.5f * colliders[j]->bounds.height };
						auto aTransform = colliders[i]->GetGameObject()->GetComponent<TransformComponent>();

						if (intersectionWidth > intersectionHeight)
						{
							if (aPosition.y < bPosition.y)
							{
								aTransform->MoveBy({ 0, -intersectionHeight });
								colliders[i]->bounds.top -= intersectionHeight;
								std::cout << "Top collision" << std::endl;
							}
							else
							{
								aTransform->MoveBy({ 0, intersectionHeight });
								colliders[i]->bounds.top += intersectionHeight;
								std::cout << "Down collision" << std::endl;
							}
						}
						else
						{
							if (aPosition.x < bPosition.x)
							{
								aTransform->MoveBy({ -intersectionWidth, 0.f });
								colliders[i]->bounds.left -= intersectionWidth;
								std::cout << "Right collision" << std::endl;
							}
							else
							{
								aTransform->MoveBy({ intersectionWidth, 0.f });
								colliders[i]->bounds.left += intersectionWidth;
								std::cout << "Left collision" << std::endl;
							}
						}

						auto collision = new Collision(colliders[i], colliders[j], intersection);
						colliders[i]->OnCollision(*collision);
						colliders[j]->OnCollision(*collision);
					}
				}
			}
		}

		for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair; triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
		{
			++nextTriggeredPair;
			if (!triggeredPair->first->bounds.intersects(triggeredPair->second->bounds))
			{
				auto trigger = new Trigger(triggeredPair->first, triggeredPair->second);
				triggeredPair->first->OnTriggerExit(*trigger);
				triggeredPair->second->OnTriggerExit(*trigger);

				triggersEnteredPair.erase(triggeredPair);
			}
		}
	}

	void PhysicsSystem::Subscribe(ColliderComponent* collider)
	{
		std::cout << "Subscribe " << collider << std::endl;
		colliders.push_back(collider);
	}
	void PhysicsSystem::Unsubscribe(ColliderComponent* collider)
	{
		std::cout << "Unsubscribe " << collider << std::endl;

		colliders.erase(std::remove_if(colliders.begin(), colliders.end(), [collider](ColliderComponent* obj) { return obj == collider; }), colliders.end());
	}
}