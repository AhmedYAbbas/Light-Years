#pragma once

#include <functional>

#include "Core/Core.h"
#include "Framework/Object.h"

namespace ly
{
	class Timer
	{
	public:
		Timer(WeakRef<Object> obj, std::function<void()> callback, float duration, bool repeat);

		void TickTime(float deltaTime);
		inline bool Expired() const { return m_IsExpired || m_Listener.first.expired() || m_Listener.first.lock()->IsPendingDestroy(); }
		inline void SetExpired() { m_IsExpired = true; }

	private:
		std::pair<WeakRef<Object>, std::function<void()>> m_Listener;
		float m_Duration;
		bool m_Repeat;
		float m_TimeCounter;
		bool m_IsExpired;
	};

	class TimerManager
	{
	public:
		static TimerManager& Get();

		template<typename Class>
		void SetTimer(WeakRef<Object> obj, void(Class::* callback)(), float duration, bool repeat = false)
		{
			m_Timers.push_back(Timer(obj, [=]()
			{
				(static_cast<Class*>(obj.lock().get())->*callback)();
			},
			duration,
			repeat));
		}

		void UpdateTimer(float deltaTime);

	protected:
		TimerManager() = default;

	private:
		Vector<Timer> m_Timers;

	private:
		static Scope<TimerManager> s_Instance;
	};
}