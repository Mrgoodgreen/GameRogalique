#include "Enemy.h"
#include <ResourceSystem.h>
#include <SpriteRendererComponent.h>
#include <RigidbodyComponent.h>
#include <SpriteColliderComponent.h>
#include "EnemyAIComponent.h"
#include "HealthComponent.h"

namespace XYZRoguelike
{
	Enemy::Enemy()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball")); // RE-USE ball for now
		renderer->SetPixelSize(32, 32);
		renderer->SetColor(sf::Color::Red); // Make enemy red

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto ai = gameObject->AddComponent<EnemyAIComponent>();

		auto health = gameObject->AddComponent<HealthComponent>();
		health->Init(50.0f, 0.0f); // 50 HP, 0 armor
	}

	XYZEngine::GameObject* Enemy::GetGameObject()
	{
		return gameObject;
	}
}