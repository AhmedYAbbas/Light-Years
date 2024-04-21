#include "Framework/TimerManager.h"

namespace ly
{
	Scope<TimerManager> TimerManager::s_Instance = nullptr;


	TimerManager& TimerManager::Get()
	{
		if (!s_Instance)
			s_Instance = Scope<TimerManager> {new TimerManager};

		return *s_Instance;
	}

	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (Timer& timer : m_Timers)
		{
			timer.TickTime(deltaTime);
		}
	}

	Timer::Timer(WeakRef<Object> obj, std::function<void()> callback, float duration, bool repeat)
		: m_Listener{obj, callback}, m_Duration{duration}, m_Repeat{repeat}, m_TimeCounter{0.f}, m_IsExpired{false}
	{
	}

	void Timer::TickTime(float deltaTime)
	{
		if (m_IsExpired)
			return;

		m_TimeCounter += deltaTime;
		if (m_TimeCounter >= m_Duration)
		{
			m_Listener.second();
			if (m_Repeat)
				m_TimeCounter = 0.f;
			else
				SetExpired();
		}
	}
}