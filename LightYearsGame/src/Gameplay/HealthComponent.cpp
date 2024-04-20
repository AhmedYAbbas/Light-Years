#include "Gameplay/HealthComponent.h"

#include <Core/Core.h>

namespace ly
{
	HealthComponent::HealthComponent(float health, float maxHealth)
		: m_Health{health}, m_MaxHealth{maxHealth}
	{
	}

	void HealthComponent::ChangeHealth(float amount)
	{
		if (amount == 0)
			return;
		if (m_Health == 0)
			return;

		m_Health += amount;
		if (m_Health < 0.f)
			m_Health = 0.f;
		if (m_Health > m_MaxHealth)
			m_Health = m_MaxHealth;

		if (amount < 0)
		{
			TakeDamage(-amount);

			if (m_Health <= 0)
				OnEmptyHealth();
		}
		else
		{

		}
	}

	void HealthComponent::TakeDamage(float amount)
	{
		LOG("Took Damage: %f, now health is: %f/%f", amount, m_Health, m_MaxHealth);
	}

	void HealthComponent::OnEmptyHealth()
	{
		LOG("DEAD!");
	}

	void HealthComponent::RegenerateHealth(float amount)
	{
		LOG("Health Regenerated: % f, now health is : % f / % f", amount, m_Health, m_MaxHealth);

	}
}