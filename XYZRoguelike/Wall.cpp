#include "Wall.h"
#include <ResourceSystem.h>
#include <SpriteRendererComponent.h>
#include <RigidbodyComponent.h>
#include <SpriteColliderComponent.h>
#include <GameWorld.h>

namespace XYZRoguelike
{
	Wall::Wall()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Wall");
		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("wall"));
		renderer->SetPixelSize(32, 32);

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		body->SetKinematic(true);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
	}

	XYZEngine::GameObject* Wall::GetGameObject()
	{
		return gameObject;
	}
}