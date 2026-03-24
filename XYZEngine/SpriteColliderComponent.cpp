#include "pch.h"
#include "SpriteColliderComponent.h"

namespace XYZEngine
{
	SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject) : ColliderComponent(gameObject)
	{
		auto spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
		if (spriteRenderer == nullptr)
		{
			std::cout << "SpriteRenderer required to SpriteCollider." << std::endl;
			gameObject->RemoveComponent(this);
			return;
		}

		sprite = gameObject->GetComponent<SpriteRendererComponent>()->GetSprite();
		PhysicsSystem::Instance()->Subscribe(this);
	}
	SpriteColliderComponent::~SpriteColliderComponent()
	{
		if (&bounds != nullptr)
		{
			std::destroy_at(&bounds);
		}
		PhysicsSystem::Instance()->Unsubscribe(this);
	}

	void SpriteColliderComponent::Update(float deltaTime)
	{
		auto transform = GetGameObject()->GetComponent<TransformComponent>();
		auto spriteRenderer = GetGameObject()->GetComponent<SpriteRendererComponent>();
		if (sprite == nullptr)
		{
			sprite = spriteRenderer->GetSprite();
		}

		if (sprite != nullptr && transform != nullptr)
		{
			// Update the sprite's transform manually here so bounds are perfectly in sync
			// with RigidbodyComponent updates that might have happened earlier in the frame
			auto nonConstSprite = const_cast<sf::Sprite*>(sprite);
			nonConstSprite->setPosition(Convert<sf::Vector2f, Vector2Df>(transform->GetWorldPosition()));
			nonConstSprite->setRotation(transform->GetWorldRotation());

			auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
			auto rendererScale = spriteRenderer->GetScale();
			nonConstSprite->setScale({ rendererScale.x * transformScale.x, rendererScale.y * transformScale.y });
		}

		bounds = sprite->getGlobalBounds();
	}
	void SpriteColliderComponent::Render()
	{
	}
}