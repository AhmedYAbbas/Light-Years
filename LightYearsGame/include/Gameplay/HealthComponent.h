#pragma once

#include "Framework/Delegate.h"

namespace ly
{
	class HealthComponent
	{
	public:
		HealthComponent(float health, float maxHealth);

		void ChangeHealth(float amount);
		float GetHealth() const { return m_Health; }
		float GetMaxHealth() const { return m_MaxHealth; }

	private:
		void TakeDamage(float amount);
		void HealthEmpty();

	public:
		Delegate<float, float, float> onHealthChanged;
		Delegate<float, float, float> onTakenDamage;
		Delegate<> onHealthEmpty;

	private:
		float m_Health;
		float m_MaxHealth;
	};
}