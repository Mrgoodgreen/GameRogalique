#include "Floor.h"
#include <ResourceSystem.h>
#include <SpriteRendererComponent.h>
#include <GameWorld.h>

namespace XYZRoguelike
{
	Floor::Floor()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Floor");
		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("floor"));
		renderer->SetPixelSize(32, 32);

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		// No collider or rigidbody
	}

	XYZEngine::GameObject* Floor::GetGameObject()
	{
		return gameObject;
	}
}