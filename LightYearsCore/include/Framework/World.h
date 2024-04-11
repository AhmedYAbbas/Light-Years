#pragma once

class Application;

namespace ly
{
	class World
	{
	public:
		World();
		virtual ~World() = default;

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		
	private:
		bool m_BeganPlay;
	};
}