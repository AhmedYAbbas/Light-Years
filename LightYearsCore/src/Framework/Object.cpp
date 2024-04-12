#include "Framework/Object.h"
#include "Core/Core.h"

namespace ly
{
	Object::Object()
		: m_IsPendingDestroy{false}
	{
	}

	Object::~Object()
	{
	}

	void Object::Destroy()
	{
		m_IsPendingDestroy = true;
	}
}