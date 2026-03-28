#pragma once
#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <algorithm>

namespace XYZRoguelike
{
	class CameraFollowComponent : public XYZEngine::Component
	{
	public:
		CameraFollowComponent(XYZEngine::GameObject* gameObject) 
			: XYZEngine::Component(gameObject), target(nullptr) {}

		void SetTarget(XYZEngine::GameObject* t) { target = t; }

		void Update(float deltaTime) override
		{
			if (!target) return;

			auto targetTransform = target->GetComponent<XYZEngine::TransformComponent>();
			auto myTransform = gameObject->GetComponent<XYZEngine::TransformComponent>();

			if (targetTransform && myTransform)
			{
				auto targetPos = targetTransform->GetWorldPosition();

				// Base camera pos
				float camX = targetPos.x;
				float camY = targetPos.y;

				// Width is 640, screen width is 1280. Center X is best. Map from x=-320 to 320.
				// Since map width is smaller than screen, just keep camX at 0 so we see everything.
				camX = 0.0f;

				// Map height goes from y=-320 to up to +1600.
				// For Y, we have half height = 360.
				// lowest visible Y should be around -320 (outer wall).
				// So if camY - 360 < -320 => camY < 40, we clamp to 40.
				// The maximum map height depends on level progress. Let's just limit bottom.
				// Also let's set a top limit, maybe up to 1600 (end of level 3).
				// If level 3 ends at 50 * 32 = 1600. 1600 - 360 = 1240.
				
				if (camY < 40.0f) camY = 40.0f;
				if (camY > 1240.0f) camY = 1240.0f;

				myTransform->SetWorldPosition(camX, camY);
			}
		}

		void Render() override {}

	private:
		XYZEngine::GameObject* target;
	};
}