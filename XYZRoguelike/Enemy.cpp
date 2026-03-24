#include "Enemy.h"
#include <ResourceSystem.h>
#include <SpriteRendererComponent.h>
#include <RigidbodyComponent.h>
#include <SpriteColliderComponent.h>
#include "EnemyAIComponent.h"

namespace XYZRoguelike
{
	Enemy::Enemy()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball")); // RE-USE ball for now
		renderer->SetPixelSize(32, 32);

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto ai = gameObject->AddComponent<EnemyAIComponent>();
	}

	XYZEngine::GameObject* Enemy::GetGameObject()
	{
		return gameObject;
	}
}