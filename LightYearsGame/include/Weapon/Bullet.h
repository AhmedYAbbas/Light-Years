#include <Framework/Actor.h>

namespace ly
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);

		inline void SetSpeed(float speed) { m_Speed = speed; }
		inline void SetDamage(float damage) { m_Damage = damage; }

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		void Move(float deltaTime);

	private:
		Actor* m_Owner;
		float m_Speed;
		float m_Damage;
	};
}