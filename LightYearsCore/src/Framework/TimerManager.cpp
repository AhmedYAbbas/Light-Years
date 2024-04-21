#include "Framework/TimerManager.h"

namespace ly
{
	Scope<TimerManager> TimerManager::s_Instance = nullptr;
	unsigned int TimerHandle::s_TimerKeyCounter = 0;

	TimerManager& TimerManager::Get()
	{
		if (!s_Instance)
			s_Instance = Scope<TimerManager> {new TimerManager};

		return *s_Instance;
	}

	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (auto it = m_Timers.begin(); it != m_Timers.end();)
		{
			if (it->second.Expired())
				it = m_Timers.erase(it);
			else
			{
				it->second.TickTime(deltaTime);
				++it;
			}
		}
	}

	void TimerManager::ClearTimer(TimerHandle handle)
	{
		if (auto it = m_Timers.find(handle); it != m_Timers.end())
			it->second.SetExpired();
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

	TimerHandle::TimerHandle()
		: m_TimerKey {GetNextTimerKey()}
	{
	}

	bool operator==(const TimerHandle& rhs, const TimerHandle& lhs)
	{
		return rhs.GetTimerKey() == lhs.GetTimerKey();
	}
}