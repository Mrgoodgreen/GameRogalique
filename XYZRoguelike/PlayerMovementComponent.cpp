#include "PlayerMovementComponent.h"
#include "GameObject.h"
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
	}

	void PlayerMovementComponent::Render()
	{
	}
}