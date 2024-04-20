#pragma once

#include <functional>
#include "Core/Core.h"

namespace ly
{
	class Object;

	template<typename... Args>
	class Delegate
	{
	public:
		template<typename Class>
		void Bind(WeakRef<Object> obj, void(Class::*callback)(Args...))
		{
			std::function<bool(Args&&...)> callbackFunc = [obj, callback](Args&&... args) -> bool
			{
				if (!obj.expired())
				{
					(static_cast<Class*>(obj.lock().get())->*callback)(std::forward<Args>(args)...);
					return true;
				}
				return false;
			};
			m_Callbacks.push_back(callbackFunc);
		}

		void Broadcast(Args... args)
		{
			for (auto it = m_Callbacks.begin(); it != m_Callbacks.end();)
			{
				if ((*it)(std::forward<Args>(args)...))
					it++;
				else
					it = m_Callbacks.erase(it);
			}
		}

	private:
		Vector<std::function<bool(Args&&...)>> m_Callbacks;
	};
}