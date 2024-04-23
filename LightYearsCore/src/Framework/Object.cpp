#include "Framework/Object.h"
#include "Core/Core.h"

namespace ly
{
	unsigned int Object::s_UniqueIDCounter = 0;

	Object::Object()
		: m_IsPendingDestroy{false}, m_UniqueID{GetNextUniqueID()}
	{
	}

	Object::~Object()
	{
	}

	void Object::Destroy()
	{
		m_IsPendingDestroy = true;
	}

	unsigned int Object::GetNextUniqueID()
	{
		return ++s_UniqueIDCounter;
	}
}