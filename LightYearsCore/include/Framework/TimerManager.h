#pragma once

#include <functional>

#include "Core/Core.h"
#include "Framework/Object.h"

namespace ly
{
	class TimerHandle
	{
	public:
		TimerHandle();

		inline unsigned int GetTimerKey() const { return m_TimerKey; }

	private:
		inline static unsigned int GetNextTimerKey() { return ++s_TimerKeyCounter; }

	private:
		unsigned int m_TimerKey;
		static unsigned int s_TimerKeyCounter;
	};

	class TimerHandleHash
	{
	public:
		size_t operator()(const TimerHandle& handle) const { return handle.GetTimerKey(); }
	};

	bool operator==(const TimerHandle& rhs, const TimerHandle& lhs);

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
		TimerHandle SetTimer(WeakRef<Object> obj, void(Class::* callback)(), float duration, bool repeat = false)
		{
			TimerHandle handle;
			m_Timers.insert({handle, Timer(obj, [=]()
			{
				(static_cast<Class*>(obj.lock().get())->*callback)();
			},
			duration,
			repeat)});

			return handle;
		}

		void UpdateTimer(float deltaTime);
		void ClearTimer(TimerHandle handle);

	protected:
		TimerManager() = default;

	private:
		Dict<TimerHandle, Timer, TimerHandleHash> m_Timers;

	private:
		static Scope<TimerManager> s_Instance;
	};
}