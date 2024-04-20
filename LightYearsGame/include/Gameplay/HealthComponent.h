#pragma once

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
		void OnEmptyHealth();
		void RegenerateHealth(float amount);

	private:
		float m_Health;
		float m_MaxHealth;
	};
}