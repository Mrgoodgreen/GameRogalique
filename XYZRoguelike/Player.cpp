#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include "PlayerMovementComponent.h"
#include "HealthComponent.h"

namespace XYZRoguelike
{
	Player::Player()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		playerRenderer->SetPixelSize(32, 32);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto movement = gameObject->AddComponent<PlayerMovementComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto health = gameObject->AddComponent<HealthComponent>();
		health->Init(100.0f, 20.0f);
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}