#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Core.h"
#include "Utility/Math.h"
#include "Framework/Object.h"
#include "Framework/World.h"
#include "Framework/Delegate.h"

class b2Body;

namespace ly
{

	class Actor : public Object
	{
	public:
		Actor(World* world, const std::string& filepath = "");
		virtual ~Actor() = default;

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		void SetTexture(const std::string& filepath);
		void SetTextureRepeated(bool repeated);
		virtual void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& pos);
		void SetActorRotation(float angle);
		void AddActorLocationOffset(const sf::Vector2f& offset);
		void AddActorRotationOffset(float offset);

		inline const sf::Vector2f& GetActorLocation() const { return m_Sprite.getPosition(); }
		inline float GetActorRotation() const { return m_Sprite.getRotation(); }
		inline sf::Vector2f GetForwardDirection() { return Math::RotationToVector(GetActorRotation()); }
		inline sf::Vector2f GetRightDirection() { return Math::RotationToVector(GetActorRotation() + 90.f); }

		inline sf::FloatRect GetActorGlobalBounds() const { return m_Sprite.getGlobalBounds(); }
		sf::Vector2u GetWindowSize() const { return m_World->GetWindowSize(); }

		inline const World* GetWorld() const { return m_World; }
		inline World* GetWorld() { return m_World; }

		bool IsActorOutOfWindowBounds(float allowance = 10.f) const;
		void SetEnablePhysics(bool enable);

		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);

		virtual void Destroy() override;

		inline void SetTeamID(int teamID) { m_TeamID = teamID; }
		inline static int GetNeutralTeamID() { return s_NeutralTeamID; }
		inline int GetTeamID() const { return m_TeamID; }

		bool IsOtherHostile(Actor* other);
		virtual void TakeDamage(float amout);

		sf::Sprite& GetSprite() { return m_Sprite; }
		const sf::Sprite& GetSprite() const { return m_Sprite; }

	protected:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);


	private:
		void CenterPivot();
		void InitializePhysics();
		void UninitializePhysics();
		void UpdatePhysicsBodyTransform();

	public:
		Delegate<Actor*> OnActorDestroyed;

	private:
		World* m_World;
		bool m_HasBegunPlay;

		sf::Sprite m_Sprite;
		Ref<sf::Texture> m_Texture;

		b2Body* m_PhysicsBody;
		bool m_PhysicsEnabled;

		int m_TeamID;
		static const int s_NeutralTeamID = 255;
	};
}