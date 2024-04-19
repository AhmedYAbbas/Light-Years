#pragma once

namespace ly
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		inline bool IsPendingDestroy() const { return m_IsPendingDestroy; }

	private:
		bool m_IsPendingDestroy;
	};
}