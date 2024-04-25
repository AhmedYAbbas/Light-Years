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

		OnHealthChanged.Broadcast(amount, m_Health, m_MaxHealth);

		if (amount < 0)
		{
			TakeDamage(-amount);

			if (m_Health <= 0)
				HealthEmpty();
		}
	}

	void HealthComponent::SetInitialHealth(float health, float maxHealth)
	{
		m_Health = health;
		m_MaxHealth = maxHealth;
	}

	void HealthComponent::TakeDamage(float amount)
	{
		OnTakenDamage.Broadcast(amount, m_Health, m_MaxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		OnHealthEmpty.Broadcast();
	}
}