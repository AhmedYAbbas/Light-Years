#pragma once

#include <memory>
#include <Core/Core.h>

namespace ly
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		inline bool IsPendingDestroy() const { return m_IsPendingDestroy; }

		inline WeakRef<Object> GetWeakRef() { return weak_from_this(); }
		inline WeakRef<const Object> GetWeakRef() const { return weak_from_this(); }

	private:
		bool m_IsPendingDestroy;
	};
}