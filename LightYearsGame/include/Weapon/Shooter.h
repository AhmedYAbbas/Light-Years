#pragma once

namespace ly
{
	class Actor;

	class Shooter
	{
	public:
		void Shoot();

		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }
		Actor* GetOwner() const { return m_Owner; }

		inline int GetCurrentLevel() const { return m_CurrentLevel; }
		inline int GetMaxLevel() const { return m_MaxLevel; }

		virtual void IncrementLevel(int amount = 1);

	protected:
		Shooter(Actor* owner);
	private:
		virtual void ShootImpl() = 0;

	private:
		Actor* m_Owner;

		int m_CurrentLevel;
		int m_MaxLevel;
	};
}