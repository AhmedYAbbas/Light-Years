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

	protected:
		Shooter(Actor* owner);
	private:
		virtual void ShootImpl() = 0;

	private:
		Actor* m_Owner;
	};
}