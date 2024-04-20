#include <Framework/Actor.h>

namespace ly
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);

		inline void SetSpeed(float speed) { m_Speed = speed; }
		inline void SetDamage(float damage) { m_Damage = damage; }

		inline float GetDamage() const { return m_Damage; }
		inline float GetSpeed() const { return m_Speed; }

	protected:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		
		virtual void OnActorBeginOverlap(Actor* other);

	private:
		void Move(float deltaTime);

	private:
		Actor* m_Owner;
		float m_Speed;
		float m_Damage;
	};
}  