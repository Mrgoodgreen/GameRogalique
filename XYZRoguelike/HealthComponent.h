#pragma once
#include "Component.h"
#include <iostream>
#include <algorithm>
#include "Logger.h"

namespace XYZRoguelike
{
	class HealthComponent : public XYZEngine::Component
	{
	public:
		HealthComponent(XYZEngine::GameObject* gameObject) : XYZEngine::Component(gameObject) {}
		~HealthComponent() override = default;

		void Init(float maxHp, float maxArmor)
		{
			hp = maxHp;
			armor = maxArmor;
		}

		void Update(float deltaTime) override {}
		void Render() override {}

		void TakeDamage(float amount)
		{
			if (amount < 0) return;
			float damageToArmor = std::min(amount, armor);
			armor -= damageToArmor;
			float damageToHp = amount - damageToArmor;
			hp -= damageToHp;
			
			XYZEngine::Logger::Log(XYZEngine::LogLevel::INFO, GetGameObject()->GetName() + " took " + std::to_string(amount) + " damage. HP left: " + std::to_string(hp));

			if (hp <= 0)
			{
				hp = 0;
				XYZEngine::Logger::Log(XYZEngine::LogLevel::WARNING, GetGameObject()->GetName() + " died!");
			}
		}

		bool IsDead() const { return hp <= 0; }
		float GetHp() const { return hp; }

	private:
		float hp = 100.f;
		float armor = 0.f;
	};
}