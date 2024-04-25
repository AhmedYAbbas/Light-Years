#include "Player/PlayerManager.h"
#include "Player/Player.h"

namespace ly
{
	Scope<PlayerManager> PlayerManager::s_Instance = nullptr;

	PlayerManager& PlayerManager::Get()
	{
		if (!s_Instance)
			s_Instance = Scope<PlayerManager>{new PlayerManager};

		return *s_Instance;
	} 

	Player& PlayerManager::CreateNewPlayer()
	{
		return m_Players.emplace_back(Player());
	}

	Player* PlayerManager::GetPlayer(int index)
	{
		if (index >= 0 && index < m_Players.size())
			return &m_Players[index];

		return nullptr;
	}

	const Player* PlayerManager::GetPlayer(int index) const
	{
		if (index >= 0 && index < m_Players.size())
			return &m_Players[index];

		return nullptr;
	}

	void PlayerManager::Reset()
	{
		m_Players.clear();
	}
}